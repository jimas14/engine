#ifndef ML_GAME_EVENT_HPP
#define ML_GAME_EVENT_HPP

#include <spdlog/spdlog.h>
#include <json.hpp>
#include "game_event_type.hpp"
#include "game_event_gamesync.hpp"
#include "game_event_player_joined.hpp"
#include "game_event_player_left.hpp"
#include "game_event_chat.hpp"
#include "game_event_teamchat.hpp"
#include "game_event_honk.hpp"
#include "game_event_ballsync.hpp"
#include "game_event_ball_respawn.hpp"
#include "game_event_bomb_respawn.hpp"
#include "game_event_powerup_respawn.hpp"
#include "game_event_booster_respawn.hpp"
#include "game_event_portal_respawn.hpp"

/*
#include "game_event_ball_popped.hpp"
#include "game_event_ball_boosted.hpp"
#include "game_event_portal_ball.hpp"
#include "game_event_bomb_explosion.hpp"
#include "game_event_flag_grabbed.hpp"
#include "game_event_flag_dropped.hpp"
#include "game_event_flag_transferred.hpp"
#include "game_event_team_score.hpp"
#include "game_event_toggle_on.hpp"
#include "game_event_toggle_off.hpp"
*/

struct game_event_gamesync;
struct game_event_ballsync;
struct game_event_player_joined;
struct game_event_player_left;
struct game_event_chat;
struct game_event_teamchat;
struct game_event_honk;
struct game_event_ball_respawn;
struct game_event_bomb_respawn;
struct game_event_powerup_respawn;
struct game_event_booster_respawn;
struct game_event_portal_respawn;


// this is used for relaying game events over network
struct game_event
{
    game_event_type type;
    void* ptr;

    game_event(const game_event_gamesync e);
    game_event(const game_event_ballsync e);
    game_event(const game_event_player_joined e);
    game_event(const game_event_player_left e);
    game_event(const game_event_chat e);
    game_event(const game_event_teamchat e);
    game_event(const game_event_honk e);
    game_event(const game_event_ball_respawn e);
    game_event(const game_event_bomb_respawn e);
    game_event(const game_event_powerup_respawn e);
    game_event(const game_event_booster_respawn e);
    game_event(const game_event_portal_respawn e);

};

void to_json(nlohmann::json& j, const game_event& p);

#endif
