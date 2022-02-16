#include <iostream>
#include <map>
#include <string>
#include <cstdio>

//xoth42 Feb 6 base idea of project

using namespace std;

string format = "";

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
	char str1 = '-';
	string args = argv[2];
	if (str1 != argv[2][0]){
		cout << 0 << endl;
		return 0;
	}

	//there is a '-' in the second arg (arguments given)
	args = args.substr(1, args.length());
	//'args' is now only the arguments ex) 'ub'
	char bold = 'b';
	if (args.find(bold) != std::string::npos){
		format = "\033[1m";
	}
	char italic = 'i';
	if (args.find(italic) != std::string::npos){
		format = format + "\e[3m";
	}

	
	/*
	Parse Command line arguments
	./cpnt [args] [color] [message]...
	
	nothing : [color] [message]...
	
	TODO:
	-r		: [rgb value ex=<###,###,###>] [message]...
	specify rgb color instead of color name

	

	-u		: [color] [message]...
	underline
	*/
	return 1;
}

int main(int argc, char **argv) 
{
	string input = argv[2]; //color pre-interp
	if (parse(argc, argv) == 1){
		//bold
		try{
		input = argv[3];
		}
		catch (out_of_range error){
			//no more args
		}
	}
	
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
	format = format + "\033[" + colornum + "m"; //does the color
	
	//done with format, printing
	cout << format << message << endl;
	
}
