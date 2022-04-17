#include "stdafx.h"

menu_item::menu_item()
{
	memset(this, 0, sizeof * this);
}

menu_item::menu_item(const char* Name)
{
	memset(this, 0, sizeof * this);
	name = Name;

	set_type();
}

std::string menu_item::get_tooltip()
{
	return tooltip;
}

std::string menu_item::get_name() {
	return name;
}

bool menu_item::get_bool() {
	return *(bool*)m_valuePtr;
}

int menu_item::get_int() {
	return *(int*)m_valuePtr;
}

float menu_item::get_float() {
	return *(float*)m_valuePtr;
}

void(*menu_item::get_callback())() {
	return m_OptionCallback;
}

void menu_item::set_bool(bool value)
{
	*(bool*)m_valuePtr = value;
}

void menu_item::set_int(int value)
{
	*(int*)m_valuePtr = value;
}

void menu_item::set_float(float value)
{
	*(float*)m_valuePtr = value;
}

menu_item& menu_item::set_tooltip(std::string name)
{
	if (name.size() >= 100) return *this;
	tooltip = name;
	return *this;
}

menu_item& menu_item::set_value(void* value)
{
	m_valuePtr = static_cast<menu_option*>(value);
	return *this;
}

menu_item& menu_item::set_type(menu_item_type option)
{
	m_OptionType = option;
	return *this;
}

menu_item& menu_item::set_callback(void(*callback)())
{
	m_OptionCallback = callback;
	return *this;
}

menu_item& menu_item::set_array(std::vector<std::string> array)
{
	if (array.size() == 0)
		return *this;

	m_OptionType = type_list;
	m_OptionDisplayed = array[0];
	m_OptionArray = array;
	return *this;
}

menu_item& menu_item::set_increment(float value)
{
	m_OptionType = type_float;
	m_OptionLimits.increment.data_float = value;
	return *this;
}

menu_item& menu_item::set_limits(float min, float max)
{
	if (m_valuePtr != nullptr)
		set_float(min);

	m_OptionLimits.mins.data_float = min;
	m_OptionLimits.maxs.data_float = max;
	return *this;
}

menu_item& menu_item::set_increment(int value)
{
	if (this->m_OptionType == type_none)
		this->m_OptionType = type_integer;

	m_OptionLimits.increment.data_int = value;
	return *this;
}

menu_item& menu_item::set_limits(int min, int max)
{
	if (m_valuePtr != nullptr)
		set_int(min);

	m_OptionLimits.mins.data_int = min;
	m_OptionLimits.maxs.data_int = max;
	return *this;
}

menu_item::~menu_item()
{
	memset(this, 0, sizeof * this);
}

