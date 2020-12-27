#include <string>
#include "Help.h"

using namespace std;

string DefaultInfo();
string SpaceInfo();

string CommonHelp() {
	return DefaultInfo()+"\n"+
		"----------------------\n"+
		SpaceInfo() + "\n" +
		"----------------------\n" +
		LoadHelp(false) + "\n" +
		"----------------------\n" +
		StoreHelp(false,false) + "\n" +
		"----------------------\n" +
		SwitchHelp(false) + "\n" +
		"----------------------\n" +
		ListHelp() + "\n" +
		"----------------------\n" +
		FreeHelp(false) + "\n" +
		"----------------------\n" +
		BlurHelp(false) + "\n" +
		"----------------------\n" +
		ResizeHelp(false) + "\n" +
		"----------------------\n" +
		HelpHelp() + "\n" +
		"----------------------\n" +
		ExitHelp() + "\n";
}

string CommandList() {
	return "load(ld) <name> <filename>\n";
}

string DefaultInfo() {
	return "If the object name is not specified, the command will be applied to the selected object.";
}

string SpaceInfo() {
	return "If the name or filename has spaces, they must be enclosed in quotes.";
}

string LoadHelp(bool isSpace) {
	string ret;
	if (isSpace) ret += SpaceInfo() + "\n";
	return ret +
		"load(ld) <name> <filename>\n"
		"<name> - the name of object.\n"
		"<filename> - filename.\n"
		"Loading a file in memory. Use <name> for action with it.";
}

string StoreHelp(bool isDefault, bool isSpace) {
	string ret;
	if (isDefault) ret += DefaultInfo() + "\n";
	if (isSpace) ret += SpaceInfo() + "\n";
	return ret+
		"store(s) [<name>] <filename>"
		"<name> - the name of object.\n"
		"<filename> - filename.\n"
		"Saves image to disk";
}

string SwitchHelp(bool isSpace) {
	string ret;
	if (isSpace) ret += SpaceInfo() + "\n";
	return ret+
		"switch <name>\n"
		"Changes active image";
}

string ListHelp() {
	return "list\n"
		"Prints the list of image";
}

string FreeHelp(bool isSpace) {
	string ret;
	if (isSpace) ret += SpaceInfo() + "\n";
	return ret+
		"free [<name>]\n"
		"Remove object from memory\n"
		"If the object name is not specified, it's only clear work object, don't remove it from memory.";
}

string BlurHelp(bool isDefault, bool isSpace) {
	string ret;
	if (isDefault) ret += DefaultInfo() + "\n";
	if (isSpace) ret += SpaceInfo() + "\n";
	return ret+
		"blur [<from_name>] <to name> <size_x[*size_y]>\n"
		"Smooths the image\n"
		"If the size_y is not specified, it'll be equaly with size_x.";
}

string ResizeHelp(bool isDefault, bool isSpace) {
	string ret;
	if (isDefault) ret += DefaultInfo() + "\n";
	if (isSpace) ret += SpaceInfo() + "\n";
	return ret+
		"resize [<from_name>] <to_name> <new_width> <new_height>\n"
		"Resizes the image";
}

string HelpHelp() {
	return "help(h) [<functin>]\n"
		"Prints help information about function or, if not specified, about all functions";
}

string ExitHelp() {
	return "Exit from program";
}
