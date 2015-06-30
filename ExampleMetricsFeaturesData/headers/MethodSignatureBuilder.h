
#ifndef METHOD_SIGNATURE_BUILDER_H
#define METHOD_SIGNATURE_BUILDER_H

#include "PDBFeatureBuilder.h"
#include "PDBFeatureType.h"

class MethodSignatureBuilder : public PDBFeatureBuilder {

private:

	string myName;

public:

	// accepts the name of the feature that we are building
	explicit MethodSignatureBuilder (const string &myName);

	// from the interface
	bool runsOnThisPDBData (PDBData &checkMe) override;
	PDBFeatureTypePtr buildFeature (PDBData &fromMe, bool &wasError, string &errMsg) override;
	const string &getFeatureName () override;
	PDBFeatureBuilder &operator = (PDBFeatureBuilderPtr copyMeIn);
        void *serialize(void *toHere, size_t &size) override;
        void *deSerialize(void *fromHere, size_t &size) override;

};

#endif

