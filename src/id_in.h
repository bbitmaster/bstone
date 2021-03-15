/*
BStone: A Source port of
Blake Stone: Aliens of Gold and Blake Stone: Planet Strike

Copyright (c) 1992-2013 Apogee Entertainment, LLC
Copyright (c) 2013-2021 Boris I. Bendovsky (bibendovsky@hotmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the
Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/


//
//      ID Engine
//      ID_IN.h - Header file for Input Manager
//      v1.0d1
//      By Jason Blochowiak
//


#ifndef BSTONE_ID_IN_INCLUDED
#define BSTONE_ID_IN_INCLUDED


#ifdef  __DEBUG__
#define __DEBUG_InputMgr__
#endif

#include <cstdint>
#include <bitset>

#ifdef __vita__
#include "SDL.h"
void TranslateControllerEvent(SDL_Event *ev);
void TranslateTouchEvent(SDL_Event *ev);
void TranslateAnalogEvent(SDL_Event *ev);
#endif

#define MaxPlayers 4
#define MaxKbds 2
#define NumCodes 256

enum class ScanCode
{
	sc_none = 0,

	sc_return = 0x1C,
	sc_escape = 0x01,
	sc_space = 0x39,
	sc_minus = 0x0C,
	sc_equals = 0x0D,
	sc_backspace = 0x0E,
	sc_tab = 0x0F,
	sc_alt = 0x38,
	sc_left_bracket = 0x1A,
	sc_right_bracket = 0x1B,
	sc_control = 0x1D,
	sc_caps_lock = 0x3A,
	sc_num_lock = 0x45,
	sc_scroll_lock = 0x46,
	sc_left_shift = 0x2A,
	sc_right_shift = 0x36,
	sc_up_arrow = 0x48,
	sc_down_arrow = 0x50,
	sc_left_arrow = 0x4B,
	sc_right_arrow = 0x4D,
	sc_insert = 0x52,
	sc_delete = 0x53,
	sc_home = 0x47,
	sc_end = 0x4F,
	sc_page_up = 0x49,
	sc_page_down = 0x51,
	sc_slash = 0x35,
	sc_f1 = 0x3B,
	sc_f2 = 0x3C,
	sc_f3 = 0x3D,
	sc_f4 = 0x3E,
	sc_f5 = 0x3F,
	sc_f6 = 0x40,
	sc_f7 = 0x41,
	sc_f8 = 0x42,
	sc_f9 = 0x43,
	sc_f10 = 0x44,
	sc_f11 = 0x57,
	sc_f12 = 0x59,
	sc_print_screen = 0x37,
	sc_pause = 0x54,
	sc_back_quote = 0x29,
	sc_semicolon = 0x27,
	sc_quote = 0x28,
	sc_backslash = 0x2B,
	sc_comma = 0x33,
	sc_period = 0x34,

	sc_1 = 0x02,
	sc_2 = 0x03,
	sc_3 = 0x04,
	sc_4 = 0x05,
	sc_5 = 0x06,
	sc_6 = 0x07,
	sc_7 = 0x08,
	sc_8 = 0x09,
	sc_9 = 0x0a,
	sc_0 = 0x0b,

	sc_a = 0x1E,
	sc_b = 0x30,
	sc_c = 0x2E,
	sc_d = 0x20,
	sc_e = 0x12,
	sc_f = 0x21,
	sc_g = 0x22,
	sc_h = 0x23,
	sc_i = 0x17,
	sc_j = 0x24,
	sc_k = 0x25,
	sc_l = 0x26,
	sc_m = 0x32,
	sc_n = 0x31,
	sc_o = 0x18,
	sc_p = 0x19,
	sc_q = 0x10,
	sc_r = 0x13,
	sc_s = 0x1F,
	sc_t = 0x14,
	sc_u = 0x16,
	sc_v = 0x2F,
	sc_w = 0x11,
	sc_x = 0x2D,
	sc_y = 0x15,
	sc_z = 0x2C,

	sc_kp_minus = 0x4A,
	sc_kp_plus = 0x4E,

	sc_mouse_left = 0x64,
	sc_mouse_middle = 0x65,
	sc_mouse_right = 0x66,
	sc_mouse_x1 = 0x67,
	sc_mouse_x2 = 0x68,

	sc_mouse_wheel_down = 0x69,
	sc_mouse_wheel_up = 0x6A,

	sc_joy_axis0_up   = 0x80,
	sc_joy_axis0_down = 0x81,
	sc_joy_axis1_up = 0x82,
	sc_joy_axis1_down = 0x83,
	sc_joy_axis2_up = 0x84,
	sc_joy_axis2_down = 0x85,
	sc_joy_axis3_up = 0x86,
	sc_joy_axis3_down = 0x87,
	sc_joy_axis4_up = 0x88,
	sc_joy_axis4_down = 0x89,
	sc_joy_axis5_up = 0x8a,
	sc_joy_axis5_down = 0x8b,
	sc_joy_axis6_up = 0x8c,
	sc_joy_axis6_down = 0x8d,
	sc_joy_btn0 = 0x90,
	sc_joy_btn1 = 0x91,
	sc_joy_btn2 = 0x92,
	sc_joy_btn3 = 0x93,
	sc_joy_btn4 = 0x94,
	sc_joy_btn5 = 0x95,
	sc_joy_btn6 = 0x96,
	sc_joy_btn7 = 0x97,
	sc_joy_btn8 = 0x98,
	sc_joy_btn9 = 0x99,
	sc_joy_btn10 = 0x9a,
	sc_joy_btn11 = 0x9b,
	sc_joy_btn12 = 0x9c,
	sc_joy_btn13 = 0x9d,
	sc_joy_btn14 = 0x9e,
	sc_joy_btn15 = 0x9f,
	sc_joy_btn16 = 0xa0,
	sc_joy_btn17 = 0xa1,
	sc_joy_btn18 = 0xa2,
	sc_joy_btn19 = 0xa3,
	sc_joy_btn20 = 0xa4,
	sc_joy_btn21 = 0xa5,
	sc_joy_btn22 = 0xa6,
	sc_joy_btn23 = 0xa7,
	sc_joy_btn24 = 0xa8,
	sc_joy_btn25 = 0xa9,
	sc_joy_btn26 = 0xaa,
	sc_joy_btn27 = 0xab,
	sc_joy_btn28 = 0xac,
	sc_joy_btn29 = 0xad,
	sc_joy_btn30 = 0xae,
	sc_joy_btn31 = 0xaf
}; // ScanCode

#define key_None 0
#define key_Return 0x0d
#define key_Enter key_Return
#define key_Escape 0x1b
#define key_Space 0x20
#define key_BackSpace 0x08
#define key_Tab 0x09
#define key_Delete 0x7f
#define key_UnderScore 0x0c

//      Stuff for the mouse
#define MReset 0
#define MButtons 3
#define MDelta 11

#define MouseInt 0x33


enum Demo
{
	demo_Off,
	demo_Record,
	demo_Playback,
	demo_PlayDone
}; // Demo

enum ControlType
{
	ctrl_None, // JAM - added
	ctrl_Keyboard,
	ctrl_Keyboard1 = ctrl_Keyboard,
	ctrl_Keyboard2,
	ctrl_Mouse
}; // ControlType

enum Motion
{
	motion_Left = -1,
	motion_Up = -1,
	motion_None = 0,
	motion_Right = 1,
	motion_Down = 1
}; // Motion

enum Direction
{
	dir_North,
	dir_NorthEast,
	dir_East,
	dir_SouthEast,
	dir_South,
	dir_SouthWest,
	dir_West,
	dir_NorthWest,
	dir_None
}; // Direction

// BBi
enum BindingId
{
	e_bi_forward,
	e_bi_backward,
	e_bi_left,
	e_bi_right,
	e_bi_strafe,
	e_bi_strafe_left,
	e_bi_strafe_right,
	e_bi_quick_left,
	e_bi_quick_right,
	e_bi_turn_around,
	e_bi_run,

	e_bi_attack,
	e_bi_weapon_1,
	e_bi_weapon_2,
	e_bi_weapon_3,
	e_bi_weapon_4,
	e_bi_weapon_5,
	e_bi_weapon_6,
	e_bi_weapon_7,

	e_bi_use,

	e_bi_stats,
	e_bi_radar_magnify,
	e_bi_radar_minify,

	e_bi_help,
	e_bi_save,
	e_bi_load,
	e_bi_sound,
	e_bi_controls,
	e_bi_end_game,
	e_bi_quick_save,
	e_bi_quick_load,
	e_bi_quick_exit,

	e_bi_attack_info,
	e_bi_lightning,
	e_bi_sfx,
	e_bi_music,
	e_bi_ceiling,
	e_bi_flooring,
	e_bi_heart_beat,

	e_bi_pause,
	e_bi_grab_mouse,

	e_bi_cycle_previous_weapon,
	e_bi_cycle_next_weapon,

	e_bi_last_entry,
}; // BindingId

const int k_max_binding_keys = 3;
const int k_max_bindings = e_bi_last_entry;

using Binding = ScanCode[k_max_binding_keys];
using Bindings = Binding[k_max_bindings];

extern Bindings in_bindings;

const int k_max_joystick_axes = 6;
extern int in_joy_deadzone[k_max_joystick_axes];
extern int in_joy_sensitivity[k_max_joystick_axes];

extern int JoyNumAxes;
extern int JoyNumButtons;

extern std::bitset<NumCodes> jstate;

extern SDL_GameController* GameController;
extern SDL_Joystick* Joystick;

void in_set_default_bindings();

struct CursorInfo
{
	int button0;
	int button1;
	int button2;
	int button3;
	int x;
	int y;
	Motion xaxis;
	Motion yaxis;
	Direction dir;
}; //  CursorInfo

using ControlInfo = CursorInfo;

struct KeyboardDef
{
	ScanCode button0;
	ScanCode button1;
	ScanCode upleft;
	ScanCode up;
	ScanCode upright;
	ScanCode left;
	ScanCode right;
	ScanCode downleft;
	ScanCode down;
	ScanCode downright;
}; // KeyboardDef


//==========================================================================
//
// clamp
//
// Clamps in to the range [min,max].
//==========================================================================

template<class T>
inline
T clamp(const T in, const T min, const T max)
{
	return in <= min ? min : in >= max ? max : in;
}

// Global variables

class KeyboardState
{
private:
	using State = std::bitset<NumCodes>;


public:
	State::reference operator[](
		const int index)
	{
		return state_[index];
	}

	State::reference operator[](
		const ScanCode scan_code)
	{
		return state_[static_cast<std::size_t>(scan_code)];
	}

	void reset()
	{
		state_.reset();
	}

private:
	State state_;
}; // KeyboardState

extern ControlType ControlTypeUsed; // JAM - added
extern KeyboardState Keyboard;
extern bool MousePresent;
extern bool Paused;
extern char LastASCII;
extern ScanCode LastScan;
extern KeyboardDef KbdDefs;
extern ControlType Controls[MaxPlayers];

extern std::uint8_t* DemoBuffer;
extern std::uint16_t DemoOffset, DemoSize;

extern bool allcaps;

// Function prototypes
#define IN_KeyDown(code) (Keyboard[(code)])
#define IN_ClearKey(code) { Keyboard[code] = false; \
                            if (code == LastScan) { LastScan = ScanCode::sc_none; } }

// DEBUG - put names in prototypes
void init_joystick_gamepad();
void IN_Startup();
void IN_Shutdown();

int IN_JoyButtons(bool& bt_esc);
void IN_GetJoyDelta(int* dx, int* dy);
int IN_GetJoyAxis(int axis);
void UpdateRawJoystickAxis(void);
void PollJoystickButton(void);

void IN_ClearKeysDown();
void IN_ReadCursor(CursorInfo*);
void IN_ReadControl(std::int16_t, ControlInfo*);
void IN_SetControlType(std::int16_t, ControlType);

void IN_Ack();

extern bool IN_UserInput(
	std::uint32_t delay);
extern char IN_WaitForASCII();
extern const std::string& IN_GetScanName(ScanCode);


std::uint8_t IN_MouseButtons();


// BBi
extern bool in_is_mouse_grabbed;

bool in_grab_mouse(
	bool grab);


void in_handle_events();

void in_get_mouse_deltas(
	int& dx,
	int& dy);

void in_clear_mouse_deltas();

bool in_is_binding_pressed(
	BindingId binding_id);

void in_reset_binding_state(
	BindingId binding_id);

void in_reset_state();
// BBi


#endif // BSTONE_ID_IN_INCLUDED
