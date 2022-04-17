#include "stdafx.h"

menu* g_menu;

bool menu::is_open()
{
	return test_flags(open);
}

bool example_bool;
int example_data;
int example_int;
int example_intms;
float example_float;

void menu::on_build()
{
	m_maxViewableOptions = 10;

	auto m_rootMenu = new  menu_tab("Main");
	m_rootMenu->add_option("Bool Toggle Option").set_type(type_bool).set_value(&example_bool);

	m_rootMenu->add_option("Array Option").set_value(&example_data).set_array({"This", "Is", "An", "Array", "Option"});
	m_rootMenu->add_option("Int Slider Option").set_value(&example_int).set_type(type_integer).set_increment(1).set_limits(0, 100);
	m_rootMenu->add_option("Int ms Slider Option").set_value(&example_intms).set_type(type_integer_ms).set_increment(1).set_limits(0, 25);
	m_rootMenu->add_option("Float Slider Option").set_value(&example_float).set_type(type_float).set_increment(0.25f).set_limits(0.0f, 80.0f);
	m_rootMenu->add_option("Settings").set_type(type_menu);

	auto m_settingsMenu = new menu_tab("Settings");
	m_settingsMenu->add_option("Menu Width").set_value(&g_vars->menu.width).set_type(type_float).set_increment(0.25f).set_limits(300.0f, 400.0f);

	submenus.push_back(m_settingsMenu);
	menu_stack.push(m_rootMenu);
}

