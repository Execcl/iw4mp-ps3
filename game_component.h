#pragma once

#define isFlagSet(bit, flag) (((bit) & (flag)) == (flag))

enum RenderFlags : short
{
	align_left = 1 << 1,
	align_right = 1 << 2,
	align_center = 1 << 3,
	align_top = 1 << 4,
	align_bottom = 1 << 5,
	align_middle = 1 << 6,

	border_left = 1 << 7,
	border_right = 1 << 8,
	border_top = 1 << 9,
	border_bottom = 1 << 10,
	border_all = border_left | border_right | border_top | border_bottom,
};

class component
{
public:
	void add();

	component(float x, float y, float width, float height, float thickness, float rotation, const float* rectColor, const float* shadowColor, Material* material, short flags) : x(x), y(y), width(width), height(height), thickness(thickness), rotation(rotation), flags(flags), rectColor(rectColor), shadowColor(shadowColor), material(material) {}
	component(std::string string, float x, float y, float xScale, float yScale, float rotation, float style, const float* stringColor,const float* shadowColor, Font_s* font, short flags) : x(x), y(y), xScale(xScale), yScale(yScale), rotation(rotation), style(style), flags(flags), string(string), stringColor(stringColor), shadowColor(shadowColor), font(font) {}
	component(std::string string, float x, float y, float xScale, float yScale, float thickness, float style, const float* stringColor, const float* rectColor, const float* shadowColor, Font_s* font, Material* material, short flags) : x(x), y(y), xScale(xScale), yScale(yScale), thickness(thickness), style(style), flags(flags), string(string), stringColor(stringColor), rectColor(rectColor), shadowColor(shadowColor), material(material), font(font) {}

private:
	float x = 0.0f;
	float y = 0.0f;
	float width = 0.0f;
	float height = 0.0f;
	float thickness = 0.0f;
	float xScale = 0.0f;
	float yScale = 0.0f;
	float rotation = 0.0f;
	int style = 0;

	short flags;

	std::string string;

	const float* stringColor = vec4_t(0.0f, 0.0f, 0.0f, 0.0f);
	const float* rectColor = vec4_t(0.0f, 0.0f, 0.0f, 0.0f);
	const float* shadowColor = vec4_t(0.0f, 0.0f, 0.0f, 0.0f);
	const float* lineColor = vec4_t(0.0f, 0.0f, 0.0f, 0.0f);

	Material* material = nullptr;
	Font_s* font = nullptr;

	void transform_color(const float* color, float output[4]);
	void set_align(int type, float& width, float& height, unsigned short flags);
};


