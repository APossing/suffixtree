#include "SuffixTreeNode.h"
#include <iostream>
int SuffixTreeNode::childSize;

SuffixTreeNode::SuffixTreeNode(std::string myEdge, int id, SuffixTreeNode* parent, int depth)
{
	this->children = std::vector<SuffixTreeNode*>(30);
	this->id = id;
	this->isEnd = false;
	this->Parent = parent;
	this->Depth = depth;
	this->suffixLink = nullptr;
	this->childCount = 0;
	this->isSmall = true;
	this->smallIndex = -1;
	this->leafId = -1;
	this->edgeString = myEdge;
}

SuffixTreeNode::SuffixTreeNode(std::string myEdge, int id, SuffixTreeNode* parent, int depth, int childrenCount, std::vector<SuffixTreeNode*> childrenArray)
{
	this->children = childrenArray;
	this->id = id;
	this->isEnd = false;
	this->Parent = parent;
	this->Depth = depth;
	this->suffixLink = nullptr;
	this->childCount = childrenCount;
	this->isSmall = childrenCount <=1;
	this->smallIndex = -1;
	this->leafId = -1;
	this->edgeString = myEdge;
}

SuffixTreeNode* SuffixTreeNode::GetChild(int index) const
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

SuffixTreeNode* SuffixTreeNode::AddChild(int index, std::string myEdge, int id)
{
	if (isSmall)
	{
		if (childCount > 0)
		{
			SuffixTreeNode* temp = this->children[0];
			this->children = std::vector<SuffixTreeNode*>(30);
			this->children[smallIndex] = temp;

			this->children[index] = new SuffixTreeNode(myEdge, id, this, Depth + 1);
			isSmall = false;
			this->childCount++;
			return this->children[index];
		}
		else
		{
			this->smallIndex = index;
			this->children = std::vector<SuffixTreeNode*>(30);
			children[0] = new SuffixTreeNode(myEdge, id, this, Depth + 1);
			this->childCount++;
			return this->children[0];
		}

	}
	else
	{
		childCount++;
		this->children[index] = new SuffixTreeNode(myEdge, id, this, Depth + 1);
		return this->children[index];
	}

}

SuffixTreeNode* SuffixTreeNode::breakApart(int breakIndex, int smallIndex)
{
	if (edgeString.length() == 1)
		return nullptr;
	if (breakIndex > edgeString.length())
		return nullptr;
	SuffixTreeNode* child = new SuffixTreeNode(edgeString.substr(breakIndex), id+ breakIndex, this, Depth+breakIndex, childCount, children);
	edgeString = edgeString.substr(0, breakIndex);
	child->isEnd = this->isEnd;

	child->leafId = leafId;
	child->suffixLink = suffixLink;
	child->smallIndex = this->smallIndex;
	
	isEnd = false;
	this->suffixLink = nullptr;
	children = std::vector<SuffixTreeNode*>(30);
	children[0] = {child};
	this->isSmall = true;
	this->childCount = 1;
	this->smallIndex = smallIndex;

	return child;
}

bool SuffixTreeNode::IsLeaf() const
{
	return this->childCount == 1 && !this->isEnd || this->childCount == 0 && this->isEnd || this->childCount == 0 && !this->isEnd;
}

void SuffixTreeNode::Display() const
{
	std::cout << character << std::endl;
}
