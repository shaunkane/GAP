// Code stolen and modded from: http://www.cplusplus.com/forum/beginner/19486/
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#include "input_item.h"

using namespace std;

/* HWND = "Window Handle" */
LPCWSTR window_name = _T("Snes9x rerecording 1.51 v7");
HWND emu_window = FindWindow(0, window_name);

void PressKey(int vk, BOOL vk_ext) 
{    
	KEYBDINPUT kb = {0};
	INPUT input = {0};

	/* Generate a "Key Down" */
	if (vk_ext) 
	{
		kb.dwFlags = KEYEVENTF_EXTENDEDKEY;
	}

	kb.wVk  = vk;
	input.type  = INPUT_KEYBOARD;
	input.ki  = kb;
	SendInput(1, &input, sizeof(input));

	return;
}

void ReleaseKey(int vk, BOOL vk_ext)
{
	KEYBDINPUT kb = {0};
	INPUT input = {0};

	/* Generate a "Key Up" */
	ZeroMemory(&kb, sizeof(KEYBDINPUT));
	ZeroMemory(&input, sizeof(INPUT));
	kb.dwFlags  =  KEYEVENTF_KEYUP;
	
	if (vk_ext) 
	{
		kb.dwFlags |= KEYEVENTF_EXTENDEDKEY;
	}

	kb.wVk = vk;
	input.type = INPUT_KEYBOARD;
	input.ki = kb;
	SendInput(1, &input, sizeof(input));

	return;
}

int ParseTime(string in_tme)
{
	cout << in_tme.substr(11, 2) << " ";
	int in_hour = atoi(in_tme.substr(11, 2).c_str()) * 60 * 60 * 1000;
	cout << in_tme.substr(14, 2) << " ";
	int in_min = atoi(in_tme.substr(14, 2).c_str()) * 60 * 1000;
	cout << in_tme.substr(17, 2) << " ";
	int in_sec = atoi(in_tme.substr(17, 2).c_str()) * 1000;
	cout << in_tme.substr(20, 3) << " ";
	int in_mil = atoi(in_tme.substr(20, 3).c_str());

	return (in_hour + in_min + in_sec + in_mil);
}

vector<InputItem> ChewFile()
{
	cout << "Chewing those yummy buttons!" << endl;
	vector<InputItem> in_controls;
	string in_line;

	int in_tme = 0;
	string in_str = "";
	string in_val = "";

	string in_temp = "";
	
	ifstream in_file;

	in_file.open("C:/Users/Karim Said/Desktop/SMB.txt", ios::in);
	
	if(in_file.is_open())
	{
		getline(in_file, in_line); // Oh man, it's been a while. I need to initialize the line buffer. Hehe.
		// This is ugly. 
		// How in the hello, world do you parse strings nicely in C++?!
		while(in_file.good() && in_file.eof() == false)
		{
			cout << in_line << endl;

			int start_index = 0;
			int end_index = in_line.find(",", start_index);
			
			in_temp = in_line.substr(start_index, end_index - start_index);
			cout << in_temp << endl;
			in_tme = ParseTime(in_temp);
			cout << in_tme << endl;

			start_index = end_index + 1;
			end_index = in_line.find(",", start_index);
			in_str = in_line.substr(start_index, end_index - start_index);
			cout << in_str << endl;

			start_index = end_index + 1;
			end_index = in_line.find(",", start_index);
			in_val = in_line.substr(start_index, end_index - start_index);
			cout << in_val << endl << endl;

			InputItem itm(in_tme, in_str, in_val);

			cout << in_controls.size() << endl;
			in_controls.push_back(itm);
			
			getline(in_file, in_line);
		}
	}

	in_file.close();

	return in_controls;
}

int main() 
{
	vector<InputItem> in_controls;

	in_controls = ChewFile();

	SetForegroundWindow(emu_window);
	
	cout << "Spitting Hot Buttons!" << endl;

	for(int i = 0; i < in_controls.size(); i++)
	{
		cout << "Input Index: " << i << endl;
		cout << in_controls[i].get_input_type() << " " << in_controls[i].get_input_value() << endl;

		if(in_controls[i].get_input_type() == "JOYBUTTONDOWN")
		{
			if(in_controls[i].get_input_value() == "A Button")
			{
				// S
				PressKey(0x53, false);
			}
			else if(in_controls[i].get_input_value() == "B Button")
			{
				// D
				PressKey(0x44, false);
			}
			else if(in_controls[i].get_input_value() == "X Button")
			{
				// W
				PressKey(0x57, false);
			}
			else if(in_controls[i].get_input_value() == "Y Button")
			{
				// A
				PressKey(0x41, false);
			}
		}
		else if(in_controls[i].get_input_type() == "JOYBUTTONUP")
		{
			if(in_controls[i].get_input_value() == "A Button")
			{
				// S
				ReleaseKey(0x53, false);
			}
			else if(in_controls[i].get_input_value() == "B Button")
			{
				// D
				ReleaseKey(0x44, false);
			}
			else if(in_controls[i].get_input_value() == "X Button")
			{
				// W
				ReleaseKey(0x57, false);
			}
			else if(in_controls[i].get_input_value() == "Y Button")
			{
				// A
				ReleaseKey(0x41, false);
			}
		}
		else if(in_controls[i].get_input_type() == "JOYHATMOTION")
		{
			if(in_controls[i].get_input_value() == "Left"|| in_controls[i].get_input_value() == "Top Left" || in_controls[i].get_input_value() == "Bottom Left" )
			{
				PressKey(VK_LEFT, false);
				ReleaseKey(VK_RIGHT, false);

				if(in_controls[i].get_input_value() == "Top Left")
				{
					PressKey(VK_UP, false);
					ReleaseKey(VK_DOWN, false);
				}
				else if(in_controls[i].get_input_value() == "Bottom Left")
				{
					PressKey(VK_DOWN, false);
					ReleaseKey(VK_UP, false);
				}
			}
			else if(in_controls[i].get_input_value() == "Right" || in_controls[i].get_input_value() == "Top Right" || in_controls[i].get_input_value() == "Bottom Right")
			{
				PressKey(VK_RIGHT, false);
				ReleaseKey(VK_LEFT, false);

				if(in_controls[i].get_input_value() == "Top Right")
				{
					PressKey(VK_UP, false);
					ReleaseKey(VK_DOWN, false);
				}
				else if(in_controls[i].get_input_value() == "Bottom Right")
				{
					PressKey(VK_DOWN, false);
					ReleaseKey(VK_UP, false);
				}
			}
			else if(in_controls[i].get_input_value() == "Top Center")
			{
				PressKey(VK_UP, false);
				ReleaseKey(VK_RIGHT, false);
				ReleaseKey(VK_LEFT, false);
				ReleaseKey(VK_DOWN, false);
			}
			else if(in_controls[i].get_input_value() == "Bottom Center")
			{
				PressKey(VK_DOWN, false);
				ReleaseKey(VK_RIGHT, false);
				ReleaseKey(VK_LEFT, false);
				ReleaseKey(VK_UP, false);
			}
			else if(in_controls[i].get_input_value() == "Center")
			{
				ReleaseKey(VK_DOWN, false);
				ReleaseKey(VK_RIGHT, false);
				ReleaseKey(VK_LEFT, false);
				ReleaseKey(VK_UP, false);
			}
		}
		if(i < in_controls.size() - 1)
		{
			int sleep_time = in_controls[i + 1].get_input_time() - in_controls[i].get_input_time();
			cout << "Sleeping for: " << sleep_time << " milliseconds" << endl;
			Sleep(sleep_time);
		}
	}

	return 0;
}