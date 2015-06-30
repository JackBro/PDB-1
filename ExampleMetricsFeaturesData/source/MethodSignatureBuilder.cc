
#ifndef CLASS_NAME_BUILDER_C
#define CLASS_NAME_BUILDER_C

#include "MethodSignatureBuilder.h"
#include "TextFeatureType.h"
#include "TextFileData.h"

MethodSignatureBuilder :: MethodSignatureBuilder (const string &myNameIn) {
	myName = myNameIn;
}

PDBFeatureBuilder &MethodSignatureBuilder :: operator = (PDBFeatureBuilderPtr copyMeIn) {
	MethodSignatureBuilder *copyMe = dynamic_cast<MethodSignatureBuilder *> (copyMeIn.get ());
	myName = copyMe->myName;
	return *this;
}

bool MethodSignatureBuilder :: runsOnThisPDBData (PDBData &checkMe) {
	if (checkMe.getData ()->getCode () == 494853243)
		return true;
	else
		return false;
}

PDBFeatureTypePtr MethodSignatureBuilder :: buildFeature (PDBData &fromMe, bool &wasError, string &) {

	wasError = false;
	TextFileData *temp = dynamic_cast<TextFileData *> (fromMe.getData ().get ());
	return make_shared<TextFeatureType>(temp->getSignature());
}

const string &MethodSignatureBuilder :: getFeatureName () {
	return myName;
}

// these do not do anything... they will only be called in a distributed database
// implementation in order to ship serialized objects around the cluster
void *MethodSignatureBuilder :: serialize(void *toHere, size_t &) {
	return toHere;
}

void *MethodSignatureBuilder :: deSerialize(void *fromHere, size_t &) {
	return fromHere;
}

#endif
