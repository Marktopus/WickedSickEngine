// ImGui Win32 + DirectX11 binding
// https://github.com/ocornut/imgui

struct ImDrawData;


// Use if you want to reset your rendering device without losing ImGui state.
void        DxImguiRender(ImDrawData* draw_data);
// Handler for Win32 messages, update mouse/keyboard data.
// You may or not need this for your implementation, but it can serve as reference for handling inputs.
// Commented out to avoid dragging dependencies on <windows.h> types. You can copy the extern declaration in your code.
/*
IMGUI_API LRESULT   ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
*/
