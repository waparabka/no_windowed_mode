#include "plugin.h"


c_plugin::c_plugin() {

    using namespace std::placeholders;

    auto user32 = LoadLibraryA("User32.dll");

    if (user32) {

        set_window_long_hook.set_dest(reinterpret_cast<void*>(GetProcAddress(user32, "SetWindowLongA")));
        set_window_long_hook.set_cb(std::bind(&c_plugin::set_window_long_hooked, this, _1, _2, _3, _4));

        set_window_long_hook.install();
    }
}


LONG c_plugin::set_window_long_hooked(const decltype(set_window_long_hook)& hook, HWND hwnd, int index, LONG new_long) {

    if (index == GWL_STYLE)
        new_long = GetWindowLong(hwnd, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW;
    
    return hook.get_trampoline()(hwnd, index, new_long);
}


c_plugin::~c_plugin() {
    set_window_long_hook.remove();
}