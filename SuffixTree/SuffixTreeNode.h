#pragma once
class SuffixTreeNode
{
public:
	SuffixTreeNode(char myChar, int childSize, int id);
	//SuffixTreeNode(int childSize, char child, int id);
	SuffixTreeNode* GetChild(int index);
	SuffixTreeNode* AddChild(int index, char myChar, int id);
	void Display();
	int getId();
	bool isEnd;
	char character;
private:
	SuffixTreeNode** children;
	int childSize;
	int id;
};

