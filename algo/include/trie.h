#pragma once
#include<iostream>
#include<string>
#include<fstream>

#define alphabets 27
#define hyphen 26

class trie
{
public:
	trie()
	{
		for(int i = 0; i < alphabets; i++)
			children[i] = NULL;
		isWord = false;
	}
	~trie()
	{
		for(int i = 0; i < alphabets; i++)
			if(children[i] != NULL) 
				delete children[i];
	}
	void setIsWord(bool inIsWord){isWord = inIsWord;}
	bool getIsWord(){return isWord;}
	void setChildren(int index, trie* child){children[index] = child;}
	trie* getChildren(int index){return children[index];}
	bool find(std::string word)
	{
		trie* root = this;
		for(unsigned int i = 0; i < word.length(); i++)
		{
			if(word[i] != '-')
			{
				if(root->getChildren(word[i] - 'a') == NULL)
					return false;
				root = root->getChildren(word[i] -'a');
			}
			else
			{
				if(root->getChildren(hyphen) == NULL)
					return false;
				root = root->getChildren(hyphen);
			}
		}
		return root->getIsWord();
	}
	static trie* CreateTrie()
	{
		trie* root = new trie();
		std::ifstream file;
		file.open("res/dict1.txt");
		if(file.good())
		{
			while(!file.eof())
			{
				std::string str;
				std::getline(file,str);
				CreateTrie(root,str);
			}
			file.close();
		}
		return root;
	}
	static void CreateTrie(trie* root, std::string word)
	{
		if(word.length() == 0)
			return;
		for(unsigned int i = 0; i < word.length(); i++)
		{
			if(word[i] != '-')
			{
				if(root->getChildren(word[i] - 'a') == NULL)
				{
					trie* child = new trie();
					root->setChildren(word[i] - 'a', child);
				}
				root = root->getChildren(word[i] - 'a');
			}
			else
			{
				if(root->getChildren(hyphen) == NULL)
				{
					trie* child = new trie();
					root->setChildren(hyphen,child);
				}
				root = root->getChildren(26);
			}
		}
		root->setIsWord(true);
	}
private:
	bool isWord;
	trie* children[alphabets];
};