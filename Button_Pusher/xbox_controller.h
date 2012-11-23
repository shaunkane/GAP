// Code modded from: http://www.david-amador.com/2012/04/xbox-360-controller-input-in-c-via-xinput/

/*****************/
/* Pre-Processer */
/*****************/
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "XInput.lib")

const float MAX_VIBRATION = 65535.0f;
const float MAX_TRIGGER = 255.0f;

int PollController(HWND);

typedef enum
{
	PLAYER_ONE		= 0,
	PLAYER_TWO		= 1,
	PLAYER_THREE	= 2,
	PLAYER_FOUR		= 3
} PlayerIndex;

typedef enum
{
	CONTROLLER_DPAD_UP			= 0,
	CONTROLLER_DPAD_RIGHT		= 1,
	CONTROLLER_DPAD_DOWN		= 2,
	CONTROLLER_DPAD_LEFT		= 3,

	CONTROLLER_BUTTON_START		= 4,
	CONTROLLER_BUTTON_BACK		= 5,
	
	CONTROLLER_BUTTON_THUMB_L	= 6,
	CONTROLLER_BUTTON_THUMB_R	= 7,
	
	CONTROLLER_BUTTON_BUMPER_L	= 8,
	CONTROLLER_BUTTON_BUMPER_R	= 9,
	
	CONTROLLER_BUTTON_A			= 10,
	CONTROLLER_BUTTON_B			= 11,
	CONTROLLER_BUTTON_X			= 12,
	CONTROLLER_BUTTON_Y			= 13,

	// This is a cheap way to do "sizeof", I guess.
	CONTROLLER_BUTTON_MAX		= 14
} ControllerControl;

// Coordinates for ISO tracking. Quick and dirty.s
struct Vector2
{
	float _x;
	float _y;

	void set(float xVal, float yVal)
	{
		_x = xVal;
		_y = yVal;
	}
};

// Nice little package for when I poll the controller.
struct ControllerState
{
	bool _buttons[CONTROLLER_BUTTON_MAX];
	Vector2 _iso_l;
	Vector2 _iso_r;
	float _trigger_l;
	float _trigger_r;

	void reset()
	{
		for(int i = 0; i < (int) CONTROLLER_BUTTON_MAX; i++)
		{
			_buttons[i] = false;
		}

		_iso_l.set(0, 0);
		_iso_r.set(0, 0);
		_trigger_l = _trigger_l = 0;
	}
};

class XBoxController
{
public:
	/* Constructors */
	XBoxController(PlayerIndex);

	/* Members */
	ControllerState state;

	/* Methods */
	bool is_connected();
	void update();
	void vibrate(float, float);

private:
	XINPUT_STATE _controller_state;
	PlayerIndex _player_index;
};


