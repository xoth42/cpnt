#include <iostream>
#include <map>
#include <string>
#include <cstdio>
#include <cstring>

// xoth42 Feb 6 base idea of project

using namespace std;

map<string, string> colors = {
	// basic colors to interpret input (placeholder)
	{"black",	"30"},
	{"red",		"31"},
	{"green",	"32"},
	{"yellow",	"33"},
	{"blue",	"34"},
	{"purple", 	"35"}
};

string S_lower(string s){
	/*
	returns lowercase version of string
	*/
	string s2 = s;
	for (int i = 0;i < s.length();i++){
		// see if its uppercase
		if (s[i] > 65 && s[i] < 90){
			// make lowercase
			s2[i] = s2[i] + 32;
		}
	}
	return s2;
}

string check_color(string input){
	/*
	returns color escape seq. num if input is valid, "37" if not 37 is the escape sequence for white terminal lettering
	*/
	try{
		return colors.at(S_lower(input)); // the escape sequence value of the color
		// color is valid
	}

	catch (exception bad_color){
		// no color or unrecognized color provided
		return "37"; 
	}
}


string parse(int argc, char **argv)
{
	/*
	Parse Command line arguments
	./cpnt [args] [color] (message)...
	
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
	
	//check if argument contains enough characters or if comma is the first character given as argument
	//if not, return "0"
	if (argc < 2 | '-' != argv[1][0]){
		//cout << argc << argv << endl;
		return "0";
	}

	//if so, continue

	string attributes = ""; //to contain escape sequence attributes (colors/formatting) 
	//example value) 4;1; <-- should turn into "\[4;1;43m" down the line and then eventually
	//make the output into: underscore (4), bold (1), and color added later: a yellow backround (43) 

	//iterate through char locations from the first to last char in the argument
	string args = S_lower(argv[1]);
	for (int i = 1;i <= args.size();i++){
		try{
		
			if (args[i] == 'b'){
				//bold
				attributes =  attributes + "1;";
			}
			if (args[i] == 'u'){
				//underline
				attributes = attributes + "21;";
			}	
		}

		catch (exception parse_err){
			//cout << i << args.size() << args << endl;
		}
	}
	return attributes;
}


int main(int argc, char **argv) 
{
	string input;
	try {
		try{
			input = argv[1]; // color pre-interp
		}

		catch(out_of_range error){
			cout << "\033[31mMissing arguments or message" << endl;
			return 1;
		}

		int messageIndex = 1; 	// to tell message forming loop where to start. Will jump values depending on if:

		string attrib = ""; // attributes for formatting

		try{	
			attrib = parse(argc, argv);
		}

		catch (exception atr){
			cout << "\033[31mParse Failed" << endl;
		}

		if (attrib != "" && attrib != "0"){

			// arguments detected 
			input = argv[2];   	// the color input is past the arguments 
			// argv[0] is the command ex) cpnt
			// argv[1] is the arguments ex) -ub
			// 2 is the color ex) blue
			messageIndex++; 	// set index to after the arguments 
		}
		
		string colornum = check_color(input);
		if (colornum != "37"){
			// color is provided and good
			messageIndex++; // set index over one, could now be 2 or 3 depending on if there are arguments
		}

		string message = "";
		// message forming loop

		for (int i = messageIndex; i < argc; i++) {
			// add all message contents
			try{
				if (message != ""){
					message = message + " " + argv[i];
				} 

				else{
					message = argv[i];
				}
			}
			catch (exception error2){
				// i is too high or other error (not detrimental)
			}
		}
		
		// done with format, printing (apply attributes and color)
		cout << "\033[" + attrib + colornum + "m" << message << "\033[0m" << endl;
	}
	catch (exception main_err){
		cout << "\033[31mMain error" << endl;
	}
}
