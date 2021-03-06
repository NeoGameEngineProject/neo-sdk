#include <HorizontalLayout.h>

void Neo2D::Gui::HorizontalLayout::updateLayout(const Widget& w, std::vector<shared_ptr<Widget>>& v, const Neo::Vector2& offset)
{
	float sy = w.getSize().y, sx = w.getSize().x / v.size();
	float px = w.getPosition().x;
	for(auto c : v)
	{
		c->setSize(Neo::Vector2(sx, sy));
		c->setPosition(offset + Neo::Vector2(px, w.getPosition().y));
		px += sx;
	}
}


















