#include "SuffixTreeEngine.h"

#include <utility>
#include <ostream>
#include <iostream>

SuffixTreeEngine::SuffixTreeEngine(std::string input, std::list<char> alphabet)
{
	alphabetCharCount = static_cast<int>(alphabet.size()) + 1;
	alphabetDict = new std::unordered_map<char, int>(alphabetCharCount);
	int i = 1;
	alphabet.sort();
	for (char element : alphabet)
	{
		(*alphabetDict)[element] = i++;
	}
	this->input = std::move(input) + "$";
	this->root = new SuffixTreeNode(' ', -1, nullptr, 0);
	SuffixTreeNode::childSize = alphabetCharCount;
	this->root->isEnd = true;
	this->curId = 1;
	this->prevMadeInternalNode = nullptr;
}

void SuffixTreeEngine::BuildTree()
{
	for (int i = 0; i < this->input.size(); i++)
	{
		InserSubString(this->input.substr(i, input.size() - i));
	}
}

void SuffixTreeEngine::PrintTree() const
{
	int count = 1;
	SuffixTreeNode* tempNode;
	std::cout << "$:1" << " ";
	for (int i = 0; i < this->alphabetCharCount; i++)
	{
		tempNode = root->GetChild(i);
		if (tempNode != nullptr)
		{
			count = PrintTree(tempNode, count);
		}
	}
}

SuffixTreeNode* SuffixTreeEngine::NodeHops(SuffixTreeNode* node)
{
	while (node->suffixLink != nullptr)
	{
		node = node->suffixLink;
	}
	return node;
}

void SuffixTreeEngine::InserSubString(std::string substring)
{
	SuffixTreeNode* curNode = root;
	if (prevMadeInternalNode != nullptr)
		curNode = prevMadeInternalNode->Parent;
	while (curNode != root)
	{
		if (curNode->suffixLink != nullptr)
		{
			curNode = NodeHops(curNode);
			break;
		}
		curNode = curNode->Parent;
	}
	
	SuffixTreeNode* tempNode;



	
	bool insertComplete = false;
	while (curNode->Depth <= (int)substring.size() && !insertComplete)
	{
		char curChar = substring[curNode->Depth];
		tempNode = curNode->GetChild(AlphabetIndex(curChar));
		if (tempNode == nullptr)
		{
			if (curChar == '$')
			{
				//end of dat string;
				if (curNode->IsLeaf() && curNode != root)
				{
					if (prevMadeInternalNode != nullptr)
						prevMadeInternalNode->suffixLink = curNode;

					prevMadeInternalNode = curNode;
				}
				
				curNode->isEnd = true;
			}
			else
			{
				if (curNode->IsLeaf() && curNode != root)
				{
					if (prevMadeInternalNode != nullptr)
						prevMadeInternalNode->suffixLink = curNode;
					
					prevMadeInternalNode = curNode;
				}
				
				//lets handle dat fresh insert...
				while (curNode->Depth < static_cast<int>(substring.size()) - 1)
				{
					curNode->AddChild(AlphabetIndex(substring[curNode->Depth]), substring[curNode->Depth], curId++); //depth may be off by one
					curNode = curNode->GetChild(AlphabetIndex(substring[curNode->Depth]));
				}
				curNode->isEnd = true;
			}
			insertComplete = true;
		}
		else
		{
			curNode = tempNode;
		}
	}
}

int SuffixTreeEngine::AlphabetIndex(char c) const
{
	return (*alphabetDict)[c];
}

int SuffixTreeEngine::PrintTree(SuffixTreeNode* curNode, int count) const
{
	if (count == 10)
	{
		count = 0;
		std::cout << std::endl;
	}
	count++;
	std::cout << curNode->character<< ":"<<curNode->Depth<< " ";
	
	if (count == 10)
	{
		count = 0;
		std::cout << std::endl;
	}

	if (curNode->isEnd)
	{
		std::cout << "$" << ":" << curNode->Depth+1 << " ";
		count++;
	}



	for (int i = 0; i < this->alphabetCharCount; i++)
	{
		if (count == 10)
		{
			count = 0;
			std::cout << std::endl;
		}
		
		SuffixTreeNode* tempNode = curNode->GetChild(i);
		if (tempNode != nullptr)
			count = PrintTree(tempNode, count++);
	}
	return count;
}
