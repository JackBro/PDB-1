
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
	std::string signature_;
	std::string boc_;

public:

	// create a TextFileData object by reading a file
	explicit TextFileData (const string &fName);

	// access the vector of lines in the file
	vector <string> getLines ();

	// access the name of the file
	const string &getFileName ();

	// access the method signature
	const std::string& getSignature();

	// access the bag of comments
	const std::string& getBagOfComments();

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