void menu::on_draw()
{
	component creator("Created by CrEaTiiOn_Zac & CrEaTiiOn_Faultz", 5, 5, 0.55f, 0.55f, 1.0f, 0, vec4_t(255, 255, 255, 255), vec4_t(208, 57, 163, 255), vec4_t(23, 25, 24, 255), g_vars->fonts.smallfont, g_vars->materials.white, align_left | border_all);

	creator.add();

	if (!is_open())
		return;

	if (this->menu_stack.empty())
		return;

	const auto m_menuTab = this->get_current();

	float m_fontScale = 0.75f;
	float m_textHeight = g_vars->fonts.smallfont->pixelHeight * m_fontScale;

	float m_cursorPos = m_menuTab->get_cursor() - m_menuTab->get_cursor_offset();
	float m_backgroundPos = m_menuTab->get_count() >= m_maxViewableOptions ? m_maxViewableOptions * m_textHeight : m_menuTab->get_count() * m_textHeight;

	
	vec4_t rectColor(208, 57, 163, 255);
	vec4_t scrollbarColor(44, 44, 43, 255);
	vec4_t backgroundColor(23, 25, 24, 255);
	vec4_t headerColor(38, 38, 38, 255);

	component header(g_vars->menu.x, g_vars->menu.y, g_vars->menu.width, 60, 1.0f, 0.0f, rectColor, headerColor, g_vars->materials.white, align_left | border_all);
	component background(g_vars->menu.x, g_vars->menu.y + 61, g_vars->menu.width, 4 + m_backgroundPos, 1.0f, 0.0f, rectColor, backgroundColor, g_vars->materials.white, align_left | border_left | border_right);
	component scrollbar(g_vars->menu.x + 2, g_vars->menu.y + 63 + m_cursorPos * m_textHeight, g_vars->menu.width - 3, m_textHeight, 0.0f, 0.0f, g_vars->global.emptyColor, scrollbarColor, g_vars->materials.white, align_left);
	component bottomHeader(g_vars->menu.x, g_vars->menu.y + 62 + 4 + m_backgroundPos, g_vars->menu.width, m_textHeight, 1.0f, 0.0f, rectColor, headerColor, g_vars->materials.white, align_left | border_all);
	component title("Menu Base", g_vars->menu.x + 5, g_vars->menu.y + 30 + 0 * g_vars->fonts.smallfont->pixelHeight * m_fontScale + 0.25f, m_fontScale + 0.25f, m_fontScale + 0.25f, 0.0f, 0, vec4_t(255, 255, 255, 255), g_vars->global.emptyColor, g_vars->fonts.smallfont, align_left | align_middle);
	component team("CrEaTiiOnBrotherhood", g_vars->menu.x + 5, g_vars->menu.y + 30 + 1 * g_vars->fonts.smallfont->pixelHeight * m_fontScale + 0.25f, m_fontScale - 0.25f, m_fontScale - 0.25f, 0.0f, 0, vec4_t(255, 255, 255, 255), g_vars->global.emptyColor, g_vars->fonts.smallfont, align_left | align_middle);

	header.add();
	background.add();
	scrollbar.add();
	bottomHeader.add();
	title.add();
	team.add();

	for (int i = 0; i < m_menuTab->get_count(); i++)
	{
		auto m_menuOption = m_menuTab->get_option(i);

		if (m_menuOption == nullptr)
			continue;

		if (i - m_menuTab->get_cursor_offset() >= 0 && i < m_menuTab->get_cursor_offset() + m_maxViewableOptions)
		{
			float m_optionSpacing = (i - m_menuTab->get_cursor_offset()) * m_textHeight;

			component options(m_menuOption->get_name(), g_vars->menu.x + 5, g_vars->menu.y + 81.50f + m_optionSpacing, m_fontScale, m_fontScale, 0.0f, 0, vec4_t(255, 255, 255, 255), g_vars->global.emptyColor, g_vars->fonts.smallfont, align_left);

			options.add();

			switch (m_menuOption->m_OptionType)
			{
			case type_bool:
			{
				if (m_menuOption->m_valuePtr != nullptr)
				{
					component toggleBackground(g_vars->menu.x + g_vars->menu.width - 5, g_vars->menu.y + 67.50f + m_textHeight / 4 + m_optionSpacing, m_textHeight - 8, m_textHeight - 8, 1.0f, 0.0f, rectColor, backgroundColor, g_vars->materials.white, align_right | align_middle | border_all);
					component toggle(g_vars->menu.x + g_vars->menu.width - 6, g_vars->menu.y + 67.50f + m_textHeight / 4 + m_optionSpacing, m_textHeight - 11, m_textHeight - 10, 0.0f, 0.0f, g_vars->global.emptyColor, vec4_t(255, 255, 255, 130), g_vars->materials.white, align_right | align_middle);

					toggleBackground.add();
					if(m_menuOption->get_bool())
						toggle.add();
				}
			}
			break;
			case type_integer:
				{
				float m_ilScale = (static_cast<float>(m_menuOption->get_int()) - static_cast<float>(m_menuOption->m_OptionLimits.mins.data_int)) / (static_cast<float>(m_menuOption->m_OptionLimits.maxs.data_int) - static_cast<float>(m_menuOption->m_OptionLimits.mins.data_int)) * 77;

					component integerSliderBackground(g_vars->menu.x + g_vars->menu.width - 5, g_vars->menu.y + 67.50f + m_textHeight / 4 + m_optionSpacing, 80, m_textHeight - 8, 1.0f, 0.0f, rectColor, backgroundColor, g_vars->materials.white, align_right | align_middle | border_all);
					component integerSlider(g_vars->menu.x + g_vars->menu.width - 83, g_vars->menu.y + 67.50f + m_textHeight / 4 + m_optionSpacing, m_ilScale, m_textHeight - 10, 0.0f, 0.0f, g_vars->global.emptyColor, vec4_t(255, 255, 255, 130), g_vars->materials.white, align_left | align_middle);
					component value(va("%i", m_menuOption->get_int()), g_vars->menu.x + g_vars->menu.width - 41, g_vars->menu.y + 81.50f - m_textHeight / 2 + 1.20 + m_optionSpacing, m_fontScale, m_fontScale - 0.35f, 0.0f, 0, vec4_t(255, 255, 255, 255), g_vars->global.emptyColor, g_vars->fonts.smallfont, align_center | align_middle);


					integerSliderBackground.add();
					integerSlider.add();
					value.add();

				}
				break;
			case type_integer_ms: 
				{
					float m_ilScale = (static_cast<float>(m_menuOption->get_int()) - static_cast<float>(m_menuOption->m_OptionLimits.mins.data_int)) / (static_cast<float>(m_menuOption->m_OptionLimits.maxs.data_int) - static_cast<float>(m_menuOption->m_OptionLimits.mins.data_int)) * 77;

					component integerSliderBackground(g_vars->menu.x + g_vars->menu.width - 5, g_vars->menu.y + 67.50f + m_textHeight / 4 + m_optionSpacing, 80, m_textHeight - 8, 1.0f, 0.0f, rectColor, backgroundColor, g_vars->materials.white, align_right | align_middle | border_all);
					component integerSlider(g_vars->menu.x + g_vars->menu.width - 83, g_vars->menu.y + 67.50f + m_textHeight / 4 + m_optionSpacing, m_ilScale, m_textHeight - 10, 0.0f, 0.0f, g_vars->global.emptyColor, vec4_t(255, 255, 255, 130), g_vars->materials.white, align_left | align_middle);
					component value(va("%i ms", m_menuOption->get_int()), g_vars->menu.x + g_vars->menu.width - 41, g_vars->menu.y + 81.50f - m_textHeight / 2 + 1.20 + m_optionSpacing, m_fontScale, m_fontScale - 0.35f, 0.0f, 0, vec4_t(255, 255, 255, 255),  g_vars->global.emptyColor, g_vars->fonts.smallfont, align_center | align_middle);

					integerSliderBackground.add();
					integerSlider.add();
					value.add();
				}
				break;
			case type_float:
			{
					float m_flScale = (m_menuOption->get_float() - m_menuOption->m_OptionLimits.mins.data_float) / (m_menuOption->m_OptionLimits.maxs.data_float - m_menuOption->m_OptionLimits.mins.data_float) * 77;

					component floatSliderBackground(g_vars->menu.x + g_vars->menu.width - 5, g_vars->menu.y + 67.50f + m_textHeight / 4 + m_optionSpacing, 80, m_textHeight - 8, 1.0f, 0.0f, rectColor, backgroundColor, g_vars->materials.white, align_right | align_middle | border_all);
					component floatSlider(g_vars->menu.x + g_vars->menu.width - 83, g_vars->menu.y + 67.50f + m_textHeight / 4 + m_optionSpacing, m_flScale, m_textHeight - 10, 0.0f, 0.0f, g_vars->global.emptyColor, vec4_t(255, 255, 255, 130), g_vars->materials.white, align_left | align_middle);
					component value(va("%.2f", m_menuOption->get_float()), g_vars->menu.x + g_vars->menu.width - 41, g_vars->menu.y + 81.50f - m_textHeight / 2 + 1.20 + m_optionSpacing, m_fontScale, m_fontScale - 0.35f, 0.0f, 0, vec4_t(255, 255, 255, 255), g_vars->global.emptyColor, g_vars->fonts.smallfont, align_center | align_middle);

					floatSliderBackground.add();
					floatSlider.add();
					value.add();
			}
			break;
			case type_menu:
				{
					component arrow(">", g_vars->menu.x + g_vars->menu.width - 5, g_vars->menu.y + 81.50f + m_optionSpacing, m_fontScale, m_fontScale, 0.0f, 0, vec4_t(255, 255, 255, 255), g_vars->global.emptyColor, g_vars->fonts.smallfont, align_right);

					arrow.add();
				}
				break;
			case type_list:
				{
					component list(m_menuOption->m_OptionArray[m_menuOption->get_int()], g_vars->menu.x + g_vars->menu.width - 5, g_vars->menu.y + 81.50f + m_optionSpacing, m_fontScale, m_fontScale, 0.0f, 6, vec4_t(255, 255, 255, 255), g_vars->global.emptyColor, g_vars->fonts.smallfont, align_right);

					list.add();
				}
				break;
			default: 
				
				break;
			}
		}
	}
}

