
#ifndef BAG_COMMENTS_BUILDER_H
#define BAG_COMMENTS_BUILDER_H

#include "PDBFeatureBuilder.h"
#include "PDBQueryExecutor.h"
#include "WordFrequencyAggregator.h"

class BagOfCommentsBuilder : public PDBFeatureBuilder {

private:

	string myName;
	PDBQueryExecutorPtr myAggregator;
	int dictionarySize;

public:

	// constructor accepts the name of the feature that we are supposed
	// to be building, as well as aggregate info about the data set (this is a pointer
	// to a WordFrequencyAggregator object), and the size of the dictionary
	// that is to be constructed
	BagOfCommentsBuilder (const string &myName, PDBQueryExecutorPtr aggs, int dictionarySize);

	// from the interface
	bool runsOnThisPDBData (PDBData &checkMe) override;
	PDBFeatureTypePtr buildFeature (PDBData &fromMe, bool &wasError, string &errMsg) override;
	const string &getFeatureName () override;
	PDBFeatureBuilder &operator = (PDBFeatureBuilderPtr &copyMeIn);
	void *serialize(void *toHere, size_t &size) override;
	void *deSerialize(void *fromHere, size_t &size) override;
};

#endif

