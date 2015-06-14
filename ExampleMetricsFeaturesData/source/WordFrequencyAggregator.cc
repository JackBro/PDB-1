
#ifndef WORD_FREQ_AGG_C
#define WORD_FREQ_AGG_C

#include "TextFileData.h"
#include "WordFrequencyAggregator.h"
#include "WordFrequencyPair.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

int WordFrequencyAggregator :: getCount (const string &checkMe) {
	if (!sorted)
		getRank ("");

	const auto found (counter.find (checkMe));
	return found == counter.end () ? 0 : found->second;
}

const string &WordFrequencyAggregator :: getKthMostFrequent (int checkMe) {
	if (!sorted)
		getRank ("");

	const auto found (reverseRanks.find (checkMe));
	static const string empty;
	return found == reverseRanks.end () ? empty : found->second;
}

int WordFrequencyAggregator :: getRank (const string &checkMe) {

	// if we are not sorted, then rebuild the ranks vector
	if (!sorted) {

		vector <WordFreqPair> frequencies;
		frequencies.reserve (counter.size ());
	
		// first, extract the frequencies
		for (auto const &p : counter)
			frequencies.emplace_back (p.first, p.second);

		// now sort them
		sort (frequencies.begin (), frequencies.end ());

		// and load them up into the list of ranks
		ranks.clear ();
		reverseRanks.clear ();
		for (size_t i = 0; i < frequencies.size (); i++) {
			const string &word {frequencies[i].getString ()};
			ranks[word] = i;
			reverseRanks[i] = word;
		}

		// done!
		sorted = true;
	}

	const auto found (ranks.find (checkMe));
	return found == ranks.end () ? -1 : found->second;
}

int WordFrequencyAggregator :: getNumDistinctWords () {
	return counter.size ();
}

WordFrequencyAggregator :: WordFrequencyAggregator () {
	sorted = false;
}

PDBQueryExecutor &WordFrequencyAggregator :: operator += (PDBQueryExecutorPtr rhs) {

	// we have to re-sort
	sorted = false;

	// this guy had better be a WordFrequencyAggregator!!
	WordFrequencyAggregator *other = dynamic_cast<WordFrequencyAggregator *> (rhs.get ());
	
	// loop through all of his entries
	for (auto const &p : other->counter)
		counter[p.first] += p.second;

	return *this;
}

PDBQueryExecutorPtr WordFrequencyAggregator :: getEmpty () {
	return make_shared<WordFrequencyAggregator> ();
}

void WordFrequencyAggregator :: aggregate (PDBData &aggMe) {

	// make sure we are trying to aggregate a TextFileData object
	if (aggMe.getData ()->getCode () != 494853243)
		return;

	// we have to re-sort
	sorted = false;

	// now, loop through all of the lines in the text file
	TextFileData *temp = dynamic_cast<TextFileData *> (aggMe.getData ().get ());
	for (const string &s : temp->getLines ()) {

		// find the first "real" character
		size_t posLast = s.find_first_not_of (" \t\n");
		if (posLast == string :: npos) 
			continue;

		// loop through the string
		while (true) {

			// find the next space character
			size_t posNext = s.find_first_of (" <>?(),-';.\"\t\n", posLast);
			if (posNext == string :: npos) {
				posNext = s.size ();
			}

			// now, extract the word
			string word = s.substr (posLast, posNext - posLast);
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			
			// and count it
			if (!word.empty ())
				++counter[word];

			// and see if we are done
			if (posNext == s.size ())
				break;
			posLast = s.find_first_not_of (" <>?(),-';.\"\t\n", posNext);
			if (posLast == string :: npos) 
				break;
		}
	}
}

bool WordFrequencyAggregator ::  wasAnError (string &) {
	// no possible errors at this time!
	return false;
}

string WordFrequencyAggregator :: display () {
	ostringstream buffer;
	buffer << '<';
	int limit = 10;
	if (getNumDistinctWords () < limit)
		limit = getNumDistinctWords ();
	for (int i = 0; i < limit; i++) {
		string word = getKthMostFrequent (i);
		int count = getCount (word);
		buffer << word << ": " << count;
		if (i != limit - 1)
			buffer << ", ";			
	}	
	if (limit < getNumDistinctWords ())
		buffer << "...";
	buffer << '>';
	return buffer.str();
}

// these are unimplemented; will be needed for the distributed version!!
void *WordFrequencyAggregator :: serialize (void *toHere, size_t &) {
	return toHere;
}

void *WordFrequencyAggregator :: deSerialize (void *fromHere, size_t &) {
	return fromHere;
}

#endif

