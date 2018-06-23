#ifndef NEO_ANIMATEDRENDERBEHAVIOR_H
#define NEO_ANIMATEDRENDERBEHAVIOR_H

#include <Behavior.h>

namespace Neo 
{

class AnimatedRenderBehavior : public Neo::Behavior
{
public:
    const char* getName() const override { return "AnimatedRender"; }
};

}

#endif // NEO_ANIMATEDRENDERBEHAVIOR_H