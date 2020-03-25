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
	void PrintTree() const;
	void FindPath(SuffixTreeNode* node);
	static SuffixTreeNode* NodeHops(SuffixTreeNode* node);
	void DisplayNode(SuffixTreeNode* node);
private:
	std::unordered_map<char, int>* alphabetDict;
	std::string input;
	int alphabetCharCount;
	void InserSubString(std::string substring);
	SuffixTreeNode* root;
	int AlphabetIndex(char c) const;
	int PrintTree(SuffixTreeNode* curNode, int count) const;
	int curId;
	SuffixTreeNode* prevMadeInternalNode;
};

