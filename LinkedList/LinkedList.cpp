// Linked List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include <list>
#include <time.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>

using namespace std;

const int TESTSIZE = 100;
const int REMOVESIZE = 50;
const int INSERTSIZE = 50;
int sortCompare = 0;
int sort2Compare = 0;
int sort3Compare = 0;
int sort4Compare = 0;

void merge(int *arr,const int p, const int q, const int r)
{
	int *target = new int[r-p+1];
	int tp = p, tq = q+1, tr = 0;
	while(tp <= q && tq <= r)
	{
		if(arr[tp] >= arr[tq])
		{
			target[tr] = arr[tp];
			tp++;
			tr++;
		}
		else
		{
			target[tr] = arr[tq];
			tq++;
			tr++;
		}
		sort2Compare++;
	}
	int len1 = r-tq+1;
	int len2 = q-tp+1;
	if(tp > q)
	{
		for(int i = 1; i <= len1; i++)
		{
			target[tr] = arr[tq];
			tq++;
			tr++;
		}
	}
	else
	{
		for(int i = 1; i <= len2; i++)
		{
			target[tr] = arr[tp];
			tp++;
			tr++;
		}
	}
	int pos = p;
	for(int i = 0; i < r-p+1; i++)
	{
		arr[pos] = target[i];
		pos++;
	}
	delete [] target;
}
void mergeSort(int *arr, int p, int r)
{
	if(p < r)
	{
		int mid = (p+r)/2;
		mergeSort(arr,p,mid);
		mergeSort(arr,mid+1,r);
		merge(arr,p,mid,r);
	}
}

int split(int* p, int low, int high){
	int i = low;
	int x = p[low];
	for(int j = low+1; j <= high; ++j)
	{
		if(p[j] < x)
		{
			i++;
			if(i!= j)
			{
				swap(p[i],p[j]);				
			}
		}
		sort3Compare++;
	}	
	swap(p[low],p[i]);
	return i;
}
void quickSort(int*p,int low, int high){
	if(low < high)
	{
		int w = split(p,low,high);
		quickSort(p,low,w-1);
		quickSort(p,w+1,high);
	}
}

class Node{
public:
	int val;
	Node *pNext;
	Node(){
		val = NULL;
		pNext = NULL;
	}
	Node(int val){
		this->val = val;
		pNext = NULL;
	}
	Node(int val,Node *p){
		this->val = val;
		this->pNext = p;
	}
};

class LinkedList{
private:
	Node *pNode;
	int size;
public:
	LinkedList(){
		pNode = NULL;
		size = 0;
	}
	~LinkedList(){
		while(pNode != NULL)
		{
			Node *pTemp = pNode;
			pNode = pNode->pNext;
		    delete pTemp;
		}
	}
	Node* begin(){
		return pNode;
	}
	Node* end(){
		if(pNode == NULL)
			return NULL;
		else
		{
			Node* pTemp = pNode;
			while(pTemp->pNext != NULL)
			{
				pTemp = pTemp->pNext;
			}
			return pTemp;
		}
	}
	Node* at(int num){
		if (num < 0 || num >= size )
		{
			return NULL;
		}
		Node *pTemp = pNode;
		for(int i = 0; i < num; ++i)
		{
			pTemp = pTemp->pNext;
		}
		return pTemp;
	}
	int getSize(){	//return the size of the linked list
		return size;
	}
	void add(int val){	// add val at the end of the list
		if(pNode == NULL)
		{
			pNode = new Node(val);
		}
		else 
		{
			end()->pNext = new Node(val);
		}
		++size;
	}
	int insert(int k, int val){	// insert val into the position before the node of k and return 0; or return -1 if k beyond the list 
		if(k < 0 || k >= size){return -1;}
		else if(k == 0)
		{
			pNode = new Node(val,pNode);			
		}
		else
		{
			Node *pTemp = at(k-1);
			pTemp->pNext = new Node(val,pTemp->pNext);
		}
		++size;
		return 0;
	}
	int remove(int k){	//remove the node in position k and return 0; or return -1 if k beyond the list span
		if(k < 0 || k >= size){
			return -1;
		}
		else
		{
			if(k == 0)
			{
				pNode = pNode->pNext;
			}
			else
			{
				Node *pTemp1 = at(k-1);
				Node *pTemp2 = at(k);
				pTemp1->pNext = pTemp2->pNext;
				delete pTemp2;
			}
			--size;
			return 0;
		}
	}
	void sort(){	// bubble sort algorith applied; element will be sorted in ascending order
		sortCompare = 0;
		for(int i = size-1; i > 0; --i)
		{		
			Node *pTemp1 = pNode;
			Node *pTemp2 = pNode->pNext;
			for(int j = 0; j < i; ++j)
			{				
				if(pTemp1->val > pTemp2->val)
				{
					swap(pTemp1->val,pTemp2->val);
				}
				pTemp1 = pTemp1->pNext;
				pTemp2 = pTemp2->pNext;
				sortCompare++;
			}
		}
	}
	void sort2(){	//mergesort applied, ; element will be sorted in ascending order
		sort2Compare = 0;
		if(size > 1)
		{
			int *pArray = new int[size]; // array used to store temp values of the linked list
			Node *pTemp = pNode;
			for(int i = 0; i < size; ++i)
			{
				pArray[i] = pTemp->val;
				pTemp = pTemp->pNext;
			}
			mergeSort(pArray, 0, size);
			pTemp = pNode;
			for(int i = size-1; i >= 0; --i)
			{
				pTemp->val = pArray[i];
				pTemp = pTemp->pNext;
			}
			delete [] pArray;
		}
	}
	void sort3(){	//quicksort applied
		sort3Compare = 0;
		if(size > 1)
		{
			int *pArray = new int[size]; // array used to store temp values of the linked list
			Node *pTemp = pNode;
			for(int i = 0; i < size; ++i)
			{
				pArray[i] = pTemp->val;
				pTemp = pTemp->pNext;
			}
			quickSort(pArray, 0, size-1);
			pTemp = pNode;
			for(int i = 0; i < size; ++i)
			{
				pTemp->val = pArray[i];
				pTemp = pTemp->pNext;
			}
			delete [] pArray;
		}
	}	
};

