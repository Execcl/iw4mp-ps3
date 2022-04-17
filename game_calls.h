#pragma once

static libpsutil::symbol<void(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float* color, Material* material)> R_AddCmdDrawStretchPic{ static_cast<int>(game_table::r_addcmddrawstretchpic) };
static libpsutil::symbol<void(ScreenPlacement* scrPlace, float x, float y, float width, float height, float angle, const float* color, Material* material)> CG_DrawRotatedPicPhysical{ static_cast<int>(game_table::cg_drawrotatedpicphysical) };
static libpsutil::symbol<void(const char* text, unsigned int maxChars, Font_s* font, float x, float y, float xScale, float yScale, float rotation, const float* color, int style)> R_AddCmdDrawText{ static_cast<int>(game_table::r_addcmddrawtext) };
static libpsutil::symbol <int(int* unk, XAssetType type, const char* name) > DB_FindXAssetHeader{ static_cast<int>(game_table::db_findxassetheader) };
static libpsutil::symbol<int(const char* text, int maxChars, Font_s* font)> R_TextWidth{ static_cast<int>(game_table::r_textwidth) };
static libpsutil::symbol<const char*(const char* format, ...)> va{ static_cast<int>(game_table::va) };