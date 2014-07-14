#include "misc.h"

template<class T>
void merge(T* arr, T*aux, unsigned int start, unsigned int mid, unsigned int end)
{
	unsigned int i = start, j = mid+1, k = start;
	for(unsigned int lk = 0; lk <= end; lk++)
		aux[lk] = arr[lk];
	for(;k<=end; k++)
	{
		if(i > mid) arr[k] = aux[j++];
		else if (j > end) arr[k] = aux[i++];
		else if(aux[i] < aux[j]) arr[k] = aux[i++];
		else arr[k] = aux[j++];
	}
	//printArra(arr+start,end-start + 1);
}

template<class T>
void mSort(T* arr, T* aux, unsigned int start, unsigned int end)
{
	if(end <= start) return;
	
	//Always calculate average in this way
	unsigned int mid = start + (end - start)/2;
	
	mSort(arr,aux, start,mid);
	mSort(arr,aux,mid+1,end);

	//Check if already sorted
	if(arr[mid] <= arr[mid+1]) return;
	merge(arr,aux,start,mid,end);
}

template<class T>
void mergesort(T* arr,unsigned int length)
{
	T* aux = new T[length];
	mSort(arr,aux,0,length-1);
	//printArra(aux,length);
	delete[] aux;
}
