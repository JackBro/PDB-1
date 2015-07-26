
#ifndef TEXT_FILE_C
#define TEXT_FILE_C


#include "TextFileData.h"
#include <fstream>
#include <iostream>
using namespace std;

TextFileData :: TextFileData (const string &fNameIn) {
	fName = fNameIn;

	// now read in the file
	string line;
	ifstream myfile(fName);
	if (myfile.is_open()) {
		std::getline(myfile, boc_);
		std::getline(myfile, return_type_);
		std::getline(myfile, method_name_);
		std::getline(myfile, parameters_);
		while (getline (myfile, line)) {
			lines.push_back (line);
		}
        myfile.close();
	} else {
		cerr << "Warning: unable to open file '" << fNameIn << "'\n";
	}
}

const string &TextFileData :: getFileName () {
	return fName;	
}

const std::string& TextFileData::getBagOfComments() {
	return boc_;
}

const std::string& TextFileData::getReturnType() {
	return return_type_;
}

const std::string& TextFileData::getMethodName() {
	return method_name_;
}

const std::string& TextFileData::getParameters() {
	return parameters_;
}

void *TextFileData :: serialize (void *toHereIn, size_t &size) {

	// write the text file name
	char *toHere = static_cast<char *> (toHereIn);

	// copy the characters over
	fName.copy (toHere, fName.size (), 0);
	toHere[fName.size ()] = 0;
	toHere += fName.size () + 1;

	// and now write the individual lines
	*(reinterpret_cast<int *> (toHere)) = lines.size ();
	toHere += sizeof (int);
	for (const string &s : lines) {
		s.copy (toHere, s.size (), 0);
		toHere[s.size ()] = 0;
		toHere += s.size () + 1;
	}

	// done!!
	size = toHere - static_cast<char *> (toHereIn);
	return toHere;
}

void *TextFileData :: deSerialize (void *fromHereIn, size_t &size) {

	// get the text file name
	char *fromHere = static_cast<char *> (fromHereIn);
	fName = fromHere;
	fromHere += fName.size () + 1;
	
	// now, read in all of the lines
	int numLines = *(reinterpret_cast<int *> (fromHere));
	fromHere += sizeof (int);

	lines.clear ();
	for (int i = 0; i < numLines; i++) {
		string nextLine (fromHere);
		fromHere += nextLine.size () + 1;
		lines.push_back (nextLine);
	}

	// done!!
	size = fromHere - static_cast<char *> (fromHereIn);
	return fromHere;
}

int TextFileData :: getCode () {
	return 494853243;
}

const string &TextFileData :: getName () {
	static const string result {"TextFileData"};
	return result;
}

vector <string> TextFileData :: getLines () {
	return lines;
}

PDBStoredDataTypePtr TextFileData :: getNewStoredDataTypeObject () {
	return make_shared<TextFileData> ();
}

string TextFileData :: display () {
	if (lines.size () == 0) {
		return fName + ": <empty>";
	} else {
		return fName + ": '" + return_type_ + " " + method_name_ + "(" + parameters_ + ")'";
	}
}

#endif
