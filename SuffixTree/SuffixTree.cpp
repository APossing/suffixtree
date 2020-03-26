// SuffixTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "FileReader.h"
#include "SuffixTreeEngine.h"
int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Please add parameters... <input file containing s1> <input file containing alphabet" << endl;
		return 0;
	}
	
	SingleSequenceFasta sequence = FileReader::ReadFile(argv[1]);
	string alphabet = FileReader::ReadAlphabet(argv[2]);
	SuffixTreeEngine st = SuffixTreeEngine(sequence.s1, list<char>(alphabet.begin(), alphabet.end()));
	st.BuildTree();
	st.DisplayBWT();
	st.PrintTree();
	return 1;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
