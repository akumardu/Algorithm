
#include<vector>
#include<utility>
#include<iostream>
#include<cstring>
#include "heap.h"
#include<queue>
#include<set>
#include<stack>

typedef unsigned int uint;

#ifndef GRAPH_H
#define GRAPH_H

class graph
{
public:
	graph(unsigned int numOfNodes)
	{
		
		while(numOfNodes--)
		{
			std::vector< std::pair<unsigned int, long> > temp;
			data.push_back(temp);
		}
		//ivstreet specific
		maxCuts = 0;
	}

	void addEdge(unsigned long start, unsigned int end, long weight)
	{
		std::pair<unsigned int, long> temp(end, weight);
		data[start].push_back(temp);
	}

	void process_vertex_early(int index)
	{
	}

	void process_vertex_late(int index)
	{

	}
	void process_edge(int vertexA, int vertexB, int leaf_count)
	{
		if(leaf_count && leaf_count%2 == 0)
		{
			//std::cout<<"Found One from : "<<vertexA<<"  to "<<vertexB<<std::endl;
			//ivstreet specific
			maxCuts++;
		}
	}

	void dfsGraph(bool* visited, bool* processed, int* entry_time, int* exit_time, int time, int index, int& leaf_count)
	{
		visited[index] = true;
		time++;
		process_vertex_early(index);
		int valid_leaf_count = 0,valid_children_leaf = 0;
		entry_time[index] = time;
#ifdef DEBUG
		//printf("N: %d\n",index);
#endif
		for(unsigned int i = 0; i < data[index].size(); i++)
		{
			if(!visited[data[index][i].first])
			{
				int local_leaf_count = 0;
				dfsGraph(visited,processed, entry_time, exit_time, time, data[index][i].first,local_leaf_count);
				process_edge(index, data[index][i].first,local_leaf_count + 1);
				valid_leaf_count++;
				valid_leaf_count += local_leaf_count;
			}
		}
		leaf_count = valid_leaf_count;

		time++;
		exit_time[index] = time;
		processed[index] = true;
	}
	void dfs()
	{
		int numOfNodes = data.size();
		int time = 0;
		bool* visited = new bool[numOfNodes];
		bool* processed = new bool[numOfNodes];
		int* entry_time = new int[numOfNodes];
		int* exit_time = new int[numOfNodes];
		std::memset(visited,0,sizeof(bool)*numOfNodes);
		std::memset(processed,0,sizeof(bool)*numOfNodes);
		std::memset(entry_time,0,sizeof(int)*numOfNodes);
		std::memset(exit_time,0,sizeof(int)*numOfNodes);
		
		int leaf_count = 0;
		for(int i = 0;i<numOfNodes; i++)
			if(!visited[i])
			{
				dfsGraph(visited,processed,entry_time,exit_time,time, i, leaf_count);
			}
	}

