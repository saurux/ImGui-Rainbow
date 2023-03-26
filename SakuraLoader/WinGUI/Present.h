#pragma once
#include "Sprites.h"
#include "../Sakura/Sakura.h"

static bool bIsOpen = true;
ImVec2 ButtonSize = ImVec2(160, 60); // w, h
static int Tab = 0;
ID3D11ShaderResourceView* pTexture = NULL;
int WarfaceX = 0;
int WarfaceY = 0;

ImVec4 RGBAToImVec4(float r, float g, float b, float a)
{
	return ImVec4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

template <typename T>
T FindPercent(T x, T y)
{
	T result = (x * y) / 100;
	return result;
}

void PaintGui()
{
	//static const ImWchar icon_ranges[] = { ICON_MIN, ICON_MAX, 0 };
	//io.Fonts->AddFontFromMemoryTTF(OPI, sizeof(OPI), 17, &config, icon_ranges);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	pFont = io.Fonts->AddFontFromFileTTF("Intro.otf", 18, 0, io.Fonts->GetGlyphRangesCyrillic());

	ImGui::GetIO().IniFilename = NULL;// "pussy.ini";

	ImGui::GetStyle().FrameRounding = 1.5f;
	ImGui::GetStyle().GrabRounding = 1.5f;
	ImGui::GetStyle().WindowRounding = 1.0f;
	ImGui::GetStyle().WindowBorderSize = 2.5f;
	ImGui::GetStyle().ChildBorderSize = 2.5f;
	ImGui::GetStyle().PopupBorderSize = 2.5f;
	ImGui::GetStyle().WindowTitleAlign.x = 0.50f;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = RGBAToImVec4(255.f, 255.f, 255.f, 255.f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
	colors[ImGuiCol_WindowBg] = RGBAToImVec4(35.f, 2.f, 85.f, 50.f); // Background
	colors[ImGuiCol_ChildBg] = RGBAToImVec4(0.f, 0.f, 0.f, 56.f);
	colors[ImGuiCol_PopupBg] = RGBAToImVec4(53.f, 0.f, 138.f, 50.f);
	colors[ImGuiCol_Border] = RGBAToImVec4(225.f, 0.f, 82.f, 255.f);
	colors[ImGuiCol_BorderShadow] = ImVec4(225.f, 0.00f, 0.00f, 255.00f);
	colors[ImGuiCol_FrameBg] = RGBAToImVec4(7.f, 0.f, 255.f, 255.f); // marks , sliders background
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.10f, 0.10f, 0.10f, 0.77f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.10f, 0.10f, 0.10f, 0.80f);
	colors[ImGuiCol_TitleBg] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_TitleBgActive] = RGBAToImVec4(225.f, 0.f, 82.f, 255.f); // Main Title -> 
	colors[ImGuiCol_TitleBgCollapsed] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_MenuBarBg] = RGBAToImVec4(217.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_ScrollbarBg] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_ScrollbarGrab] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_ScrollbarGrabHovered] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_ScrollbarGrabActive] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_CheckMark] = RGBAToImVec4(255.f, 255.f, 255.f, 255.f);
	colors[ImGuiCol_SliderGrab] = RGBAToImVec4(255.f, 255.f, 255.f, 155.f);
	colors[ImGuiCol_SliderGrabActive] = RGBAToImVec4(255.f, 255.f, 255.f, 255.f);
	colors[ImGuiCol_Button] = RGBAToImVec4(225.f, 0.f, 82.f, 225.f);
	colors[ImGuiCol_ButtonHovered] = RGBAToImVec4(225.f, 255.f, 255.f, 10.f);
	colors[ImGuiCol_ButtonActive] = RGBAToImVec4(225.f, 255.f, 255.f, 15.f);
	colors[ImGuiCol_Header] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_HeaderHovered] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_HeaderActive] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_Separator] = RGBAToImVec4(53.f, 0.f, 138.f, 50.f);
	colors[ImGuiCol_SeparatorHovered] = RGBAToImVec4(53.f, 0.f, 138.f, 50.f);
	colors[ImGuiCol_SeparatorActive] = RGBAToImVec4(53.f, 0.f, 138.f, 50.f);
	colors[ImGuiCol_ResizeGrip] = RGBAToImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ResizeGripHovered] = RGBAToImVec4(225.f, 0.f, 80.f, 205.f);
	colors[ImGuiCol_ResizeGripActive] = RGBAToImVec4(225.f, 0.f, 80.f, 255.f);
	colors[ImGuiCol_Tab] = RGBAToImVec4(0.f, 0.f, 255.f, 190.f);
	colors[ImGuiCol_TabHovered] = RGBAToImVec4(157.f, 0.f, 255.f, 140.f);
	colors[ImGuiCol_TabActive] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_TabUnfocused] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_TabUnfocusedActive] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_PlotLines] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_PlotLinesHovered] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_PlotHistogram] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_PlotHistogramHovered] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_TextSelectedBg] = RGBAToImVec4(54.f, 54.f, 54.f, 95.f);
	colors[ImGuiCol_DragDropTarget] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_NavHighlight] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_NavWindowingHighlight] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_NavWindowingDimBg] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
	colors[ImGuiCol_ModalWindowDimBg] = RGBAToImVec4(157.f, 0.f, 255.f, 255.f);
}

