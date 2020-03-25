#include "SuffixTreeEngine.h"

#include <utility>
#include <ostream>
#include <iostream>

SuffixTreeEngine::SuffixTreeEngine(std::string input, std::list<char> alphabet)
{
	alphabetCharCount = alphabet.size() + 1;
	alphabetDict = new std::unordered_map<char, int>(alphabetCharCount);
	int i = 1;
	alphabet.sort();
	for (char element : alphabet)
	{
		(*alphabetDict)[element] = i++;
	}
	this->input = std::move(input) + "$";
	this->root = new SuffixTreeNode(' ', alphabetCharCount, -1);
	
}

void SuffixTreeEngine::BuildTree()
{
	for (int i = 0; i < this->input.size(); i++)
	{
		InserSubString(this->input.substr(i, input.size() - i));
	}
}

void SuffixTreeEngine::PrintTree()
{
	SuffixTreeNode* tempNode;
	for (int i = 0; i < this->alphabetCharCount; i++)
	{
		tempNode = root->GetChild(i);
		if (tempNode != nullptr)
		{
			//tempNode->Display();
			PrintTree(tempNode);
		}
	}
}

void SuffixTreeEngine::InserSubString(std::string substring)
{
	SuffixTreeNode* tempNode;
	SuffixTreeNode *curNode = root;
	int index = 0;
	bool insertComplete = false;
	while (index < substring.size() && !insertComplete)
	{
		char curChar = substring[index];
		tempNode = curNode->GetChild(AlphabetIndex(curChar));
		if (tempNode == nullptr)
		{
			if (curChar == '$')
			{
				//end of dat string;
				curNode->isEnd = true;
			}
			else
			{
				//lets handle dat fresh insert...
				while (index < substring.size()-1)
				{
					curNode->AddChild(AlphabetIndex(substring[index]), substring[index], 1);
					curNode = curNode->GetChild(AlphabetIndex(substring[index]));
					index++;
				}
				curNode->isEnd = true;
			}
			insertComplete = true;
		}
		else
		{
			curNode = tempNode;
			index++;
		}
	}
}

int SuffixTreeEngine::AlphabetIndex(char c)
{
	return (*alphabetDict)[c];
}

void SuffixTreeEngine::PrintTree(SuffixTreeNode* curNode)
{
	curNode->Display();
	if (curNode->isEnd)
		std::cout << "$" << std::endl;
	for(int i = 0; i < this->alphabetCharCount; i++)
	{
		SuffixTreeNode* tempNode = curNode->GetChild(i);
		if (tempNode != nullptr)
			PrintTree(tempNode);
	}
}
