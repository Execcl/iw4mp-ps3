#include "stdafx.h"

Material* Material_Register(std::string name)
{
	int unk[4];
	DB_FindXAssetHeader(unk, ASSET_TYPE_MATERIAL, name.c_str());
	return reinterpret_cast<Material*>(unk[0]);
}

Font_s* R_RegisterFont(std::string name)
{
	int unk[4];
	std::string font = "fonts/" + name;
	DB_FindXAssetHeader(unk, ASSET_TYPE_FONT, font.c_str());
	return reinterpret_cast<Font_s*>(unk[0]);
}