#ifndef NEO_WINDOW_H
#define NEO_WINDOW_H

#include <Renderer.h>
#include <memory>

namespace Neo
{

class Window
{
	std::unique_ptr<Renderer> m_renderer;
	unsigned int m_width, m_height;
public:
	Window(unsigned int w, unsigned int h) : m_width(w), m_height(h) {}
	virtual ~Window() {}
	virtual void setTitle(const char* title) = 0;
	virtual void activateRendering() = 0;
	virtual void swapBuffers() = 0;
	
	Renderer* getRenderer() { return m_renderer.get(); }
	void setRenderer(std::unique_ptr<Renderer>&& renderer, void* ndt, void* nwh) 
	{ 
		m_renderer = std::move(renderer); 
		m_renderer->initialize(m_width, m_height, ndt, nwh);
	}
	
	virtual void setRenderer(std::unique_ptr<Renderer>&& renderer) = 0;
};

}

#endif // NEO_WINDOW_H