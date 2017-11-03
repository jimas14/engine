#include "game_event_ball_respawn.hpp"

void to_json(nlohmann::json& j, const game_event_ball_respawn& p)
{
    j = nlohmann::json{
        {"id", p.id},
        {"px", p.pos.x},
        {"py", p.pos.y}
    };
}
