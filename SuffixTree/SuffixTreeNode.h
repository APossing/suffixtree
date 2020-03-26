#pragma once
#include <string>

class SuffixTreeNode
{
public:
	SuffixTreeNode(std::string myChar, int id, SuffixTreeNode* parent, int depth);
	SuffixTreeNode(std::string myChar, int id, SuffixTreeNode* parent, int depth, int childrenCount, SuffixTreeNode** childrenArray);
	SuffixTreeNode* GetChild(int index) const;
	SuffixTreeNode* AddChild(int index, std::string myEdge, int id);
	SuffixTreeNode* breakApart(int breakIndex, int smallIndex);
	bool IsLeaf() const;
	void Display() const;
	int getId();
	bool isEnd;
	char character;
	SuffixTreeNode* Parent;
	int Depth;
	SuffixTreeNode* suffixLink;
	int childCount;
	static int childSize;
	int leafId;
	std::string edgeString;
private:
	SuffixTreeNode** children;
	int id;
	bool isSmall;
	char smallIndex{};
	
};




