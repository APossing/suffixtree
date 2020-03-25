#include "SuffixTreeNode.h"
#include <iostream>

SuffixTreeNode::SuffixTreeNode(char myChar, int childSize, int id)
{
	this->childSize = childSize;
	this->children = new SuffixTreeNode*[childSize]();
	this->id = id;
	this->isEnd = false;
	this->character = myChar;
}

SuffixTreeNode* SuffixTreeNode::GetChild(int index)
{
	//should add some error checking, but I want it to crash rn.
	return this->children[index];
}

SuffixTreeNode* SuffixTreeNode::AddChild(int index, char myChar, int id)
{
	this->children[index] = new SuffixTreeNode(myChar, this->childSize, id);
	return this->children[index];
}

void SuffixTreeNode::Display()
{
	std::cout << character << std::endl;
}
