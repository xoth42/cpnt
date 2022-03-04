#include <iostream>
#include <map>
#include <string>
#include <cstdio>

//xoth42 Feb 6 base idea of project

using namespace std;

map<string, string> colors = {
	//basic colors to interpret input (placeholder)
	{"black",	"30"},
	{"red",		"31"},
	{"green",	"32"},
	{"yellow",	"33"},
	{"blue",	"34"},
	{"purple", 	"35"}
};

string parse(int argc, char **argv)
{
	/*
	Parse Command line arguments
	./cpnt [optional-args] [color] [message]...
	
	arguments start with - and should be grouped 
	ex) ./cpnt -biu {etc}
	order does not matter
	
	u	: underline
	b	: bold
	i	: italic

	returns:
	no arguments	: "0"
	arguments found : [value of attributes] ex) "1;21;3"
	
	
	TODO:
	-r		: [rgb value ex=<###,###,###>] [message]...
	specify rgb color instead of color name

	may add more return values, for now it changes the format string in the scope outside of the function
	escape sequences info: 
	http://www.techpository.com/linux-terminal-control-commands/
	https://www.systutorials.com/docs/linux/man/4-console_codes/
	^
	"It is generally not good practice to hard-wire terminal controls into programs. 
	Linux supports a terminfo(5) database of terminal capabilities. Rather than emitting console escape
	sequences by hand, you will almost always want to use a terminfo-aware screen library or utility
	such as ncurses(3), tput(1), or reset(1)."
	tput is a viable option - just need to know how to use it
	*/
	
	//check if argument contains enough characters, and if comma is the first character given as argument
	//if not, return "0"
	if (argc < 2 || '-' != argv[1][0]){
		return "0";
	}

	//if so, continue

	string attributes = ""; //to contain excape sequence attributes (colors/formatting) 
	//example value) 4;1; <-- should turn into "\[4;1;43m" down the line and then eventually
	//make the output into: underscore (4), bold (1), and color added later: a yellow backround (43) 

	//iterate through char locations from the first to last char in the argument
	for (int i = 1;i < argc - 1;i++){
		switch (argv[1][i])
		{
		case 'b':
			//bold
			attributes+= "1;";
			break;
		
		case 'u':
			//underline
			attributes+= "21;";
			break;

		// case 'i':
		// 	//italic
		// 	attributes+= "3;"; //this might not be correct
		// 	break;	
		//(it wasnt, but easy fix: find escape sequence for italic which i'll do later)
		
		default:
			break;
		}
	}

	return attributes;
}

int main(int argc, char **argv) 
{
	string input = argv[1]; //color pre-interp
	int messageIndex = 2; //to tell message forming loop where to start
	string attrib = parse(argc, argv);
	if ((string("0").compare(attrib)) != 0){
		//arguments detected (output is not 0) this feels inefficient 
		input = argv[2]; //the color input is past the arguments
		messageIndex++;
	}
	
	string colornum;

	try {
	colornum = colors.at(input); //the escape sequence value of the color
	//color is valid
	}

	catch (out_of_range error) {
		cout << "\033[31mcolor is not valid: " << input << endl;
		return 1;
	}

	//message forming loop
	string message = argv[messageIndex];
	for (int i = messageIndex + 1; i < argc; i++) {
		//add all message contents
		message = message + " " + argv[i];
	}
	
	//done with format, printing (apply attributes and color)
	cout << "\033[" + attrib + colornum + "m" << message << endl;
	
}
