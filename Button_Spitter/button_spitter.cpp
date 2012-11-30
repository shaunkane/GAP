// Code stolen and modded from: http://www.cplusplus.com/forum/beginner/19486/
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <tchar.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
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
	int in_hour = atoi(in_tme.substr(10, 11).c_str()) * 60 * 60 * 1000;
	int in_min = atoi(in_tme.substr(13, 14).c_str()) * 60 * 1000;
	int in_sec = atoi(in_tme.substr(16, 17).c_str()) * 1000;
	int in_mil = atoi(in_tme.substr(19, 24).c_str());

	return (in_hour + in_min + in_sec + in_mil);
}

vector<InputItem> ChewFile()
{
	vector<InputItem> in_controls;

	//string in_line;

	//int in_tme;
	//string in_str = "";
	//string in_val = 0;

	//string in_temp = "";

	//ifstream in_file;
	//in_file.open("C:\\Users\\Karim\ Said\\Desktop\\SMB.txt");

	//if(in_file.is_open())
	//{
	//	// This is ugly. 
	//	// How in the hello, world do you parse strings nicely in C++?!
	//	while(in_file.good() && in_file.eof() == false)
	//	{
	//		getline(in_file, in_line);

	//		int start_index = 0;
	//		int end_index = in_line.find(",", start_index);

	//		in_temp = in_line.substr(start_index, end_index);
	//		in_tme = ParseTime(in_temp);

	//		start_index = end_index + 1;
	//		end_index = in_line.find(",", start_index);
	//		in_str = in_line.substr(start_index, end_index);

	//		start_index = end_index;
	//		end_index = in_line.find(",", start_index);
	//		in_val = in_line.substr(start_index, end_index);

	//		InputItem itm(in_tme, in_str, in_val);

	//		in_controls.push_back(itm);
	//	}
	//}

	//in_file.close();

	return in_controls;
}

int main() 
{
	vector<InputItem> in_controls;

	in_controls = ChewFile();

	SetForegroundWindow(emu_window);
	
	for(int i = 0; i < in_controls.size(); i++)
	{
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
		
		if(i < in_controls.size() - 1)
		{	
			cout << in_controls[i].get_input_type();
			Sleep(in_controls[i + 1].get_input_time() - in_controls[i].get_input_time());
		}
	}

	return 0;
}