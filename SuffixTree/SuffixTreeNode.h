#pragma once
class SuffixTreeNode
{
public:
	SuffixTreeNode(char myChar, int id, SuffixTreeNode* parent, int depth);
	//SuffixTreeNode(char myChar, int childSize, int id, SuffixTreeNode* parent, int depth);
	SuffixTreeNode* GetChild(int index) const;
	SuffixTreeNode* AddChild(int index, char myChar, int id);
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
private:
	SuffixTreeNode** children;
	int id;
	bool isSmall;
	char smallIndex{};
};




