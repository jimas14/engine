#ifndef ML_SERVER_EVENT_POWERUP_RESPAWN_HPP
#define ML_SERVER_EVENT_POWERUP_RESPAWN_HPP

#include "powerup.hpp"

struct powerup;

struct server_event_powerup_respawn
{
    powerup* m;

    server_event_powerup_respawn(powerup* m);
};

#endif
