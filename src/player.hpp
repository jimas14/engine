#ifndef ML_PLAYER_HPP
#define ML_PLAYER_HPP

#include <string>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "game.hpp"
#include "ball.hpp"
#include "player_stats.hpp"

struct game;
struct ball;

struct player
{
    bool local;
    bool remove;
    websocketpp::connection_hdl con;
    websocketpp::server<websocketpp::config::asio>* srv;
    game* g;
    ball* b;
    std::string player_id;
    bool is_registered;
    std::string name;
    std::uint32_t degree;

    int xdir;
    int ydir;

    player_stats stats;

    player(
        const websocketpp::connection_hdl con,
        websocketpp::server<websocketpp::config::asio>* srv,
        game* g,
        const std::string player_id,
        const bool is_registered,
        const std::string name,
        const std::uint32_t degree
    );

    // for "bots"
    player(
        game* g,
        ball* b,
        const std::string player_id,
        const bool is_registered,
        const std::string name,
        const std::uint32_t degree
    );

    ~player();
};

#endif
