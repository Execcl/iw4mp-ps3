#include "stdafx.h"

timers::change_overtime g_change_overtime;

namespace timers
{
	unsigned int get_time_now()
	{
		return sys_time_get_system_time() / 1000;
	}

	void sleep(unsigned int ms)
	{
		sys_timer_usleep(ms * 1000);
	}

	value_timer::value_timer(float* from, float to, unsigned int duration, unsigned int startDelay)
		: f_from(from), f_to(to), i_duration(duration)
	{
		f_startValue = *from;
		i_startTime = get_time_now() + startDelay;
	}

	bool value_timer::is_finished()
	{
		return f_from == nullptr;
	}

	bool value_timer::is_same(float* from)
	{
		return f_from == from;
	}

	void value_timer::update()
	{
		if (!f_from)
			return;

		uint64_t timeNow = get_time_now();
		if (timeNow < i_startTime)
			return;

		if (timeNow >= i_startTime + i_duration)
		{
			*f_from = f_to;
			f_from = nullptr;
			return;
		}

		uint64_t timePassed = timeNow - i_startTime;
		float timeProgress = static_cast<float>(timePassed) / static_cast<float>(i_duration);
		float progress = (f_to - f_startValue) * timeProgress;

		*f_from = f_startValue + progress;
	}


	bool change_overtime::add(float* from, float to, unsigned int duration, unsigned int startDelay, bool ignoreCheck)
	{
		if (!ignoreCheck && already_exist(from))
			return false;

		for (int i = 0; i < max_value_timers; i++)
		{
			if (timers[i].is_finished())
			{
				timers[i] = value_timer(from, to, duration, startDelay);
				return true;
			}
		}
		return false;
	}

	bool change_overtime::add(vec2_t* from, vec2_t to, unsigned int duration, unsigned int startDelay, bool ignoreCheck)
	{
		float froms[2] = { from->x, from->y };
		float tos[2] = { to.x, to.y };

		for (int i = 0; i < 2; i++)
			if (!add(&froms[i], tos[i], duration, startDelay, ignoreCheck))
				return false;
		return true;
	}

	bool change_overtime::add(vec3_t* from, vec3_t to, unsigned int duration, unsigned int startDelay, bool ignoreCheck)
	{
		float froms[3] = { from->x, from->y, from->z };
		float tos[3] = { to.x, to.y, to.z };

		for (int i = 0; i < 3; i++)
			if (!add(&froms[i], tos[i], duration, startDelay, ignoreCheck))
				return false;
		return true;
	}

	bool change_overtime::add(vec4_t* from, vec4_t to, unsigned int duration, unsigned int startDelay, bool ignoreCheck)
	{
		float froms[4] = { from->x, from->y, from->z, from->w };
		float tos[4] = { to.x, to.y, to.z, to.w };

		for (int i = 0; i < 4; i++)
			if (!add(&froms[i], tos[i], duration, startDelay, ignoreCheck))
				return false;
		return true;
	}

	void change_overtime::update()
	{
		for (int i = 0; i < max_value_timers; i++)
			timers[i].update();
	}

	bool change_overtime::already_exist(float* from)
	{
		for (int i = 0; i < max_value_timers; i++)
		{
			if (timers[i].is_same(from))
				return true;
		}

		return false;
	}
}