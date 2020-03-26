#include "SuffixTreeEngine.h"
#include <ctime>
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
	clock_t begin = clock();
	for (int i = 0; i < static_cast<int>(this->input.size()); i++)
	{
		if (i % 100 == 0)
			std::cout << i << ":" << (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;

		SuffixTreeNode* curNode = root;
		if (prevMadeInternalNode != nullptr)
			curNode = prevMadeInternalNode->Parent;
		std::string beta = "";
		while (curNode != root)
		{
			if (curNode->suffixLink != nullptr)
			{
				curNode = NodeHops(curNode, beta);
				prevMadeInternalNode->suffixLink = curNode;
				prevMadeInternalNode = curNode;
				i = i + beta.size();
				break;
			}
			beta += curNode->character;
			curNode = curNode->Parent;
		}
		
		curNode = FindPath(curNode, i);
		
		char curChar = this->input[curNode->Depth+i];
		
		if (curChar == '$')
		{
			//end of dat string;
			if (curNode->IsLeaf() && curNode != root)
			{
				if (prevMadeInternalNode != nullptr)
				{
					if (prevMadeInternalNode->Depth != curNode->Depth + 1)
						prevMadeInternalNode->suffixLink = root;
					else
						prevMadeInternalNode->suffixLink = curNode;

				}

				prevMadeInternalNode = curNode;
			}

			curNode->isEnd = true;
		}
		else
		{
			if (curNode->IsLeaf() && curNode != root)
			{
				if (prevMadeInternalNode != nullptr)
				{
					if (prevMadeInternalNode->Depth != curNode->Depth + 1)
						prevMadeInternalNode->suffixLink = root;
					else
						prevMadeInternalNode->suffixLink = curNode;

				}

				prevMadeInternalNode = curNode;
			}

			//lets handle dat fresh insert...
			while (curNode->Depth < static_cast<int>(input.size()-i) - 1)
			{
				curNode->AddChild(AlphabetIndex(this->input[curNode->Depth + i]), this->input[curNode->Depth + i], curId++);
				curNode = curNode->GetChild(AlphabetIndex(this->input[curNode->Depth + i]));
			}

			curNode->isEnd = true;
		}
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

SuffixTreeNode* SuffixTreeEngine::FindPath(SuffixTreeNode* curNode, int startIndex)
{
	std::string substring = this->input.substr(startIndex, input.size() - startIndex);
	SuffixTreeNode* tempNode;

	while (curNode->Depth <= (int)substring.size())
	{
		char curChar = substring[curNode->Depth];
		tempNode = curNode->GetChild(AlphabetIndex(curChar));
		if (tempNode == nullptr)
		{
			return curNode;
		}
		else
		{
			curNode = tempNode;
		}
	}
	//This should NEVER happen.
	return nullptr;
}

SuffixTreeNode* SuffixTreeEngine::JumpLinks(SuffixTreeNode* node)
{
	while (node->suffixLink != nullptr)
	{
		node = node->suffixLink;
	}
	return node;
}

SuffixTreeNode* SuffixTreeEngine::NodeHops(SuffixTreeNode* node, std::string beta)
{
	for (int i = 1; i <= (int)beta.length(); i++)
	{
		node = node->GetChild((*alphabetDict)[beta[beta.size() - i]]);
	}
	return node;
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
