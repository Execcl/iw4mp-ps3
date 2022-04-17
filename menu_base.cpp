#include "stdafx.h"

extern "C" void __cxa_pure_virtual() { while (1); }

menu_tab* menu_base::get_current()
{
	return this->menu_stack.top();
}

menu_tab* menu_base::find_menu(const char* name)
{
	for (auto* menu : this->submenus)
	{
		if (strcmp(menu->get_name(), name) == 0)
			return menu;
	}

	return nullptr;
}

CellPadData* menu_base::get_buttons()
{
	return &this->cell_buttons;
}

unsigned int menu_base::get_flags()
{
	return this->flags;
}

void menu_base::set_flags(unsigned int flags)
{
	this->flags |= flags;
}

void menu_base::remove_flags(unsigned int flags)
{
	this->flags &= ~flags;
}

bool menu_base::test_flags(unsigned int bits)
{
	return this->flags & (bits);
}

std::string menu_base::get_name()
{
	return this->name;
}

menu_base::menu_base(const char* name)
{
	strcpy(this->name, name);
	this->menu_stack.empty();
}

menu_base::~menu_base()
{
	this->menu_stack.empty();

	for (int i = 0; i < this->submenus.size(); i++)
	{
		auto submenu = this->submenus.at(i);
		delete submenu;
	}

	this->submenus.clear();
	memset(this, 0, sizeof(*this));
}
