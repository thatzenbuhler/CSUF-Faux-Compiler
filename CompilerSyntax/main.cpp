// CPSC 323 Compilers
// Project 2: Syntax Analyzer
// main.cpp, lexer.h, syntax.h
// Tyler Hatzenbuhler
// Anette Ulrichsen
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<stack>

#include"lexer.h"
#include"syntax.h"
#include"assembly.h"

using namespace std;

int main() {
	string filename;
	int iterator = 0;
	vector<Token> v;
	fstream input;
	string fileline;
	Token endline("", "Endline");

	cout << "Enter file to open: ";
	cin >> filename;

	// Opens Source Code Text File
	input.open(filename);
	if (!input)
	{
		cerr << "Cannot find file" << endl;
		exit(1);
	}

	// Activates Lexer One Line at a time
	while (!input.eof())
	{
		getline(input, fileline);
		if (fileline == "")
		{
			getline(input, fileline);
		}
		lexer(fileline, v, iterator);
		v.push_back(endline); // Used for counting lines in error detection.
	}
	input.close();

	// Begins Syntax Analysis
	syntax(v);
	cout << "\nSyntax Analyis complete.\n";

	printIT();

	ofstream outf("output.txt");
	if (!outf)
	{
		// Print an error and exit
		cerr << "Could not create output file" << endl;
		exit(1);
	}
	
	// Output Instruction Vector to outf //
	for (int i = 0; i < InstrTable.size(); i++) {
		outf << i + 1 << "\t" << InstrTable[i].Op << "\t";
		if (InstrTable[i].operand == -1)
			outf << endl;
		else
			outf << InstrTable[i].operand << endl;
	}
	outf << endl;

	system("pause");
	return 0;
}