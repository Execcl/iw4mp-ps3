#pragma once

struct variables
{
	struct
	{
		float x = 5;
		float y = 250;
		float width = 350;

		const float* rectColor = vec4_t(0, 0, 0, 255);

		int m_Design;
	}menu;

	struct
	{
		const float* emptyColor = vec4_t(0, 0, 0, 0);
	}global;

	struct
	{
		Font_s* smallfont = R_RegisterFont("smallfont");
		Font_s* normalfont = R_RegisterFont("normalfont");
	}fonts;

	struct
	{
		Material* white = Material_Register("white");
	}materials;
};

extern variables* g_vars;