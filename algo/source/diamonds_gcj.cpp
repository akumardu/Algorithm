#include<iostream>
#include "graph.h"

void diamonds_inheritance()
{
	unsigned int count = 0,netCount=0;
	std::cin>>count;
	netCount = count;
	while(count--)
	{
		unsigned int numOfNodes = 0;
		std::cin>>numOfNodes;
		graph* g = new graph(numOfNodes);
		for(unsigned int i= 0; i < numOfNodes; i++)
		{
			unsigned int numLinks = 0,outEdge = 0;
			std::cin>>numLinks;
			while(numLinks--)
			{
				std::cin>>outEdge;
				g->addEdge(i,outEdge-1,1);
			}
		}
		std::cout<<"Case #"<<netCount -count<<": ";
		if(g->isCyclePresent())
			std::cout<<"Yes\n";
		else
			std::cout<<"No\n";
	}
}