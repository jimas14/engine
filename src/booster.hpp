#ifndef ML_BOOSTER_HPP
#define ML_BOOSTER_HPP

#include <memory>
#include <string>
#include <iostream>
#include <Box2D/Box2D.h>
#include <spdlog/spdlog.h>
#include <json/json_fwd.hpp>
#include "settings.hpp"
#include "collision_user_data.hpp"
#include "booster_type.hpp"
#include "ball.hpp"
#include "game_accessor.hpp"

struct ball;

struct booster
{
    static thread_local std::size_t id_counter;
    std::size_t id;
    game_accessor game;
    float x;
    float y;
    booster_type type;
    b2Body * body;
    std::shared_ptr<collision_user_data> col_data;
    bool is_alive;
    int respawn_counter;

    booster();
    booster(
        const float x,
        const float y,
        const booster_type type
    );
    ~booster();

    void add_to_world(b2World* world);
    void step_on(ball* m);
    void boost_ball(ball* m);
};

void to_json(nlohmann::json& j, const booster& p);
void from_json(const nlohmann::json& j, booster& p);

#endif

