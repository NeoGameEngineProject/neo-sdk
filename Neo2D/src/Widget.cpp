#include "Widget.h"
#include <unordered_map>
#include <algorithm>

using namespace Neo2D::Gui;

Widget::Widget(int x, int y, unsigned int w, unsigned int h, 
				const char* label,
				const std::shared_ptr<Object2D>& parent,
				const std::shared_ptr<Theme>& theme) :
	Object2D(x, y, w, h, parent),
	m_theme(theme),
	m_state(WIDGET_NORMAL),
	m_label(label ? label : ""),
	m_initialized(false)
{
	
}

void Widget::update(float dt)
{
	doInit();

	if(!isActive())
		return;

	std::unordered_map<unsigned int, bool> handled;
	if(getParent().expired())
		for(auto iter = m_events.begin(); iter != m_events.end(); iter++)
		{
			auto e = *iter;
			if(e && e->getReceiver() && !handled[e->getType()]
				&& e->getReceiver()->isActive())
			{
				e->update(dt);
				handled[e->getType()] = e->handled();
			}
		}
}

void Widget::unregisterEvent(Widget& w)
{
	auto parent = dynamic_pointer_cast<Widget>(getParent().lock());
	if(parent)
	{
		parent->unregisterEvent(w);
		return;
	}

	for(int i = m_events.size() - 1; i >= 0; i--)
		if(m_events[i]->getReceiver().get() == &w) m_events.erase(m_events.begin() + i);
}
