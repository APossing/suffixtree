#pragma once
class SuffixTreeNode
{
public:
	SuffixTreeNode(char myChar, int childSize, int id, SuffixTreeNode* parent, int depth);
	//SuffixTreeNode(int childSize, char child, int id);
	SuffixTreeNode* GetChild(int index);
	SuffixTreeNode* AddChild(int index, char myChar, int id);
	bool IsLeaf();
	void Display();
	int getId();
	bool isEnd;
	char character;
	SuffixTreeNode* Parent;
	int Depth;
	SuffixTreeNode* suffixLink;
private:
	SuffixTreeNode** children;
	int childSize;
	int id;
};

