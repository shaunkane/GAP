#include "input_item.h"

InputItem::InputItem(int in_tme = 0, string in_str = "", string in_val = "")
{
	set_input_time(in_tme);
	set_input_type(in_str);
	set_input_value(in_val);
}

int InputItem::get_input_time()
{
	return input_time;
}

string InputItem::get_input_type()
{
	return input_type;
}

string InputItem::get_input_value()
{
	return input_value;
}

void InputItem::set_input_time(int in_tme)
{
	input_time = in_tme;
}

void InputItem::set_input_type(string in_str)
{
	input_type = in_str;
}

void InputItem::set_input_value(string in_val)
{
	input_value = in_val;
}