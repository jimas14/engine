#include <Box2D/Box2D.h>
#include <vector>

struct GravWellAABBCallback : public b2QueryCallback
{
    std::vector<b2Body*> bodies;

    bool ReportFixture(b2Fixture* fixture);
};