void menu::on_run()
{
	if(is_open())
	{
		if(!check_variables())
			return;

		check_scrolling();
		check_events();
	}
	else
	{
		on_open();
	}
}

bool menu::check_variables()
{
	m_currentTab = get_current();
	if (m_currentTab == nullptr)
		return false;

	m_maxOptions = m_currentTab->get_count();

	m_currentItem = m_currentTab->get_option(m_currentTab->get_cursor());

	if (m_currentItem == nullptr)
		return false;

	return true;
}

void menu::on_trigger()
{
	if (m_currentItem->m_OptionType == type_bool && m_currentItem->m_valuePtr != nullptr)
	{
		m_currentItem->set_bool(m_currentItem->get_bool() ^ true);
	}

	if (m_currentItem->get_callback() != nullptr)
	{
		m_currentItem->get_callback()();
	}
	else if (m_currentItem->m_OptionType == type_menu)
	{
		auto* m_validMenu = find_menu(m_currentItem->get_name().c_str());
		if (m_validMenu == nullptr)
			return;

		if (m_validMenu->get_count() == 0)
		{
			printf("This menu is empty\n");
		}
		else
		{
			auto stack = menu_stack.top();

			menu_stack.push(m_validMenu);
			menu_stack.top()->set_parent(stack);
		}
	}

}

