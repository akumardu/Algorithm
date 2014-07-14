#include<iostream>
#include<string>
#include<fstream>
#include<vector>

class simpledict
{
public:
	simpledict(){
		std::ifstream file;
		file.open("res/dict1.txt");
		if(file.good())
		{
			while(!file.eof())
			{
				std::string str;
				std::getline(file,str);
				mDict.push_back(str);
			}
			file.close();
		}
	}
	bool find(std::string inputString)
	{
		for(unsigned int i=0;i<mDict.size(); i++)
		{
			if(!strcmp(inputString.c_str(),mDict[i].c_str()))
			{
				return true;
			}
		}
		return false;
	}
private:
	std::vector<std::string> mDict;
};
