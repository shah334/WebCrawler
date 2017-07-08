
#ifndef SIMPLEHTMLPARSER_H
#define SIMPLEHTMLPARSER_H

#include "openhttp.h"
#include <string>
#include <vector>
using namespace std;
class SimpleHTMLParser {
	// URL read in anchor

	int urlAnchorLength;
	char urlAnchor[MaxURLLength];
	
	bool match(char **b, const char *m);
 public:
	SimpleHTMLParser();
	int characterCount;
	string description;
	vector<string> urlvector; 
	bool parse(char * buffer, int n);

	// Calbacks
	virtual void onContentFound(char c);
	virtual void onAnchorFound(char * url);
};

#endif

