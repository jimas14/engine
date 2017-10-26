#include "websocket_server.hpp"

std::uint16_t get_local_port(
    server* srv,
    websocketpp::connection_hdl hdl
) {
    server::connection_ptr connection = srv->get_con_from_hdl(hdl);
    auto local_endpoint = connection->get_raw_socket().local_endpoint();

    return local_endpoint.port();
}

void on_lobby_request_games(
    server* srv,
    websocketpp::connection_hdl hdl,
    message_ptr msg
) {
    const server_lobby& lobby = server_lobby::get_instance();

    std::vector<request_lobby_games_response> games;
    games.reserve(lobby.games.size());

    for(auto && o : lobby.games) {
        games.emplace_back(
            o->port,
            o->max_points,
            o->max_length,
            o->timestep,
            o->m->name,
            o->m->author,
            o->m->balls.size()
        );
    }

    try {
        srv->send(
            hdl,
            nlohmann::json({{"games", games}}).dump(),
            msg->get_opcode()
        );
    } catch (const websocketpp::lib::error_code& e) {
        std::cerr
            << "Echo failed because: " << e
            << "(" << e.message() << ")"
            << std::endl;
    }

}

void handle_lobby_message(
    server* srv,
    websocketpp::connection_hdl hdl,
    message_ptr msg
) {
    try {
        nlohmann::json j = nlohmann::json::parse(msg->get_payload());
        // std::cout << j.dump() << std::endl;

        if(j.at("request").get<std::string>() == "games") {
            return on_lobby_request_games(srv, hdl, msg);
        }

    } catch(...) {
        srv->send(
            hdl,
            nlohmann::json({{"error", "json_parse_error"}}).dump(),
            msg->get_opcode()
        );
    }
}

void on_game_ready(
    server* srv,
    websocketpp::connection_hdl hdl,
    message_ptr msg,
    const std::string& login_token
) {
    server_lobby& lobby = server_lobby::get_instance();

    game& g = lobby.get_game_from_port(get_local_port(srv, hdl));

    /* get login_token
     * so we can get user_id, name, degrees
     * respond with map id
     */
    // user o = something(login_token);


    if(g.m->balls.size() >= 8) {
        // error
        return;
    }

    /*
     * check game still has open slot
     * we send all map data here to sync user
     * add clients ball
     * notify all clients on game of new ball
     * save connection hdl/server into stdmap
     */
    try {
        srv->send(
            hdl,
            nlohmann::json({{"mapsync", "todo"}}).dump(),
            msg->get_opcode()
        );
    } catch (const websocketpp::lib::error_code& e) {
        std::cerr
            << "Echo failed because: " << e
            << "(" << e.message() << ")"
            << std::endl;
    }
}

void on_game_chat(
    server* srv,
    websocketpp::connection_hdl hdl,
    message_ptr msg,
    const std::string& chat_msg
) {
    server_lobby& lobby = server_lobby::get_instance();

    game& g = lobby.get_game_from_port(get_local_port(srv, hdl));

    // broadcast chat_msg
}

void handle_game_message(
    server* srv,
    websocketpp::connection_hdl hdl,
    message_ptr msg
) {
    try {
        nlohmann::json j = nlohmann::json::parse(msg->get_payload());
        std::cout << j.dump() << std::endl;

        if(j.find("ready") != j.end()) {
            const std::string login_token = j["ready"].at("login_token").get<std::string>();
            return on_game_ready(srv, hdl, msg, login_token);
        }

        if(j.find("chat") != j.end()) {
            const std::string chat_msg = j.at("chat").get<std::string>();
            return on_game_chat(srv, hdl, msg, chat_msg);
        }
    } catch(...) {
        srv->send(
            hdl,
            nlohmann::json({{"error", "json_parse_error"}}).dump(),
            msg->get_opcode()
        );
    }
} 

int start_lobby_server(
    server_lobby& lobby,
    const std::uint16_t port
) {
    std::cout << "starting tagos lobby server... ";
    server srv;

    try {
        srv.set_access_channels(websocketpp::log::alevel::all);
        srv.clear_access_channels(websocketpp::log::alevel::frame_payload);

        srv.init_asio();
        srv.set_message_handler(bind(&handle_lobby_message,&srv,::_1,::_2));
        srv.listen(port);

        std::cout << "on port: " << port << std::endl;

        srv.start_accept();
        srv.run();
    } catch (websocketpp::exception const & e) {
        std::cerr << "error: server exception: " << e.what() << std::endl;
        lobby.is_alive = false;
        return 1;
    } catch (...) {
        std::cerr << "error: unknown server exception" << std::endl;
        lobby.is_alive = false;
        return 1;
    }

    return 0;
}

int start_game_server(const std::uint16_t port) 
{
    std::cout << "starting tagos game server... ";
    server srv;

    try {
        srv.set_access_channels(websocketpp::log::alevel::all);
        srv.clear_access_channels(websocketpp::log::alevel::frame_payload);

        srv.init_asio();
        srv.set_message_handler(bind(&handle_game_message,&srv,::_1,::_2));
        srv.listen(port);

        std::cout << "on port: " << port << std::endl;

        srv.start_accept();
        srv.run();
    } catch (websocketpp::exception const & e) {
        std::cerr << "error: server exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "error: unknown server exception" << std::endl;
        return 1;
    }

    return 0;
}

