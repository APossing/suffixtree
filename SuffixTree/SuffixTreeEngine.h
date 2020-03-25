#pragma once
#include <string>
#include <list>
#include <unordered_map>
#include "SuffixTreeNode.h"
class SuffixTreeEngine
{
public:
	SuffixTreeEngine(std::string input, std::list<char> alphabet);
	void BuildTree();
	void PrintTree();
	void FindPath(SuffixTreeNode* node);
	SuffixTreeNode* NodeHops(SuffixTreeNode* node);
	void DisplayNode(SuffixTreeNode* node);
private:
	std::unordered_map<char, int>* alphabetDict;
	std::string input;
	int alphabetCharCount;
	void InserSubString(std::string substring);
	SuffixTreeNode* root;
	int AlphabetIndex(char c);
	int PrintTree(SuffixTreeNode* curNode, int count);
	int curId;
	SuffixTreeNode* prevMadeInternalNode;
};

