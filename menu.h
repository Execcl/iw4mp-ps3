#pragma once


class menu : public menu_base
{
public:

	menu() = default;
	menu(const char* name) : menu_base(name){}

	void on_build();
	void on_draw();
	void on_run();
	bool check_variables();

	void on_trigger();
	void on_open();
	void on_close();
	void on_back();
	void check_events();

	int on_scroll_up();
	int on_scroll_down();
	void on_scroll_left();
	void on_scroll_right();
	void check_scrolling();

	bool is_open();

	menu_tab* m_currentTab{};

	menu_item* m_currentItem{};

	int m_maxOptions{};
	int m_maxViewableOptions{};
	int m_currentScroll{};
	int m_currentScrollOffset{};
};

extern menu* g_menu;

