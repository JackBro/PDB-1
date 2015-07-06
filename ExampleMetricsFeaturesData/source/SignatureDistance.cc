
#ifndef SIGNATURE_C
#define SIGNATURE_C

#include "SignatureDistance.h"
#include "SignatureFeatureType.h"
#include <iostream>
#include <string>
using namespace std;

SignatureDistance :: SignatureDistance () {
	gotError_ = false;
}

const string &SignatureDistance :: getName () {
	static const string result {"SignatureDistance"};
	return result;
}

int SignatureDistance :: getNumParams () {
	return 2;
}

void SignatureDistance :: takeParam (int whichParam, PDBFeatureTypePtr param) {

	// only take SignatureFeatureType
	if (param->getCode () != 1000001) {
		gotError_ = true;
		errorMsg_ = "You gave SignatureDistance a param of type " + param->getTypeName ();
		return;
	}

	if (whichParam == 0) {
		sigOne_ = param;
		return;
	}
	if (whichParam == 1) {
		sigTwo_ = param;
		return;
	}

	gotError_ = true;
	errorMsg_ = "Bad parameter number to SignatureDistance!";
}

const string &SignatureDistance :: getParamType (int) {
	static const string result {"SignatureFeatureType"};
	return result;
}

void SignatureDistance :: reset () {
	PDBFeatureTypePtr temp;
	sigOne_ = temp;
	sigTwo_ = temp;
	gotError_ = false;
}

double SignatureDistance :: apply (bool &wasError, string &errorMessage) {

	if (gotError_) {
		wasError = true;
		errorMessage = errorMsg_;
		return 9e99;
	}

	if (!sigOne_ || !sigTwo_) {
		wasError = true;
		errorMessage = "One of the parameters to SignatureDistance was null";
		return 9e99;
	}
	
//	SignatureFeatureType* sigOne = dynamic_cast<SignatureFeatureType*>(sigOne_.get());
//	SignatureFeatureType* sigTwo = dynamic_cast<SignatureFeatureType*>(sigTwo_.get());

	double tot = 1.0;
	wasError = false;
	/*
	for (int i : sigOne_Cast->getNonZeroSlots ()) {
		double first = sigOne_Cast->getValue (i);
		double second = sigTwo_Cast->getValue (i);
		tot += (first - second) * (first - second);
	}
	*/
	return tot;
}

PDBMetricPtr SignatureDistance :: getCopy () {
	return make_shared<SignatureDistance>();
}

#endif
