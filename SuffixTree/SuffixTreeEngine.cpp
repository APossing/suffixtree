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
	this->input = std::move(input);
	this->root = new SuffixTreeNode("", -1, nullptr, 0);
	this->root->suffixLink = root;
	this->root->leafId = this->input.length();
	this->u = root;
	SuffixTreeNode::childSize = alphabetCharCount;
	this->root->isEnd = true;
	this->curId = 1;
	this->prevMadeInternalNode = nullptr;
}

void SuffixTreeEngine::BuildTree()
{
	clock_t begin = clock();
	for (int i = 0; i < static_cast<int>(this->input.length()); i++)
	{
		if (i % 100 == 0)
			std::cout << i << ":" << (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;

		SuffixTreeNode* curNode = u;

		if (u->suffixLink == nullptr)
		{
			clock_t begin1 = clock();
			//case 2
			std::string beta = curNode->edgeString.substr(0, curNode->edgeString.length() - 1);
			curNode = curNode->Parent;
			while (curNode->suffixLink == nullptr)
			{
				beta += curNode->edgeString;
				curNode = curNode->Parent;
			}
			//case 2b
			if (curNode == root && beta.length() > 0)
			{
				beta.erase(0,1);
			}
			curNode = curNode->suffixLink;
			curNode = NodeHops(curNode, beta);
			if (u != root)
				u->suffixLink = curNode;
			curNode = FindPath(curNode, i);
			clock_t begin3 = clock();
			InsertEndOfSuffix(curNode, i);
			std::cout << i << "isnSuffix took: " << (clock() - begin3) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;

			std::cout << i << "case2 took: " << (clock() - begin1) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;
		}
		else
		{
			clock_t begin2 = clock();
			//case 1
			curNode = u->suffixLink;
			curNode = FindPath(curNode, i);
			clock_t begin5 = clock();
			InsertEndOfSuffix(curNode, i);
			std::cout << i << "isnSuffix took: " << (clock() - begin5) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;
			std::cout << i << "case 1 took:" << (clock() - begin2) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;
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

int SuffixTreeEngine::PrintTree(SuffixTreeNode* curNode, int count) const
{
	if (count == 10)
	{
		count = 0;
		std::cout << std::endl;
	}
	count++;
	std::cout << curNode->edgeString << ":" << curNode->Depth << " ";

	if (count == 10)
	{
		count = 0;
		std::cout << std::endl;
	}

	if (curNode->isEnd)
	{
		std::cout << "$" << ":" << curNode->Depth + 1 << " ";
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


SuffixTreeNode* SuffixTreeEngine::FindPath(SuffixTreeNode* curNode, int startIndex)
{
	std::string substring = this->input.substr(startIndex, input.size() - startIndex);
	SuffixTreeNode* tempNode;

	for (int i = 0; i < (int)substring.length();)
	{
		int amount = curNode->edgeString.length();
		int j = 0;
		for (j = 0; j < amount; j++)
		{
			if (curNode->edgeString[j] != substring[i+j])
			{
				curNode->breakApart(j, (*alphabetDict)[substring[i + j-1]]);
				return curNode;
			}
		}
		i += j;
		tempNode = curNode->GetChild(AlphabetIndex(substring[i]));
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

SuffixTreeNode* SuffixTreeEngine::NodeHops(SuffixTreeNode* node, std::string beta)
{
	for (int i = 0; i <= (int)beta.length();)
	{
		int amount = node->edgeString.length();
		if (i+amount > (int)beta.length())
		{
			int breakpoint = (int)beta.length() - i;
			node->breakApart(breakpoint, (*alphabetDict)[node->edgeString[breakpoint]]);
			break;
		}
		if (i+amount == (int)beta.length())
		{
			return node;
		}
		else
		{
			i += amount;
			char endingChar = beta[i];
			node = node->GetChild((*alphabetDict)[endingChar]);
		}
		
	}
	return node;
}

void SuffixTreeEngine::DisplayBWT()
{
	std::cout << std::endl<< "BWT" << std::endl;
	DisplayBWT(root);
	std::cout << std::endl;
}

void SuffixTreeEngine::DisplayBWT(SuffixTreeNode* curNode)
{
	if (curNode->isEnd)
	{
		int value = curNode->leafId -1;
		if (value < 0)
			std::cout << "$" << std::endl;
		else
			std::cout << this->input[value] << std::endl;
	}

	for (int i = 0; i < this->alphabetCharCount; i++)
	{
		SuffixTreeNode* tempNode = curNode->GetChild(i);
		if (tempNode != nullptr)
			DisplayBWT(tempNode);
	}
}

int SuffixTreeEngine::AlphabetIndex(char c) const
{
	return (*alphabetDict)[c];
}

void SuffixTreeEngine::InsertEndOfSuffix(SuffixTreeNode* curNode, int i)
{
	u = curNode;
	std::string restOfString = this->input.substr(i + curNode->Depth);
	
	if (restOfString != "" && restOfString.length() > curNode->edgeString.length())
	{
		clock_t begin5 = clock();
		curNode = curNode->AddChild(AlphabetIndex(this->input[curNode->Depth + i]), restOfString.substr(0,restOfString.size()), curId);
		curId += restOfString.size();
		std::cout << i << "while loop took: " << (clock() - begin5) / static_cast<double>(CLOCKS_PER_SEC) << std::endl;
	}

	curNode->isEnd = true;
	curNode->leafId = i;
}


