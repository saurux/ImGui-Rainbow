#pragma once
#include <Windows.h>

static bool RainbowMode = false;

float RED = 225.f / 255.f;
float GREEN = 0.f;
float BLUE = 80.0f / 255.f;

static float SPEED = 0.1f;

static float BRIGHT = 0.75f;

void RealTimeColor()
{
	if (RainbowMode)
	{
		static float Color[3];
		static DWORD Tickcount = 0;
		static DWORD Tickcheck = 0;
		ImGui::ColorConvertRGBtoHSV(RED, GREEN, BLUE, Color[0], Color[1], Color[2]);
		if (GetTickCount() - Tickcount >= 1)
		{
			if (Tickcheck != Tickcount)
			{
				Color[0] += 0.001f * SPEED;
				Tickcheck = Tickcount;
			}
			Tickcount = GetTickCount();
		}
		if (Color[0] < 0.0f) Color[0] += 1.0f;
		ImGui::ColorConvertHSVtoRGB(Color[0], Color[1], Color[2], RED, GREEN, BLUE);
	}
}

bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format)
{
	//ImGui::PushItemWidth(-1);
	char str[256];
	//sprintf(str, "##%s", label);
	const bool value_changed = ImGui::SliderFloat(label, v, v_min, v_max, format);
	//ImGui::PopItemWidth();
	return value_changed;
}