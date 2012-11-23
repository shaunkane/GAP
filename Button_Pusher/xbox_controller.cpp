#include "xbox_controller.h"

XBoxController::XBoxController(PlayerIndex player = PLAYER_ONE)
{
	_player_index = player;
	state.reset();
}

bool XBoxController::is_connected()
{
		// Clean the state.
		memset(&_controller_state, 0, sizeof(XINPUT_STATE));

		// Get the state.
		DWORD result = XInputGetState(_player_index, &_controller_state);

		if(result == ERROR_SUCCESS)
		{
			return true;
		}
		else
		{
			return false;
		}
}

void XBoxController::update()
{
		state.reset();

		// The values of L and R Triggers go from 0 to 255.
		if(_controller_state.Gamepad.bRightTrigger && _controller_state.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			state._trigger_r = _controller_state.Gamepad.bRightTrigger / MAX_TRIGGER;
		}
		if(_controller_state.Gamepad.bLeftTrigger && _controller_state.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			state._trigger_l = _controller_state.Gamepad.bLeftTrigger / MAX_TRIGGER;
		}

		// Get the buttons.
		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_A) state._buttons[CONTROLLER_BUTTON_A] = true;
		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_B) state._buttons[CONTROLLER_BUTTON_B] = true;
		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_X) state._buttons[CONTROLLER_BUTTON_X] = true;
		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) state._buttons[CONTROLLER_BUTTON_Y] = true;

		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) state._buttons[CONTROLLER_DPAD_DOWN] = true;
		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) state._buttons[CONTROLLER_DPAD_UP] = true;
		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) state._buttons[CONTROLLER_DPAD_LEFT] = true;
		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) state._buttons[CONTROLLER_DPAD_RIGHT] = true;

		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_START) state._buttons[CONTROLLER_BUTTON_START] = true;
		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) state._buttons[CONTROLLER_BUTTON_BACK] = true;

		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) state._buttons[CONTROLLER_BUTTON_THUMB_L] = true;
		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) state._buttons[CONTROLLER_BUTTON_THUMB_R] = true;

		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) state._buttons[CONTROLLER_BUTTON_BUMPER_L] = true;
		if(_controller_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) state._buttons[CONTROLLER_BUTTON_BUMPER_R] = true;

		// Checking ISO dead zones.
		if((_controller_state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			_controller_state.Gamepad.sThumbLX > -1 * XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			_controller_state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			_controller_state.Gamepad.sThumbLY > -1 * XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{
			_controller_state.Gamepad.sThumbLX = 0;
			_controller_state.Gamepad.sThumbLY = 0;
		}

		// Update ISO positions.
		float isoLeftY = _controller_state.Gamepad.sThumbLY;
		if(isoLeftY)
		{
			state._iso_l._y = isoLeftY;
		}
		float isoLeftX = _controller_state.Gamepad.sThumbLX;
		if(isoLeftX)
		{
			state._iso_l._x = isoLeftX;
		}

		float isoRightY = _controller_state.Gamepad.sThumbRY;
		if(isoRightY)
		{
			state._iso_r._y = isoRightY;
		}
		float isoRightX = _controller_state.Gamepad.sThumbRX;
		if(isoRightX)
		{
			state._iso_r._x = isoRightX;
		}
}

void XBoxController::vibrate(float motorL = 0.0f, float motorR = 0.0f)
{
		// Create new vibration.
		XINPUT_VIBRATION vibration;

		memset(&vibration, 0, sizeof(XINPUT_VIBRATION));

		int vibrationL = (int)(motorL * MAX_VIBRATION);
		int vibrationR = (int)(motorR * MAX_VIBRATION);

		// Set the vibration values.
		vibration.wLeftMotorSpeed = vibrationL;
		vibration.wRightMotorSpeed = vibrationR;

		// Vibrate the controller.
		XInputSetState((int)_player_index, &vibration);
}

int PollController(HWND hWnd)
{
	return 0;
}