void menu::on_open()
{
	if (g_input.IsButtonBinds(CInput::BUTTON_R3, CInput::BUTTON_PAD_UP))
		set_flags(open);
}

void menu::on_close()
{
	remove_flags(open);
}

void menu::on_back()
{
	if (m_currentItem->m_OptionType == type_list)
	{
		m_currentItem->m_OptionActive = false;
	}
	else
	{
		if (menu_stack.size() > 1)
		{
			menu_stack.pop();
		}
		else
		{
			on_close();
		}
	}
}

void menu::check_events()
{
	if(g_input.IsButtonDown(CInput::BUTTON_CROSS, 400))
	{
		on_trigger();
	}
	if(g_input.IsButtonDown(CInput::BUTTON_CIRCLE, 400))
	{
		on_back();
	}
}

int menu::on_scroll_up()
{
	if (m_currentItem->m_OptionActive)
	{
		if (m_currentItem->m_OptionPosition <= 0)
			m_currentItem->m_OptionPosition = 0;
		else
			m_currentItem->m_OptionPosition = m_currentItem->m_OptionPosition - 1;
	}
	else
	{
		int m_Scroll = m_currentTab->get_cursor() - 1;
		if (m_Scroll < 0)
		{
			m_Scroll = m_maxOptions - 1;
			m_currentTab->set_cursor_offset(m_maxOptions - m_maxViewableOptions + 1);
			if (m_currentTab->get_cursor_offset() < 0)
				m_currentTab->set_cursor_offset(0);
		}
		if (m_currentTab->get_cursor_offset() > 0)
		{
			m_currentTab->set_cursor_offset(m_currentTab->get_cursor_offset() - 1);
		}

		m_currentTab->set_cursor(m_Scroll);

		return m_Scroll;
	}

	return 0;
}

int menu::on_scroll_down()
{
	if (m_currentItem->m_OptionActive)
	{
		if (m_currentItem->m_OptionPosition >= m_currentItem->m_OptionArray.size() - 1)
			m_currentItem->m_OptionPosition = m_currentItem->m_OptionArray.size() - 1;
		else
			m_currentItem->m_OptionPosition = m_currentItem->m_OptionPosition + 1;
	}
	else
	{
		int m_Scroll = m_currentTab->get_cursor() + 1;
		if (m_maxOptions > m_maxViewableOptions)
			if (m_Scroll >= m_maxViewableOptions)
				m_currentTab->set_cursor_offset(m_currentTab->get_cursor_offset() + 1);
		if (m_Scroll > m_maxOptions - 1)
		{
			m_Scroll = 0;
			if (m_maxOptions > m_maxViewableOptions)
			{
				m_currentTab->set_cursor_offset(0);
			}
		}

		m_currentTab->set_cursor(m_Scroll);

		return m_Scroll;
	}

	return 0;
}

