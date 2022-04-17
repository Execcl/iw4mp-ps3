#pragma once

namespace timers
{
	unsigned int get_time_now();
	void sleep(unsigned int ms);

	constexpr int max_value_timers = 20;
	class value_timer
	{
	public:
		value_timer() {}
		value_timer(float* from, float to, unsigned int duration, unsigned int startDelay);

		bool is_finished();
		bool is_same(float* from);
		void update();

	private:
		float* f_from;
		float f_startValue;
		float f_to;
		unsigned int i_startTime;
		unsigned int i_duration;
	};

	class change_overtime
	{
	public:
		change_overtime() = default;
		bool add(float* from, float to, unsigned int duration, unsigned int startDelay = 0, bool ignoreCheck = false);
		bool add(vec2_t* from, vec2_t to, unsigned int duration, unsigned int startDelay = 0, bool ignoreCheck = false);
		bool add(vec3_t* from, vec3_t to, unsigned int duration, unsigned int startDelay = 0, bool ignoreCheck = false);
		bool add(vec4_t* from, vec4_t to, unsigned int duration, unsigned int startDelay = 0, bool ignoreCheck = false);
		void update();

	private:
		bool already_exist(float* from);

	private:
		value_timer timers[max_value_timers];
	};
}
extern timers::change_overtime g_change_overtime;