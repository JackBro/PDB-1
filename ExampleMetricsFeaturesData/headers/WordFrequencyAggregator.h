
#ifndef WORD_FREQ_AGG_H
#define WORD_FREQ_AGG_H

#include "PDBQueryExecutor.h"
#include <map>
#include <memory>
#include <vector>
using namespace std;

class WordFrequencyAggregator;
typedef shared_ptr <WordFrequencyAggregator> WordFrequencyAggregatorPtr;

// this class is used to count word frequencies in a document
class WordFrequencyAggregator : public PDBQueryExecutor {

public:

	// checks how frequent the given word is... returns a value from 0
	// (most frequent) to the number of words (found - 1) (least frequent)
	// if the word has not been ranked, reutrn a -1
	int getRank (const string &checkMe);

	// gets the count of this word
	int getCount (const string &checkMe);

	// gets the kth most frequent word
	const string &getKthMostFrequent (int k);

	// returns the number of distinct words found
	int getNumDistinctWords ();

	// constructor
	WordFrequencyAggregator ();

	// these are inherited from PDBQueryExecutor
	PDBQueryExecutor &operator += (PDBQueryExecutorPtr rhs) override;
	PDBQueryExecutorPtr getEmpty () override;
	void aggregate (PDBData &aggMe) override;
	string display () override;
	void *serialize (void *toHere, size_t &numBytes) override;
	void *deSerialize (void *fromHere, size_t &numBytes) override;
	bool wasAnError (string &error) override;

private:

	// used to count words
	map <string, int> counter;

	// used to get the rank of the frequency of different words
	map <string, int> ranks;

	// used to get the word for a particular ranking
	map <int, string> reverseRanks;
	
	// used to see if ranks is up-to-date
	bool sorted;
};

#endif

