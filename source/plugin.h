#pragma once

#include <windows.h>
#include <cstdint>
#include <filesystem>
#include <algorithm>
#include <map>

#include <kthook/kthook.hpp>

using set_window_long_t = LONG(__stdcall*)(HWND, int, LONG);


class c_plugin {
public:
	c_plugin();
	~c_plugin();
	
	kthook::kthook_simple<set_window_long_t> set_window_long_hook { };
	LONG set_window_long_hooked(const decltype(set_window_long_hook)& hook, HWND hwnd, int index, LONG new_long);
};