void Present()
{
	//SkrCheckData();

	ImGui::SetNextWindowPos(ImVec2(22.5f, 1.5f));
	ImGui::SetNextWindowSize(ImVec2(Width - 23, Height - 55));

	float ColorHSV[3];
	float ColorFloat;
	ImGui::ColorConvertRGBtoHSV(RED, GREEN, BLUE, ColorHSV[0], ColorHSV[1], ColorHSV[2]);
	ColorFloat = ColorHSV[0];

	if (RainbowMode)
	{
		RealTimeColor();
		for (int i = 0; i < 64; i++)
		{
			ColorFloat += 1.0f / 64.0f;
			if (ColorFloat > 1.0f)
				ColorFloat -= 1.0f;
		}
	}

	//ImGui::PushStyleColor(ImGuiCol_Border, RainbowMode ? (ImVec4)ImColor::HSV(ColorFloat, ColorHSV[1], ColorHSV[2]) : RGBAToImVec4(225.f, 0.f, 82.f, 255.f));
	ImGui::PushStyleColor(ImGuiCol_Button, RainbowMode ? (ImVec4)ImColor::HSV(ColorFloat, ColorHSV[1], BRIGHT) : ImVec4(RED, GREEN, BLUE, 255.f));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, RainbowMode ? (ImVec4)ImColor::HSV(ColorFloat, ColorHSV[1], BRIGHT) : ImVec4(RED, GREEN, BLUE, 255.f));
	ImGui::PushStyleColor(ImGuiCol_Border, RainbowMode ? (ImVec4)ImColor::HSV(ColorFloat, ColorHSV[1], BRIGHT) : ImVec4(RED, GREEN, BLUE, 255.f));
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, RainbowMode ? (ImVec4)ImColor::HSV(ColorFloat, ColorHSV[1], BRIGHT) : ImVec4(RED, GREEN, BLUE, 255.f));
	ImGui::Begin("Sakura Launcher", &bIsOpen);
	ImGui::PopStyleColor();

	ImGui::BeginChild(u8"Меню", ImVec2(Width - (FindPercent(Width, 75)), Height - 95), true);

	if(ImGui::Button("Warface", ButtonSize)) Tab == 1 ? Tab = 0 : Tab = 1;
	if(ImGui::Button("Apex Legends", ButtonSize)) Tab == 2 ? Tab = 0 : Tab = 2;
	if(ImGui::Button("Fortnite", ButtonSize)) Tab == 3 ? Tab = 0 : Tab = 3;
	if(ImGui::Button(u8"Опции", ButtonSize)) Tab == 4 ? Tab = 0 : Tab = 4;

	ImGui::EndChild();
	
	if (Tab == 1)
	{
		ImGui::SetCursorPos(ImVec2(Width - FindPercent(Width, 65) + 30, -15));
		ImVec4 ImageColorNet(255, 255, 255, 255);
		ImGui::Image((void*)pTexture, ImVec2(300, 300), ImVec2(0, 0), ImVec2(1, 1), ImageColorNet);

		ImGui::SetCursorPos(ImVec2(Width - FindPercent(Width, 75) + 20, 240));
		if (ImGui::Button(u8"Запустить", ImVec2(470, 45)))
		{
			// Inject software
		}

		ImGui::SetCursorPos(ImVec2(Width - FindPercent(Width, 75) + 20, 290));
		if (ImGui::Checkbox(u8"Manual Map Method", &Sakura::IsMMap))
		{
			Sakura::IsSWH = false;
		}
		ImGui::SameLine();
		if (ImGui::Checkbox(u8"SWH Method", &Sakura::IsSWH))
		{
			Sakura::IsMMap = false;
		}
	}

	if (Tab == 4) // Options
	{
		ImGui::SetCursorPos(ImVec2(Width - FindPercent(Width, 75) + 20, 35));
		ImGui::Checkbox("Rainbow Mode", &RainbowMode);

		if (RainbowMode)
		{
			ImGui::SetCursorPos(ImVec2(Width - FindPercent(Width, 75) + 20, 65));
			SliderFloat(u8"S", &SPEED, 0.1f, 10.f, "%.1f");
			ImGui::SetCursorPos(ImVec2(Width - FindPercent(Width, 75) + 20, 95));
			SliderFloat(u8"V", &BRIGHT, 0.0f, 1.f, "%.2f");
		}

		float color[3];
		color[0] = RED, color[1] = GREEN, color[2] = BLUE;
		ImGui::SetCursorPos(ImVec2(Width - FindPercent(Width, 75) + 20, RainbowMode ? 125 : 65));
		ImGui::ColorEdit4("##1", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoAlpha);
		RED = color[0], GREEN = color[1], BLUE = color[2];
	}


	ImGui::End();
}