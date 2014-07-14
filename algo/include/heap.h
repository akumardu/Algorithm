#include <iostream>
#include <vector>

#ifndef HEAP_H
#define HEAP_H
template <typename T>
class heap
{
public:
	heap(){dataStore.push_back(0);}
	heap(T* arr, unsigned int size)
	{
		for(unsigned int i = 0; i < size ; i++)
			dataStore.push_back(arr[i]);
		for(unsigned int i = size/2 + 1; i >=0; i--)
			bubbleDown(i);
	}
	void insert(T data)
	{
		dataStore.push_back(data);
		bubbleUp(dataStore.size() - 1);
	}
	T extractMin()
	{
		if(isEmpty())
			throw "Empty Heap";
		T temp = dataStore[1];
		exch(1,dataStore.size() - 1); 
		dataStore.pop_back();
		bubbleDown(1);
		return temp;
	}
	T peekMin()
	{
		return dataStore[1];
	}
	bool isEmpty(){return dataStore.size() == 1;}
	void printHeap()
	{
		for(unsigned int i= 1; i < dataStore.size(); i++)
			std::cout<<i<<" : "<<dataStore[i]<<std::endl;
	}
	unsigned int size(){return dataStore.size() - 1;}
	bool remove(T num){
		bool found = false;
		int index = 0;
		for(unsigned int i = 1; i < dataStore.size(); i++)
		{
			if(dataStore[i] == num)
			{
				found = true;
				index = i;
			}
		}
		if(!found)
			return false;
		exch(index,dataStore.size()-1);
		dataStore.pop_back();
		bubbleDown(index);
		return true;
	}
	bool verifyHeap(unsigned int index = 1)
	{
		if(2*index >= dataStore.size())
			return true;
		if(less(2*index,index))
			return false;
		if(((2*index + 1) < dataStore.size()) && less(2*index + 1, index))
			return false;
		bool result = verifyHeap(2*index) ;
		if(result && ((2*index + 1) < dataStore.size()))
			return verifyHeap(2*index + 1);
		else
			return result;
	}

protected:
	//void heapify();
	bool less(int index1, int index2){ return dataStore[index1] < dataStore[index2];}
	void exch(int index1, int index2){T temp = dataStore[index1]; dataStore[index1]=dataStore[index2];dataStore[index2] = temp;}

private:
	void bubbleDown(unsigned int index)
	{
		while(2*index < dataStore.size())
		{
			unsigned int j = 2* index;
			if(j+1 < dataStore.size() && less(j+1,j)) j++;
			if(less(j,index)){
				exch(j,index);
			}
			else
				break;
			index = j;
		}
	}
	void bubbleUp(unsigned int index)
	{
		while(index > 0)
		{
			int j = index/2;
			if(less(index, j))
				exch(index,j);
			else
				break;
			index = j;
		}
	}
	std::vector<T> dataStore;
};

template<typename T>
class maxheap
{
public:
	maxheap()
	{
		dataStore.push_back(0);
	}
	void insert(T data)
	{
		dataStore.push_back(data);
		bubbleUp(dataStore.size() - 1);
	}
	T extractMin()
	{
		if(isEmpty())
			throw "Empty Heap";
		T temp = dataStore[1];
		exch(1,dataStore.size() - 1); 
		dataStore.pop_back();
		bubbleDown(1);
		return temp;
	}
	T peekMin()
	{
		return dataStore[1];
	}
	bool isEmpty(){return dataStore.size() == 1;}
	void printHeap()
	{
		for(unsigned int i= 1; i < dataStore.size(); i++)
			std::cout<<i<<" : "<<dataStore[i]<<std::endl;
	}
	unsigned int size(){return dataStore.size()-1;}
	bool remove(T num){
		bool found = false;
		int index = 0;
		for(unsigned int i = 1; i < dataStore.size(); i++)
		{
			if(dataStore[i] == num)
			{
				found = true;
				index = i;
			}
		}
		if(!found)
			return false;
		exch(index,dataStore.size()-1);
		dataStore.pop_back();
		bubbleDown(index);
		return true;
	}
	bool verifyHeap(int index = 1)
	{
		if(2*index >= dataStore.size())
			return true;
		if(less(2*index,index))
			return false;
		if(((2*index + 1) < dataStore.size()) && less(2*index + 1, index))
			return false;
		bool result = verifyHeap(2*index) ;
		if(result && ((2*index + 1) < dataStore.size()))
			return verifyHeap(2*index + 1);
		else
			return result;
	}

protected:
	//void heapify();
	//bool less(int index1, int index2){ return dataStore[index1] < dataStore[index2];}
	void exch(int index1, int index2){T temp = dataStore[index1]; dataStore[index1]=dataStore[index2];dataStore[index2] = temp;}

private:
	void bubbleDown(unsigned int index)
	{
		while(2*index < dataStore.size())
		{
			unsigned int j = 2* index;
			if(j+1 < dataStore.size() && less(j+1,j)) j++;
			if(less(j,index)){
				exch(j,index);
			}
			else
				break;
			index = j;
		}
	}
	void bubbleUp(unsigned int index)
	{
		while(index > 0)
		{
			int j = index/2;
			if(less(index, j))
				exch(index,j);
			else
				break;
			index = j;
		}
	}
	std::vector<T> dataStore;
protected:
	bool less(int index1, int index2){ return dataStore[index1] > dataStore[index2];}
};
#endif