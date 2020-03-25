#include "SuffixTreeNode.h"
#include <iostream>

SuffixTreeNode::SuffixTreeNode(char myChar, int childSize, int id, SuffixTreeNode* parent, int depth)
{
	this->childSize = childSize;
	this->children = new SuffixTreeNode*[childSize]();
	this->id = id;
	this->isEnd = false;
	this->character = myChar;
	this->Parent = parent;
	this->Depth = depth;
	this->suffixLink = nullptr;
	this->childCount = 0;
}

SuffixTreeNode* SuffixTreeNode::GetChild(int index)
{
	//should add some error checking, but I want it to crash rn.
	return this->children[index];
}

SuffixTreeNode* SuffixTreeNode::AddChild(int index, char myChar, int id)
{
	childCount++;
	this->children[index] = new SuffixTreeNode(myChar, this->childSize, id ,this, Depth+1);
	return this->children[index];
}

bool SuffixTreeNode::IsLeaf()
{
	return this->childCount == 1 || this->childCount == 0 && this->isEnd;
}

void SuffixTreeNode::Display()
{
	std::cout << character << std::endl;
}
