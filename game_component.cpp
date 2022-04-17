#include "stdafx.h"

void component::add()
{
	if(this->string.empty())
	{
		if (this->rotation == 0.0f)
		{
			set_align(0, this->width, this->height, this->flags);
			float shadowColorOutput[4];
			transform_color(this->shadowColor, shadowColorOutput);

			if(this->material != nullptr)
				R_AddCmdDrawStretchPic(this->x, this->y, this->width, this->height, 0.0f, 0.0f, 1.0f, 1.0f, shadowColorOutput, this->material);

			if(this->rectColor != g_vars->global.emptyColor && this->thickness != 0.0f)
			{
				if (isFlagSet(flags, RenderFlags::border_left))
				{
					float rectColorOutput[4];
					transform_color(this->rectColor, rectColorOutput);
					R_AddCmdDrawStretchPic(this->x, this->y - this->thickness, this->thickness, this->height + this->thickness * 2, 0, 0, 1, 1, rectColorOutput, this->material);
				}
				if (isFlagSet(flags, RenderFlags::border_right))
				{
					float rectColorOutput[4];
					transform_color(this->rectColor, rectColorOutput);
					R_AddCmdDrawStretchPic(this->x + this->width, this->y - this->thickness, this->thickness, this->height + this->thickness * 2, 0, 0, 1, 1, rectColorOutput, this->material);
				}
				if (isFlagSet(flags, RenderFlags::border_top))
				{
					float rectColorOutput[4];
					transform_color(this->rectColor, rectColorOutput);
					R_AddCmdDrawStretchPic(this->x, this->y - this->thickness, this->width, this->thickness, 0, 0, 1, 1, rectColorOutput, this->material);
				}
				if (isFlagSet(flags, RenderFlags::border_bottom))
				{
					float rectColorOutput[4];
					transform_color(this->rectColor, rectColorOutput);
					R_AddCmdDrawStretchPic(this->x, this->y + this->height, this->width, this->thickness, 0, 0, 1, 1, rectColorOutput, this->material);
				}
			}
		}
	}
	else
	{
		if(this->shadowColor == g_vars->global.emptyColor)
		{
			float textWidth = static_cast<float>(R_TextWidth(this->string.c_str(), this->string.length(), this->font)) * this->xScale;
			float textHeight = static_cast<float>(this->font->pixelHeight) * this->yScale;
			set_align(1, textWidth, textHeight, this->flags);

			float stringColorOutput[4];
			transform_color(this->stringColor, stringColorOutput);
			R_AddCmdDrawText(this->string.c_str(), this->string.length(), this->font, this->x, this->y, this->xScale, this->yScale, this->rotation, stringColorOutput, this->style);
		}
		else
		{
			float textWidth = static_cast<float>(R_TextWidth(this->string.c_str(), this->string.length(), this->font)) * this->xScale;
			float textHeight = static_cast<float>(this->font->pixelHeight) * this->yScale;

			set_align(1, textWidth, textHeight, this->flags);
			set_align(0, textWidth, textHeight, this->flags);


			float shadowColorOutput[4];
			float stringColorOutput[4];
			transform_color(this->shadowColor, shadowColorOutput);
			transform_color(this->stringColor, stringColorOutput);

			R_AddCmdDrawStretchPic(this->x, this->y , textWidth + 6, textHeight + 4, 0.0f, 0.0f, 1.0f, 1.0f, shadowColorOutput, this->material);
			R_AddCmdDrawText(this->string.c_str(), this->string.length(), this->font, this->x + 3, this->y + textHeight + 2 / 2, this->xScale, this->yScale, this->rotation, stringColorOutput, this->style);

			if (this->rectColor != g_vars->global.emptyColor && this->thickness != 0.0f)
			{
				if (isFlagSet(flags, RenderFlags::border_left))
				{
					float rectColorOutput[4];
					transform_color(this->rectColor, rectColorOutput);
					R_AddCmdDrawStretchPic(this->x, this->y - this->thickness, this->thickness, textHeight + 4 + this->thickness * 2, 0, 0, 1, 1, rectColorOutput, this->material);
				}
				if (isFlagSet(flags, RenderFlags::border_right))
				{
					float rectColorOutput[4];
					transform_color(this->rectColor, rectColorOutput);
					R_AddCmdDrawStretchPic(this->x + textWidth + 6, this->y - this->thickness, this->thickness, textHeight + 4 + this->thickness * 2, 0, 0, 1, 1, rectColorOutput, this->material);
				}
				if (isFlagSet(flags, RenderFlags::border_top))
				{
					float rectColorOutput[4];
					transform_color(this->rectColor, rectColorOutput);
					R_AddCmdDrawStretchPic(this->x, this->y - this->thickness, textWidth + 6, this->thickness, 0, 0, 1, 1, rectColorOutput, this->material);
				}
				if (isFlagSet(flags, RenderFlags::border_bottom))
				{
					float rectColorOutput[4];
					transform_color(this->rectColor, rectColorOutput);
					R_AddCmdDrawStretchPic(this->x, this->y + textHeight + 4, textWidth + 6, this->thickness, 0, 0, 1, 1, rectColorOutput, this->material);
				}
			}
		}
	}
}

void component::transform_color(const float* color, float output[4])
{
	output[0] = color[0] > 1.0f ? color[0] * 0.0039215689f : color[0];
	output[1] = color[1] > 1.0f ? color[1] * 0.0039215689f : color[1];
	output[2] = color[2] > 1.0f ? color[2] * 0.0039215689f : color[2];
	output[3] = color[3] > 1.0f ? color[3] * 0.0039215689f : color[3];
}

void component::set_align(int type, float& width, float& height, unsigned short flags)
{
	if (isFlagSet(flags, RenderFlags::align_right))
		this->x -= width;
	if (isFlagSet(flags, RenderFlags::align_center))
		this->x -= width * 0.5f;
	if (isFlagSet(flags, RenderFlags::align_top))
		type == 0 ? 0 : this->y += height;
	if (isFlagSet(flags, RenderFlags::align_bottom) && type == 0)
		this->y -= height;
	if (isFlagSet(flags, RenderFlags::align_middle))
		type == 0 ? this->y -= height * 0.5f : this->y += height * 0.5f;
}
