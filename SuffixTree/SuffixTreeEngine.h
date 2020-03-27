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
	SuffixTreeNode* FindPath(SuffixTreeNode* node, int startIndex);
	static SuffixTreeNode* JumpLinks(SuffixTreeNode* node);
	SuffixTreeNode* NodeHops(SuffixTreeNode* node, std::string beta);
	void DisplayNode(SuffixTreeNode* node);
	void DisplayBWT();
private:
	std::unordered_map<char, int>* alphabetDict;
	std::string input;
	int alphabetCharCount;
	SuffixTreeNode* root;
	int AlphabetIndex(char c) const;
	int PrintTree(SuffixTreeNode* curNode, int count) const;
	int curId;
	SuffixTreeNode* prevMadeInternalNode;
	SuffixTreeNode* u;
	void InsertEndOfSuffix(SuffixTreeNode* node, int startIndex);
	void DisplayBWT(SuffixTreeNode* node);
	int nodeJumpValue;
};

