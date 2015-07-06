
#ifndef SIGNATURE_F_TYPE_H
#define SIGNATURE_F_TYPE_H

#include "PDBFeatureType.h"
#include <string>
using namespace std;

// stores a vector in a sparse format
class SignatureFeatureType : public PDBFeatureType {

public:

	// constructors
	SignatureFeatureType () = default;
	explicit SignatureFeatureType (const string &forMe);

	// replace the existing string with a new one
	void replaceVal (const string &useMe);
	
	// get the string
	const string &getVal ();
	
	// from the interface
	const string &getTypeName () override;
	int getCode () override;
	void *serialize (void *toHere, size_t &size) override;
	void *deSerialize (void *fromHere, size_t &size) override;
	PDBFeatureTypePtr getNewFeatureTypeObject () override;
	string display () override;
	
private:
	
	string val_;
};

#endif
