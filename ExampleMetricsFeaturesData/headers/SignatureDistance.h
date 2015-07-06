
#ifndef SIGNATURE_H
#define SIGNATURE_H

#include "PDBMetric.h"

// computes the Signature distance between two objects
class SignatureDistance : public PDBMetric {

private:

	PDBFeatureTypePtr sigOne_;
	PDBFeatureTypePtr sigTwo_;
	bool gotError_;
	string errorMsg_;

public:

	// constructor
	SignatureDistance ();

	// from the interface
	const string &getName () override;
	int getNumParams () override;
	void takeParam (int whichParam, PDBFeatureTypePtr param) override;
	const string &getParamType (int whichParam) override;
	void reset () override;
	double apply (bool &wasError, string &errorMessage) override;
	PDBMetricPtr getCopy () override;
};

#endif

