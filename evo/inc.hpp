#pragma once
#pragma warning ( disable : 4005 )
#pragma warning ( disable : 26495 )
#pragma warning ( disable : 4244 )
#pragma warning ( disable : 4715 )
#pragma warning ( disable : 4018 )
#pragma warning ( disable : 4244 )

#include <windows.h>
#include <windowsx.h>
#include <memory>
#include <sstream>
#include <iostream>
#include <functional>
#include <WinUser.h>
#include <string_view>
#include <map>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <deque>
#include <mutex>
#include <optional>
#include <filesystem>
#include <fstream>
#include <random>
#include <array>
#include <mutex>

/* directx includes */
#include <d3d11.h>
#include <D3D11.h>

/* libs for directx */
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3D11.lib")

#include "thirdparty/imgui.h"
#include "thirdparty/imgui_impl_win32.h"
#include "thirdparty/imgui_impl_dx9.h"
#include "thirdparty/imgui_impl_dx11.h"

#define ext_draw_list ImGui::GetBackgroundDrawList( )
#define read_data_dbg
#define print_with_data(s) std::cout << "[evo-debug] " + s << std::endl;
#define print_with_data_scoped(s) std::cout << "[evo-debug] " + std::string(s) << std::endl;

/* inc */
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

#include "sdk/math/color_t.hpp"
#include "sdk/math/rect_t.hpp"
#include "sdk/math/str_t.hpp"
#include "sdk/math/vec2_t.hpp"

#include "sdk/process_manager/process_manager.hpp"
#include "sdk/memory/mem.hpp"
#include "sdk/offsets/offsets.hpp"
#include "core/ctx/ctx.hpp"

#include "sdk/classes/entity.hpp"

#include "hacks/ctx/hacks_ctx.hpp"
#include "framework/framework.hpp"

/* resources */
#define IDS_APP_TITLE 103
#define IDR_MAINFRAME 128
#define IDD_GUITEST_DIALOG 102
#define IDD_ABOUTBOX 103
#define IDM_ABOUT 104
#define IDM_EXIT 105
#define IDI_GUITEST 107
#define IDI_SMALL 108
#define IDC_GUITEST 109
#define IDC_MYICON 2
#ifndef IDC_STATIC
#define IDC_STATIC -1
#endif

#define ALPHA    ( ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )
#define NO_ALPHA ( ImGuiColorEditFlags_NoTooltip    | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )