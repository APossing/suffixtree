#include "SuffixTreeNode.h"
#include <iostream>

SuffixTreeNode::SuffixTreeNode(char myChar, int childSize, int id, SuffixTreeNode* parent, int depth)
{
	this->childSize = childSize;
	this->children = new SuffixTreeNode*[1]();
	this->id = id;
	this->isEnd = false;
	this->character = myChar;
	this->Parent = parent;
	this->Depth = depth;
	this->suffixLink = nullptr;
	this->childCount = 0;
	this->isSmall = true;
 }

SuffixTreeNode* SuffixTreeNode::GetChild(int index)
{
	//should add some error checking, but I want it to crash rn.

	if (this->isSmall)
	{
		if (this->smallIndex == index)
			return this->children[0];
		return nullptr;
	}
	else
	{
		return this->children[index];
	}
	

}

SuffixTreeNode* SuffixTreeNode::AddChild(int index, char myChar, int id)
{
	if (isSmall)
	{
		if (childCount > 0)
		{
			SuffixTreeNode* temp = this->children[0];
			this->children = new SuffixTreeNode*[this->childSize]();
			this->children[smallIndex] = temp;

			this->children[index] = new SuffixTreeNode(myChar, this->childSize, id, this, Depth + 1);
			isSmall = false;
		}
		else
		{
			this->smallIndex = index;
			this->children[0] = new SuffixTreeNode(myChar, this->childSize, id, this, Depth + 1);
		}

	}
	else
	{
		childCount++;
		this->children[index] = new SuffixTreeNode(myChar, this->childSize, id, this, Depth + 1);
		return this->children[index];
	}

}

bool SuffixTreeNode::IsLeaf()
{
	return this->childCount == 1 && !this->isEnd || this->childCount == 0 && this->isEnd;
}

void SuffixTreeNode::Display()
{
	std::cout << character << std::endl;
}
