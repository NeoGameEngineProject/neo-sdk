#ifndef NEO_PLATFORMRENDERER_H
#define NEO_PLATFORMRENDERER_H

#include <bgfx/bgfx.h>
#include <Common.h>
#include <Array.h>

namespace Neo 
{

class Vector4;
class LightBehavior;

class PlatformRenderer : public BGFX::Common
{
	unsigned int m_width, m_height;
	Array<LightBehavior*> m_visibleLights;
	Array<Vector4> m_lightBuffer;
	
	size_t m_maxVisibleLights = 256;
	static const unsigned int MAX_LIGHTS_PER_OBJECT = 8;
	
	bgfx::TextureHandle m_lightsTexture;
	bgfx::UniformHandle m_lightsTextureUniform, m_config;
	
	struct Light
	{
		bgfx::UniformHandle position, color, option, direction;
	} m_lightUniforms;
	
public:
	void beginFrame(Level& level, CameraBehavior& cam) override;
	void beginFrame(Neo::CameraBehavior & camera) override;
	void clear(float r, float g, float b, bool depth) override;
	void endFrame() override;
	void initialize(unsigned int w, unsigned int h, void * ndt, void * nwh) override;
	void swapBuffers() override;
};

}

#endif // NEO_PLATFORMRENDERER_H