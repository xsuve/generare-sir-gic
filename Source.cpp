/*

Format de intrare:
- Simbol de start
- Neterminale
- Terminale
- Productii

*/

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>

using namespace std;

#define MAXCHARS 50

struct P {
	string from;
	vector<string> to;
};

// Split String by Delimiter
vector<string> split(string s, string delimiter) {
	int pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

int main() {
	srand(time(NULL));

	/* Vars */
	int random = 0, lineNr = 0, productiiIterator = 0;
	string lambda = "#", keyChar, from, valuesWithDelimiter, valuesDelimiter = ",";
	string startSymbol;
	string neterminale;
	string terminale;
	P productii[10];

	/* Input */
	ifstream input("input2.txt");
	for(string line; getline(input, line);) {
		if(lineNr == 0) {
			startSymbol = line;
			cout << "Simbol de start: " << startSymbol << endl;
		} else if(lineNr == 1) {
			neterminale = line;
			cout << "Neterminale: " << neterminale << endl;
		} else if(lineNr == 2) {
			terminale = line;
			cout << "Terminale: " << terminale << endl;
			cout << "Productii: " << endl;
		} else {
			// Set From
			from = line.substr(0, line.find(" "));
			productii[productiiIterator].from = from;
			cout << "\t" << from << ": ";

			// Set To
			valuesWithDelimiter = line.substr(line.find(" ") + 1, line.size());
			productii[productiiIterator].to = split(valuesWithDelimiter, valuesDelimiter);
			for(int j = 0; j < productii[productiiIterator].to.size(); j++) {
				cout << productii[productiiIterator].to[j] << " ";
			}
			cout << endl;

			productiiIterator++;
		}

		lineNr++;
	}
	cout << "---------------------------------------------" << endl;

	/* Process */
	while((startSymbol.length() < MAXCHARS) && (startSymbol.find_first_of(neterminale) != string::npos)) {
		int pos = startSymbol.find_first_of(neterminale);
		keyChar = startSymbol.substr(pos, 1);

		for(int i = 0; i < sizeof(productii) / sizeof(productii[0]); i++) {
			if(productii[i].from == keyChar) {
				random = rand() % productii[i].to.size();

				cout << "rand=" << random << ": ";
				if(productii[i].to[random] != lambda) {
					startSymbol.replace(pos, 1, productii[i].to[random]);
				} else {
					startSymbol.erase(pos, 1);
				}
				cout << startSymbol << endl;
			}
		}
	}
}