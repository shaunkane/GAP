#include <Windows.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class InputItem
{
public:
	InputItem(int, string, string);

	int get_input_time();
	string get_input_type();
	string get_input_value();
	
	void set_input_time(int);
	void set_input_type(string);
	void set_input_value(string);
	
private:
	int input_time;
	string input_type;
	string input_value;
};