#include "stdafx.h"

const char* menu_tab::get_name()
{
	return name;
}

menu_item* menu_tab::get_option(unsigned int index)
{
	return m_TabOptions.at(index);
}

unsigned int menu_tab::get_count()
{
	return m_TabOptions.size();
}

short menu_tab::get_cursor()
{
	if (m_TabCursor > m_TabOptions.size())
		return -1;

	return m_TabCursor;
}

short menu_tab::get_cursor_offset()
{
	return m_TabOffset;
}

menu_tab* menu_tab::get_parent()
{
	return m_TabParent;
}

void menu_tab::set_cursor(short index)
{
	m_TabCursor = index;
}

void menu_tab::set_cursor_offset(short offset)
{
	m_TabOffset = offset;
}

void menu_tab::set_parent(menu_tab* parent)
{
	m_TabParent = parent;
}

menu_item& menu_tab::add_option(const char* name)
{
	menu_item* item = new menu_item(name);
	m_TabOptions.push_back(item);
	return *item;
}


menu_tab::menu_tab(const char* Name)
{
	strcpy(name, Name);
	set_cursor(0);
	set_cursor_offset(0);
}

menu_tab::~menu_tab()
{
	for (int i = 0; i < m_TabOptions.size(); i++)
	{
		auto option = m_TabOptions.at(i);
		delete option;
	}

	m_TabOptions.clear();
	memset(this, 0, sizeof(*this));
}