
#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include "PDBStoredDataType.h"
#include <string>
#include <vector>
using namespace std;

class TextFileData : public PDBStoredDataType {

private:

	string fName;
	vector <string> lines;
	std::string boc_;
	std::string return_type_;
	std::string method_name_;
	std::string parameters_;

public:

	// create a TextFileData object by reading a file
	explicit TextFileData (const string &fName);

	// access the vector of lines in the file
	vector <string> getLines ();

	// access the name of the file
	const string &getFileName ();

	// access the bag of comments
	const std::string& getBagOfComments();

	// access the return type
	const std::string& getReturnType();

	// access the method name
	const std::string& getMethodName();

	// access the parameters
	const std::string& getParameters();

	// do-nothing constructor
	TextFileData () = default;

	// from PDBStoredDataType
	int getCode () override;
	string display () override;
	const string &getName () override;
	void *serialize (void *toHereIn, size_t &size) override;
	void *deSerialize (void *toHereIn, size_t &size) override;
	PDBStoredDataTypePtr getNewStoredDataTypeObject () override;
};

#endif
