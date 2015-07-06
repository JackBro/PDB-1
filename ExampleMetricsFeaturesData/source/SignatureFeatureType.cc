
#ifndef SIGNATURE_F_TYPE_C
#define SIGNATURE_F_TYPE_C

#include "SignatureFeatureType.h"


SignatureFeatureType :: SignatureFeatureType (const string &forMe) {
	val_ = forMe;
}

void SignatureFeatureType :: replaceVal (const string &useMe) {
	val_ = useMe;
}

const string &SignatureFeatureType :: getVal () {
	return val_;
}

const string &SignatureFeatureType :: getTypeName () {
	static const string result {"SignatureFeatureType"};
	return result;
}

string SignatureFeatureType :: display () {
	return val_;
}

int SignatureFeatureType :: getCode () {
	return 1000001;
}

void *SignatureFeatureType :: serialize (void *toHereIn, size_t &size) {
	char *toHere = static_cast<char *> (toHereIn);
	for (size_t i = 0; i < val_.length (); i++) {
		toHere[i] = val_[i];
	}	
	toHere[val_.length ()] = 0;
	size = val_.length () + 1;
	return toHere + val_.length () + 1;
}

void *SignatureFeatureType :: deSerialize (void *fromHereIn, size_t &size) {
	char *fromHere = static_cast<char *> (fromHereIn);
	val_ = fromHere;
	size = val_.length () + 1;
	return fromHere + size;	
}

PDBFeatureTypePtr SignatureFeatureType :: getNewFeatureTypeObject () {
	return make_shared<SignatureFeatureType> ();
}

#endif

