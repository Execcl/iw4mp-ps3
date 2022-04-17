#pragma once

class menu_tab
{
public:
	menu_tab(const char* Name);
	~menu_tab();

	const char* get_name();
	menu_item* get_option(unsigned int index);
	unsigned int get_count();

	short get_cursor();
	short get_cursor_offset();
	menu_tab* get_parent();

	void set_cursor(short index);
	void set_cursor_offset(short offset);
	void set_parent(menu_tab* parent);

	menu_item& add_option(const char* name);

	std::vector<menu_item*> m_TabOptions;
	short m_TabCursor;
	short m_TabOffset;
private:
	char name[32];
	menu_tab* m_TabParent;
};