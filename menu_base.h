#pragma once

enum menu_flags {
	open = (1 << 1),
	interactive = (1 << 2),
	moving = (1 << 3),
};

class menu_tab;

class menu_base
{
public:
	menu_base() = default;
	menu_base(const char* name);
	~menu_base();

	menu_tab* get_current();
	menu_tab* find_menu(const char* name);

	CellPadData* get_buttons();

	unsigned int get_flags();
	void set_flags(unsigned int flags);
	void remove_flags(unsigned int flags);
	bool test_flags(unsigned int flags);

	std::string get_name();

protected:
	std::stack<menu_tab*> menu_stack;
	std::vector<menu_tab*> submenus;
	unsigned short flags;
	CellPadData cell_buttons;
	char name[32];
};