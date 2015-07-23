
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
    char *toHere = static_cast<char *>(toHereIn);
    for (size_t i = 0; i < boc_.length(); i++) {
        toHere[i] = boc_[i];
    }
    toHere[boc_.length()] = 0;
    toHere += boc_.length() + 1;
    for (size_t i = 0; i < returnType_.length(); i++) {
        toHere[i] = returnType_[i];
    }
    toHere[returnType_.length()] = 0;
    toHere += returnType_.length() + 1;
    for (size_t i = 0; i < methodName_.length(); i++) {
        toHere[i] = methodName_[i];
    }
    toHere[methodName_.length()] = 0;
    toHere += methodName_.length() + 1;
    for (size_t i = 0; i < parameters_.length(); i++) {
        toHere[i] = parameters_[i];
    }
    toHere[parameters_.length()] = 0;
    toHere += parameters_.length() + 1;
    size = toHere - static_cast<char*>(toHereIn);
    return toHere;
}

void *SignatureFeatureType :: deSerialize (void *fromHereIn, size_t &size) {
    char *fromHere = static_cast<char *> (fromHereIn);
    boc_ = fromHere;
    fromHere += boc_.length() + 1;
    returnType_ = fromHere;
    fromHere += returnType_.length() + 1;
    methodName_ = fromHere;
    fromHere += methodName_.length() + 1;
    parameters_ = fromHere;
    fromHere += parameters_.length() + 1;
    size = fromHere - static_cast<char*>(fromHereIn);
    return fromHere;
}

PDBFeatureTypePtr SignatureFeatureType :: getNewFeatureTypeObject () {
	return make_shared<SignatureFeatureType> ();
}

#endif

