#ifndef NEO_SOUNDCONTEXT_H
#define NEO_SOUNDCONTEXT_H

#include <Sound.h>

namespace Neo
{

class SoundContext
{
public:
	virtual void initialize(const char* device) = 0;
};

}

#endif // NEO_SOUNDCONTEXT_H