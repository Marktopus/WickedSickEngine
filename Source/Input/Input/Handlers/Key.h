
#pragma once

#include <windows.h>

namespace WickedSick
{

  ////////////////////////////////////////////////////////////
  /// \brief Key codes
  ///
  ////////////////////////////////////////////////////////////
  enum Key
  {
    Unknown = -1, ///< Unhandled key
    A = 0x41,        ///< The A key
    B = 0x42,            ///< The B key
    C = 0x43,            ///< The C key
    D = 0x44,            ///< The D key
    E = 0x45,            ///< The E key
    F = 0x46,            ///< The F key
    G = 0x47,            ///< The G key
    H = 0x48,            ///< The H key
    I = 0x49,            ///< The I key
    J = 0x4A,            ///< The J key
    K = 0x4B,            ///< The K key
    L = 0x4C,            ///< The L key
    M = 0x4D,            ///< The M key
    N = 0x4E,            ///< The N key
    O = 0x4F,            ///< The O key
    P = 0x50,            ///< The P key
    Q = 0x51,            ///< The Q key
    R = 0x52,            ///< The R key
    S = 0x53,            ///< The S key
    T = 0x54,            ///< The T key
    U = 0x55,            ///< The U key
    V = 0x56,            ///< The V key
    W = 0x57,            ///< The W key
    X = 0x58,            ///< The X key
    Y = 0x59,            ///< The Y key
    Z = 0x5A,            ///< The Z key
    Num0 = 0x30,         ///< The 0 key
    Num1 = 0x31,         ///< The 1 key
    Num2 = 0x32,         ///< The 2 key
    Num3 = 0x33,         ///< The 3 key
    Num4 = 0x34,         ///< The 4 key
    Num5 = 0x35,         ///< The 5 key
    Num6 = 0x36,         ///< The 6 key
    Num7 = 0x37,         ///< The 7 key
    Num8 = 0x38,         ///< The 8 key
    Num9 = 0x39,         ///< The 9 key
    Escape = VK_ESCAPE,       ///< The Escape key
    LControl = VK_CONTROL,     ///< The left Control key
    LShift = VK_SHIFT,       ///< The left Shift key
    LAlt = VK_MENU,         ///< The left Alt key
    LSystem = VK_LWIN,      ///< The left OS specific key
    RControl = VK_CONTROL,     ///< The right Control key
    RShift = VK_SHIFT,       ///< The right Shift key
    RAlt = VK_MENU,         ///< The right Alt key
    RSystem = VK_RWIN,      ///< The right OS specific key
    Menu = VK_MENU,         ///< The Menu key

    SemiColon = VK_OEM_1,    ///< The ; key
    Comma = VK_OEM_COMMA,        ///< The , key
    Period = VK_OEM_PERIOD,       ///< The . key
    Quote = VK_OEM_7,        ///< The ' key
    Slash = VK_DIVIDE,        ///< The / key
    BackSlash = VK_OEM_102,    ///< The \ key
    Tilde = VK_OEM_3,        ///< The ~ key

    Space = VK_SPACE,        ///< The Space key
    Return = VK_RETURN,       ///< The Return key
    BackSpace = VK_BACK,    ///< The Backspace key
    Tab = VK_TAB,          ///< The Tabulation key
    PageUp = VK_PRIOR,       ///< The Page up key
    PageDown = VK_NEXT,     ///< The Page down key
    End = VK_END,          ///< The End key
    Home = VK_HOME,         ///< The Home key
    Insert = VK_INSERT,       ///< The Insert key
    Delete = VK_DELETE,       ///< The Delete key
    Add = VK_ADD,          ///< The + key
    Subtract = VK_SUBTRACT,     ///< The - key
    Multiply = VK_MULTIPLY,     ///< The * key
    Divide = VK_DIVIDE,       ///< The / key
    Left = VK_LEFT,         ///< Left arrow
    Right = VK_RIGHT,        ///< Right arrow
    Up = VK_UP,           ///< Up arrow
    Down = VK_DOWN,         ///< Down arrow
    Numpad0 = VK_NUMPAD0,      ///< The numpad 0 key
    Numpad1 = VK_NUMPAD1,      ///< The numpad 1 key
    Numpad2 = VK_NUMPAD2,      ///< The numpad 2 key
    Numpad3 = VK_NUMPAD3,      ///< The numpad 3 key
    Numpad4 = VK_NUMPAD4,      ///< The numpad 4 key
    Numpad5 = VK_NUMPAD5,      ///< The numpad 5 key
    Numpad6 = VK_NUMPAD6,      ///< The numpad 6 key
    Numpad7 = VK_NUMPAD7,      ///< The numpad 7 key
    Numpad8 = VK_NUMPAD8,      ///< The numpad 8 key
    Numpad9 = VK_NUMPAD9,      ///< The numpad 9 key
    F1 = VK_F1,           ///< The F1 key
    F2 = VK_F2,           ///< The F2 key
    F3 = VK_F3,           ///< The F3 key
    F4 = VK_F4,           ///< The F4 key
    F5 = VK_F5,           ///< The F5 key
    F6 = VK_F6,           ///< The F6 key
    F7 = VK_F7,           ///< The F7 key
    F8 = VK_F8,           ///< The F8 key
    F9 = VK_F9,           ///< The F9 key
    F10 = VK_F10,          ///< The F10 key
    F11 = VK_F11,          ///< The F11 key
    F12 = VK_F12,          ///< The F12 key

    Pause = VK_PAUSE,        ///< The Pause key

    MouseLeft = VK_LBUTTON,
    MouseRight = VK_RBUTTON,
    MouseMiddle = VK_MBUTTON,

    KeyCount = VK_OEM_CLEAR      ///< Keep last -- the total number of keyboard keys
  };
}