int AutoTest() // automatic testing for functions of class LinkedList
				//sort(), sort2(), add(), insert(), remove(). 
				//the above five functions will be tested.
{
	list<int> originList;
	LinkedList myList;
	srand((int)time(0));
	for(int i = 0; i < TESTSIZE ; ++i)
	{
		int temp = rand()%100;
		originList.push_back(temp);
		myList.add(temp);
	}
	//comparing based test below
	//testing for func add()
	if(originList.size() && myList.getSize())
	{
		list<int>::iterator originIt = originList.begin();
		Node* pmyList = myList.begin();
		for(int i = 0; i < myList.getSize(); i++)
		{
			if(*originIt == pmyList->val)
			{
				originIt++;
				pmyList = pmyList->pNext;
			}
			else
			{
				cout<<"add testing failed!"<<endl;
				return -1;
			}
		}
		cout<<"add testing succeed!"<<endl;
	}
	else
	{
		cout<<"add testing failed!"<<endl;
		return -1;
	}

	//testing for func sort()
	myList.sort();
	originList.sort();
	if(originList.size() == myList.getSize())
	{
		list<int>::iterator originIt = originList.begin();
		Node* pmyList = myList.begin();
		for(int i = 0; i < TESTSIZE; i++)
		{
			if(*originIt == pmyList->val)
			{
				originIt++;
				pmyList = pmyList->pNext;
			}
			else
			{
				cout<<"sort testing failed!"<<endl;
				return -1;
			}
		}
		cout<<"sort testing succeed!"<<endl;
	}
	else
	{
		cout<<"sort testing failed!"<<endl;
		return -1;
	}

	//testing for func remove()
	for(int i = 0; i < REMOVESIZE; ++i)
	{
		int temp = rand()%REMOVESIZE;
		list<int>::iterator originIt = originList.begin();
		for(int j = 0; j < temp; ++j)
		{
			++originIt;
		}		
		myList.remove(temp);		
		originList.erase(originIt);
	}
	if(originList.size() == myList.getSize())
	{
		list<int>::iterator originIt = originList.begin();
		Node* pmyList = myList.begin();
		for(int i = 0; i < myList.getSize(); i++)
		{
			if(*originIt == pmyList->val)
			{
				originIt++;
				pmyList = pmyList->pNext;
			}
			else
			{
				cout<<"remove testing failed!"<<endl;
				return -1;
			}
		}
		cout<<"remove testing succeed!"<<endl;
	}
	else
	{
		cout<<"remove testing failed! size unequal!"<<endl;
		return -1;
	}
	
	
	//testing for func sort2()
	myList.sort2();
	originList.sort();
	if(originList.size() == myList.getSize())
	{
		list<int>::iterator originIt = originList.begin();
		Node* pmyList = myList.begin();
		for(int i = 0; i < myList.getSize(); i++)
		{
			if(*originIt == pmyList->val)
			{
				originIt++;
				pmyList = pmyList->pNext;
			}
			else
			{
				cout<<"sort2 testing failed!"<<endl;
				return -1;
			}
		}
		cout<<"sort2 testing succeed!"<<endl;
	}
	else
	{
		cout<<"sort2 testing failed!"<<endl;
		return -1;
	}

	//testing for func insert()
	for(int i = 0; i < INSERTSIZE; ++i)
	{
		int pos = rand() % myList.getSize();
		int val = rand() % 100;
		list<int>::iterator it = originList.begin();
		for(int j = 0; j < pos; ++j)
		{
			++it;
		}
		myList.insert(pos,val);
		originList.insert(it,val);
	}
	if(originList.size() == myList.getSize())
	{
		list<int>::iterator originIt = originList.begin();
		Node* pmyList = myList.begin();
		for(int i = 0; i < myList.getSize(); i++)
		{
			if(*originIt == pmyList->val)
			{
				originIt++;
				pmyList = pmyList->pNext;
			}
			else
			{
				cout<<"insert testing failed!"<<endl;
				return -1;
			}
		}
		cout<<"insert testing succeed!"<<endl;
	}
	else
	{
		cout<<"insert testing failed!"<<endl;
		return -1;
	}

}
void SortComparingTest(){	//comparing the performance of four different sorting implementations
							//notice that bubblesort algorithm is applied for both sort() and sort4() 
							//but sort4() copy the list into an array which to work on in order to test the performance
	LinkedList myList1;
	LinkedList myList2;
	LinkedList myList3;
	srand((int)time(0));
	for(int i = 0; i < 3000 ; ++i)
	{
		int temp = rand()%1000;
		myList1.add(temp);
		myList2.add(temp);
		myList3.add(temp);
	}	
	myList1.sort();
	myList2.sort2();
	myList3.sort3();
	cout<<"sorting algorithm performance comparing under the same condition:"<<endl;
	cout<<"sort() <bubblesort> comparing times for elements: "<<sortCompare<<endl;
	cout<<"sort2() <mergesort> comparing times for elements: "<<sort2Compare<<endl;
	cout<<"sort3() <quicksort> comparing times for elements: "<<sort3Compare<<endl;
}
int main(int argc, _TCHAR* argv[])
{
	AutoTest();
	SortComparingTest();
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}

