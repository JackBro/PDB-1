
#ifndef SIGNATURE_F_TYPE_C
#define SIGNATURE_F_TYPE_C

#include "SignatureFeatureType.h"

SignatureFeatureType::SignatureFeatureType(const std::string& boc,
                     const std::string& returnType,
                     const std::string& methodName,
                     const std::string& parameters) {
    boc_ = boc;
    returnType_ = returnType;
    methodName_ = methodName;
    parameters_ = parameters;
}

const std::string& SignatureFeatureType::getBOC() {
    return boc_;
}

const std::string& SignatureFeatureType::getReturnType() {
    return returnType_;
}

const std::string& SignatureFeatureType::getMethodName() {
    return methodName_;
}

const std::string& SignatureFeatureType::getParameters() {
    return parameters_;
}

// implementation for the interface
const std::string &SignatureFeatureType :: getTypeName () {
	static const std::string result {"SignatureFeatureType"};
	return result;
}

std::string SignatureFeatureType :: display () {
	return returnType_ + " " + methodName_ + "(";
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