	bool dfsGraphCycle(bool* visited, int index)
	{
		visited[index] = true;

		for(unsigned int i = 0; i < data[index].size(); i++)
		{
			if(!visited[data[index][i].first])
			{
				if(dfsGraphCycle(visited,data[index][i].first))
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	//Works for diamond problem. For others need to optimize it further.
	bool isCyclePresent()
	{
		int numOfNodes = data.size();
		bool* visited = new bool[numOfNodes];
		std::memset(visited,0,sizeof(bool)*numOfNodes);
		//visited[0] = true;
		for(int i = 0;i<numOfNodes; i++)
		{
			if(!visited[i])
			{
				if(dfsGraphCycle(visited, i))
					return true;
			}
			std::memset(visited,0,sizeof(bool)*numOfNodes);
		}
		return false;
	}
	void singleSourceShortestPath(unsigned int source, long** distance, int** outPath)
	{
		long* dist = new long[data.size()];
		std::memset(dist,1000000,data.size()*sizeof(int));
		int* prev = new int[data.size()];
		std::memset(prev,0,data.size());

		dist[source] = 0;
		prev[source] = -1;
		std::set< std::pair< long , int> > vertex_queue;
		vertex_queue.insert(std::make_pair(0,source));
		while(!vertex_queue.empty())
		{
			int weight = vertex_queue.begin()->first;
			int vertex = vertex_queue.begin()->second;

			vertex_queue.erase(vertex_queue.begin());
			for(unsigned int i = 0; i < data[vertex].size(); i++)
			{
				int destVert = data[vertex][i].first;
				int destWeight = data[vertex][i].second;
				if(dist[destVert] > (weight + destWeight))
				{
					vertex_queue.erase(std::make_pair(dist[destVert],destVert));
					dist[destVert] = weight + destWeight;
					prev[destVert] = vertex;
					vertex_queue.insert(std::make_pair(dist[destVert],destVert));
				}
			}

		}
		(*distance) = dist;
		(*outPath) = prev;

	}

	long long primsMinSpanTree()
	{
		long* dist = new long[data.size()];
		std::memset(dist,100000000,data.size()*sizeof(int));
		int* color = new int[data.size()];
		std::memset(color,0,data.size()*sizeof(int));
		std::set< std::pair<long,int> > vertex_queue;
		vertex_queue.insert(std::make_pair(0,1));
		long long result = 0;
		while(!vertex_queue.empty())
		{
			int weight = vertex_queue.begin()->first;
			int vertex = vertex_queue.begin()->second;
			result += weight;
			vertex_queue.erase(vertex_queue.begin());
			for(unsigned int i = 0; i < data[vertex].size(); i++)
			{
				int destVert = data[vertex][i].first;
				int destWeight = data[vertex][i].second;
				if(color[destVert] == 0 && dist[destVert] > (destWeight))
				{
					vertex_queue.erase(std::make_pair(dist[destVert],destVert));
					dist[destVert] = destWeight;
					vertex_queue.insert(std::make_pair(dist[destVert],destVert));
				}
			}
			color[vertex] = 1;

		}
		return result;
	}

	unsigned int maxPossibleCuts(){return maxCuts;}

	//returning connected components via bfs
	void bfs(std::vector< std::vector<int> >& result)
	{
		unsigned int numofnodes = data.size();
		bool* discovered = new bool[numofnodes];
		for(unsigned int i = 0; i < numofnodes; i++)
			discovered[i] = false;
		std::queue<int> queue;
		for(unsigned int i = 0; i < numofnodes; i++)
		{
			if(discovered[i])
				continue;
			queue.push(i);
			discovered[i] = true;
			std::vector<int> temp;
			while(!queue.empty())
			{
				int node = queue.front();
				queue.pop();
				temp.push_back(node);
				for(unsigned int i =0; i < data[node].size(); i++)
				{
					if(!discovered[data[node][i].first])
					{
						discovered[data[node][i].first] = true;
						queue.push(data[node][i].first);
					}
				}
			}
			result.push_back(temp);
		}
	}


	//Topological sort
	void topological_sort_util(unsigned int index, bool* visited, std::stack<unsigned int> &st)
	{
		visited[index] = true;

		for(unsigned int i = 0; i < data[index].size(); i++)
		{
			unsigned int neighbor = data[index][i].first;
			if(!visited[neighbor])
				topological_sort_util(neighbor,visited,st);
		}
		st.push(index);
	}

	void topological_sort()
	{
		std::stack<unsigned int> st;
		bool* visited = new bool[data.size()];
		for(unsigned int i = 0; i < data.size(); i++)
			visited[i] = false;
		
		for(unsigned int i = 0; i< data.size(); i++)
		{
			if(!visited[i])
				topological_sort_util(i,visited,st);
		}

		while(!st.empty())
		{
			unsigned int top = st.top();
			std::cout<<top<<std::endl;
			st.pop();
		}
	}


private:
	std::vector< std::vector< std::pair<unsigned int, long> > > data;
	//ivstreet specific
	unsigned int maxCuts;
};

class unDirectedGraph : public graph
{
public:
	unDirectedGraph(unsigned int numofNodes):graph(numofNodes)
	{
	}
	void addUndirectedEdge(unsigned int start, unsigned int end, unsigned int weight)
	{
		addEdge(start,end,weight);
		addEdge(end,start,weight);
	}
};
#endif
