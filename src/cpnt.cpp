#include <iostream>
#include <map>
#include <string>
#include <cstdio>

//xoth42 Feb 6 base idea of project

using namespace std;

map<string, string> colors = {
	//basic colors to interpret input
	{"black",	"30"},
	{"red",		"31"},
	{"green",	"32"},
	{"yellow",	"33"},
	{"blue",	"34"},
	{"purple", 	"35"}
};

int parse(int argc, char **argv)
{
	/*
	Parse Command line arguments
	./cpnt [args] [color] [message]...
	
	nothing : [color] [message]...
	
	TODO:
	-r		: [rgb value ex=<###,###,###>] [message]...
	specify rgb color instead of color name

	-b		: [color] [message]...
	bold

	-u		: [color] [message]...
	underline
	*/

}

int main(int argc, char **argv) 
{
	string input = argv[1]; //color pre-interp
	string colornum;

	try {
	colornum = colors.at(input); 
	//color is valid
	}

	catch (out_of_range error) {
		cout << "\033[31mcolor is not valid: " << input << endl;
		return 1;
	}

	string message = argv[2];
	for (int i = 3; i < argc; i++) {
		//add all message contents
		message = message + " " + argv[i];
	}
	string format = "\033[" + colornum + "m"; //does the color
	
	//done with format, printing
	cout << format << message << endl;
	
}
