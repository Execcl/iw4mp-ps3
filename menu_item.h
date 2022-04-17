#pragma once

enum menu_item_type {
	type_none,
	type_integer,
	type_integer_ms,
	type_float,
	type_spacer,
	type_bool,
	type_list,
	type_menu,
	type_func,
};

union menu_item_limit {
	int data_int;
	float data_float;
};

struct menu_item_limits {
public:
	menu_item_limit mins;
	menu_item_limit maxs;
	menu_item_limit increment;
};

union menu_option
{
	float data_bool;
	float data_float;
	int data_int;
	vec4_t* data_color;
};

class menu_item {
public:
	menu_item_type m_OptionType;

	// void data
	void(*m_OptionCallback)();

	// option data
	menu_option* m_valuePtr;

	// slider data
	menu_item_limits m_OptionLimits;

	// array data
	std::vector<std::string> m_OptionArray;
	std::string m_OptionDisplayed;
	float m_OptionSize;
	short m_OptionPosition;
	bool m_OptionActive;

	std::string get_tooltip();
	std::string get_name();
	bool get_bool();
	int get_int();
	float get_float();
	void(*get_callback())();

	void set_bool(bool value);
	void set_int(int value);
	void set_float(float value);

	menu_item();
	menu_item(const char* Name);

	menu_item& set_tooltip(std::string name);
	menu_item& set_value(void* value);
	menu_item& set_type(menu_item_type option = type_func);
	menu_item& set_callback(void(*callback)());
	menu_item& set_array(std::vector<std::string> array);

	menu_item& set_increment(float value);
	menu_item& set_limits(float min, float max);

	menu_item& set_increment(int value);
	menu_item& set_limits(int min, int max);

	~menu_item();
private:
	std::string tooltip;
	std::string name;
};