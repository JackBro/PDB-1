
#ifndef SIGNATURE_C
#define SIGNATURE_C

#include "SignatureDistance.h"
#include "SparseVectorFeatureType.h"
#include <iostream>
#include <string>
using namespace std;

SignatureDistance :: SignatureDistance () {
	gotError = false;
}

const string &SignatureDistance :: getName () {
	static const string result {"SignatureDistance"};
	return result;
}

int SignatureDistance :: getNumParams () {
	return 2;
}

void SignatureDistance :: takeParam (int whichParam, PDBFeatureTypePtr param) {

	if (param->getCode () != 5923458) {
		gotError = true;
		errorMsg = "You gave SignatureDistance a param of type " + param->getTypeName ();
		return;
	}

	if (whichParam == 0) {
		vecOne = param;
		return;
	}
	if (whichParam == 1) {
		vecTwo = param;
		return;
	}

	gotError = true;
	errorMsg = "Bad parameter number to SignatureDistance!";
}

const string &SignatureDistance :: getParamType (int) {
	static const string result {"SparseVectorFeatureType"};
	return result;
}

void SignatureDistance :: reset () {
	PDBFeatureTypePtr temp;
	vecOne = temp;
	vecTwo = temp;
	gotError = false;
}

double SignatureDistance :: apply (bool &wasError, string &errorMessage) {

	if (gotError) {
		wasError = true;
		errorMessage = errorMsg;
		return 9e99;
	}

	if (!vecOne || !vecTwo) {
		wasError = true;
		errorMessage = "One of the parameters to SignatureDistance was null";
		return 9e99;
	}
	
	SparseVectorFeatureType *vecOneCast = dynamic_cast<SparseVectorFeatureType *> (vecOne.get ());
	SparseVectorFeatureType *vecTwoCast = dynamic_cast<SparseVectorFeatureType *> (vecTwo.get ());

	double tot = 0.0;
	wasError = false;
	for (int i : vecOneCast->getNonZeroSlots ()) {
		double first = vecOneCast->getValue (i);
		double second = vecTwoCast->getValue (i);
		tot += (first - second) * (first - second);
	}
	return tot;
}

PDBMetricPtr SignatureDistance :: getCopy () {
	return make_shared<SignatureDistance>();
}

#endif
