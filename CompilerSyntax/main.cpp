#include<iostream>
#include"lexer.h"

using namespace std;

int main() {
	string filename;
	int iterator = 0;
	vector<Token> v;
	fstream input;
	string fileline;

	cout << "Enter file to open: ";
	cin >> filename;

	input.open(filename);
	if (!input)
	{
		cerr << "Cannot find file" << endl;
		exit(1);
	}

	while (!input.eof())
	{
		getline(input, fileline);
		if (fileline == "")
		{
			getline(input, fileline);
		}
		lexer(fileline, v, iterator);
	}

	input.close();

	for (int i = 0; i < v.size(); i++)
	{
		v[i].print();
	}

	ofstream outf("output.txt");
	if (!outf)
	{
		// Print an error and exit
		cerr << "Could not create output file" << endl;
		exit(1);
	}
	for (int i = 0; i < v.size(); i++)
	{
		outf << v[i].tokentype << " " << v[i].lexeme << endl;
	}

	system("pause");
	return 0;
}