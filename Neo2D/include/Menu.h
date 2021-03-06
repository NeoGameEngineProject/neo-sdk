#ifndef NEO_MENU_H
#define NEO_MENU_H

#include <Neo2D.h>
#include <Button.h>
#include <Container.h>

namespace Neo2D
{
namespace Gui
{

class NEO2D_EXPORT MenuItem : public Button
{
	bool m_visible;

public:
	MenuItem(const char* label, const shared_ptr<Object2D>& parent, const shared_ptr<Theme>& theme = nullptr)
		: Button(0,0,0,0, label, parent, theme),
		  m_visible(false)
	{
		setActive(false);
	}

	virtual bool handle(const Event& event) override;

	bool isVisible() const { return m_visible; }
	virtual void setVisible(bool b) { m_visible = b; }
	void hideHierarchy();
};

class NEO2D_EXPORT Submenu : public MenuItem
{
#ifndef SWIG
	std::vector<std::shared_ptr<MenuItem>> m_children;
#endif

	bool m_drawSelf;
	
protected:
	void addItem(const std::shared_ptr<MenuItem>& i) { i->doInit(); m_children.push_back(i); }

public:
	Submenu(const char* label, const shared_ptr<Object2D>& parent, const shared_ptr<Theme>& theme = nullptr);

	bool isDrawingItself() const { return m_drawSelf; }
	void enableDrawingSelf(bool b) { m_drawSelf = b; }
	
	std::shared_ptr<MenuItem> findChild(const std::string&) const;
	std::shared_ptr<Submenu> findSubmenu(const std::string& name) const
	{
		return dynamic_pointer_cast<Submenu>(findChild(name));
	}

	virtual bool handle(const Event& e) override;
	virtual void draw(const Neo::Vector2& offset) override
	{
		if(isVisible())
		{
			for(auto m : m_children)
			{
				m->draw(Neo::Vector2());
			}
		}

		if(isDrawingItself())
			MenuItem::draw(offset);
	}

	virtual void update(float dt) override
	{
		//if(isActive())
		//{
		size_t line = 0;
		MenuItem::update(dt);

		for(auto m : m_children)
		{
			m->setPosition(getPosition() + Neo::Vector2(!isDrawingItself() ? 0 : getSize().x, line));
			m->setSize(getSize());
			line += getSize().y + 1;

			m->update(dt);
		}
		//}
	}

	virtual void setVisible(bool b) override
	{
		MenuItem::setVisible(b);
	}

	virtual void hideChildren()
	{
		for(auto m : m_children)
		{
			m->setActive(false);
			m->setVisible(false);
		}
	}

	virtual void deselectChildren()
	{
		for(auto m : m_children)
		{
			auto sm = dynamic_pointer_cast<Submenu>(m);
			if(sm)
			{
				sm->hideChildren();
				sm->setVisible(false);
				sm->setActive(false);
			}
		}
	}

	shared_ptr<MenuItem> addItem(const std::string& name, std::function<void(Widget&, void*)> cb);
};

class NEO2D_EXPORT Menubar : public Widget
{
	// FIXME: Don't hardcode!!
	const unsigned int BTN_WIDTH = 70;

	struct MenuButton
	{
		shared_ptr<Submenu> submenu;
		shared_ptr<Button> button;
	};

	std::vector<MenuButton> m_children;

	virtual void hideChildren()
	{
		for(auto m : m_children)
		{
			m.submenu->setActive(false);
			m.submenu->setVisible(false);
		}
	}

public:
	Menubar(int x, int y, unsigned int w, unsigned int h,
			const shared_ptr<Object2D>& parent, const shared_ptr<Theme>& theme = nullptr);

	void addMenu(const shared_ptr<Submenu>& menu)
	{
		MenuButton menubutton;
		menubutton.submenu = menu;
		menubutton.button = make_shared<Button>(BTN_WIDTH * m_children.size() + getPosition().x, getPosition().y,
												BTN_WIDTH, getSize().y, menu->getLabel(), shared_from_this());

		menu->setPosition(menubutton.button->getPosition() + Neo::Vector2(0, getSize().y));

		menubutton.button->setCallback([] (Widget& w, void* data) {

			Submenu* menu = reinterpret_cast<Submenu*>(data);
			bool menuvalue = !menu->isVisible();

			static_pointer_cast<Menubar>(w.getParent().lock())->hideChildren();

			menu->setVisible(menuvalue);
			menu->setActive(menuvalue);

			menu->deselectChildren();

		}, menu.get());

		menu->setActive(false);
		menu->setVisible(false);
		menu->enableDrawingSelf(false);

		menubutton.submenu->doInit();
		menubutton.button->doInit();

		m_children.push_back(menubutton);
	}

	virtual void update(float dt) override
	{
		for(auto c : m_children)
			c.submenu->update(dt);
		
		Widget::update(dt);
	}

	virtual void draw(const Neo::Vector2& offset) override
	{
		Widget::draw(offset);

		unsigned int x = getPosition().x + BTN_WIDTH * m_children.size();

		for(auto menu : m_children)
		{
			menu.button->draw(offset);
			if(menu.submenu->isActive())
				menu.submenu->draw(offset);
		}
	}
};

}
}

#endif //NEO_MENU_H
