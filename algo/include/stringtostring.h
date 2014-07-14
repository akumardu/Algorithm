/*
Given the word "HEAD" and the word "TAIL," write code and/or describe using computer science algorithms how you would transform from the word HEAD to the word TAIL. 
Each change must be by only one letter, you cannot change the letter in a given position twice, and each new word must be a valid word.
*/

#include<simpledict.h>
#include<iostream>
#include<trie.h>

bool transformex(std::string start, std::string end, trie* Dict);
bool supertransformex(std::string start, std::string end, trie* Dict, int index);

bool transform()
{
	trie* Dict = trie::CreateTrie(); 
	std::string start = "head";
	std::string end = "tail";
	
	return transformex(start,end,Dict);
}

// Use Breadth-First Search since this resembles that.
// Need to use a queue
//Actually the problem represents shortest path from one node to another
bool supertransformex(std::string start, std::string end, trie* Dict, int index)
{
	if(!strcmp(start.c_str(),end.c_str()))
		return true;
	for(unsigned int i =0; i < start.length(); i++)
	{
		if(i == index)
			continue;
		char temp = start[i];
		if(start[i] == end[i])
			continue;
		//start[i] = end[i];
		for(char ch = 'a'; ch<='z'; ch++)
		{
			if(ch != start[i])
				start[i] = ch;
			else
				continue;
			if(!Dict->find(start))
			{
				start[i] = temp;
				continue;
			}
			else
			{
				if(supertransformex(start,end,Dict,i))
				{
					std::cout<<start<<std::endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool transformex(std::string start, std::string end, trie* Dict)
{
	if(!strcmp(start.c_str(),end.c_str()))
		return true;
	for(unsigned int i =0; i < start.length(); i++)
	{
		char temp = start[i];
		if(start[i] == end[i])
			continue;
		start[i] = end[i];
		if(!Dict->find(start))
		{
			start[i] = temp;
			continue;
		}
		else
		{
			if(transformex(start,end,Dict))
			{
				std::cout<<start<<std::endl;
				return true;
			}
		}
	}
	return false;
}
