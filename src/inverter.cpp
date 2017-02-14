#include <string>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <regex>

#include "inverter.h"

using namespace std;


string build_inverted_index(string filename) {
	map<string, set<int>> invertedindex;
	ifstream infile;
	infile.open(filename.c_str(), ios::in);
	string file;
	int fcount = 0;
	while(getline(infile, file)) {
		ifstream subfile;
		subfile.open(file.c_str(), ios::in);
		string str;
		while(getline(subfile, str)) {
			regex r("[^a-zA-Z]+");
			for(sregex_token_iterator it = sregex_token_iterator(str.begin(), str.end(), r, -1); it != sregex_token_iterator(); ++it) {
				map<string, set<int>>::iterator itr = invertedindex.find(*it);
				if(itr != invertedindex.end()) itr->second.insert(fcount);
				else {
					set<int> set = {fcount};
					invertedindex.insert(itr, make_pair(*it, set));
				}
			}
		}
		subfile.close();
		fcount++;
	}
	infile.close();
	string format = "";
	for(map<string, set<int>>::iterator it = invertedindex.begin(); it != invertedindex.end(); ++it) {
		format += (it->first + (": "));
		unsigned int loops = 1;
		for(int f : it->second) {
			if(it->second.size() == loops) format += to_string(f) + '\n';
			else format += to_string(f) + " ";
			loops++;
		}
	}
	return format;
}