void menu::on_scroll_left()
{
	if (m_currentItem->m_OptionType == type_integer)
	{
		m_currentItem->set_int(m_currentItem->get_int() - m_currentItem->m_OptionLimits.increment.data_int);
		if (m_currentItem->get_int() <= m_currentItem->m_OptionLimits.mins.data_int)
		{
			m_currentItem->set_int(m_currentItem->m_OptionLimits.mins.data_int);
		}
	}
	else if (m_currentItem->m_OptionType == type_integer_ms)
	{
		m_currentItem->set_int(m_currentItem->get_int() - m_currentItem->m_OptionLimits.increment.data_int);
		if (m_currentItem->get_int() <= m_currentItem->m_OptionLimits.mins.data_int)
		{
			m_currentItem->set_int(m_currentItem->m_OptionLimits.mins.data_int);
		}
	}
	else if (m_currentItem->m_OptionType == type_float)
	{
		m_currentItem->set_float(m_currentItem->get_float() - m_currentItem->m_OptionLimits.increment.data_float);
		if (m_currentItem->get_float() <= m_currentItem->m_OptionLimits.mins.data_float)
		{
			m_currentItem->set_float(m_currentItem->m_OptionLimits.mins.data_float);
		}
	}
	else if (m_currentItem->m_OptionType == type_list)
	{
		int pos = m_currentItem->get_int() - 1;
		if (pos <= m_currentItem->m_OptionLimits.mins.data_int)
		{
			pos = m_currentItem->m_OptionLimits.mins.data_int;
		}

		m_currentItem->set_int(pos);
	}
}

void menu::on_scroll_right()
{
	if (m_currentItem->m_OptionType == type_integer)
	{
		m_currentItem->set_int(m_currentItem->get_int() + m_currentItem->m_OptionLimits.increment.data_int);
		if (m_currentItem->get_int() >= m_currentItem->m_OptionLimits.maxs.data_int)
		{
			m_currentItem->set_int(m_currentItem->m_OptionLimits.maxs.data_int);
		}
	}
	else if (m_currentItem->m_OptionType == type_integer_ms)
	{
		m_currentItem->set_int(m_currentItem->get_int() + m_currentItem->m_OptionLimits.increment.data_int);
		if (m_currentItem->get_int() >= m_currentItem->m_OptionLimits.maxs.data_int)
		{
			m_currentItem->set_int(m_currentItem->m_OptionLimits.maxs.data_int);
		}
	}
	else if (m_currentItem->m_OptionType == type_float)
	{
		m_currentItem->set_float(m_currentItem->get_float() + m_currentItem->m_OptionLimits.increment.data_float);
		if (m_currentItem->get_float() >= m_currentItem->m_OptionLimits.maxs.data_float)
		{
			m_currentItem->set_float(m_currentItem->m_OptionLimits.maxs.data_float);
		}
	}
	else if (m_currentItem->m_OptionType == type_list)
	{
		if (m_currentItem->get_int() >= m_currentItem->m_OptionArray.size() - 1)
			m_currentItem->set_int(m_currentItem->m_OptionArray.size() - 1);
		else
			m_currentItem->set_int(m_currentItem->get_int() + 1);
	}
}

void menu::check_scrolling()
{
	if (g_input.IsButtonDown(CInput::BUTTON_PAD_UP, 200))
	{
		on_scroll_up();
	}
	else if (g_input.IsButtonDown(CInput::BUTTON_PAD_DOWN, 200))
	{
		on_scroll_down();
	}
	else if (g_input.IsButtonDown(CInput::BUTTON_PAD_LEFT, m_currentItem->m_OptionType == type_list ? 200 : 0))
	{
		on_scroll_left();
	}
	else if (g_input.IsButtonDown(CInput::BUTTON_PAD_RIGHT, m_currentItem->m_OptionType == type_list ? 200 : 0))
	{
		on_scroll_right();
	}
}