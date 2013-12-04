// Linked List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

using namespace std;


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
public:
	LinkedList(){
		pNode = NULL;
	}
	~LinkedList(){
		while(pNode != NULL)
		{
			Node *pTemp = pNode;
			pNode = pNode->pNext;
		    delete pTemp;
		}
	}
	int size(){	//return the size of the linked list
		if(pNode == NULL)
			return 0;
		else if(pNode != NULL && pNode->pNext == NULL)
			return 1;
		else
		{
			Node *pTemp = pNode;
			int s = 1;
			while(pTemp->pNext != NULL)
			{
				++s;
				pTemp = pTemp->pNext;
			}
			return s;
		}

	}
	void add(int val){	// add val at the end of the list
		if(pNode == NULL)
			pNode = new Node(val);
		else if (pNode != NULL )
		{
			Node *pTemp = pNode;
			while(pTemp->pNext != NULL)
			{
				pTemp = pTemp->pNext;
			}
			pTemp->pNext = new Node(val);
		}
	}
	int insert(int k, int val){	// insert val into the position before the node of k and return 0; or return -1 if k beyond the list 
		if(k < 0 || k >= size()){return -1;}
		else if(k == 0)
		{
			pNode = new Node(val,pNode);
			return 0;
		}
		else
		{
			Node *pTemp = pNode;
			for(int i = 0; i < k-1; ++i)
			{
				pTemp = pTemp->pNext;
			}
			pTemp->pNext = new Node(val,pTemp->pNext);
			return 0;
		}
	}
	int remove(int k){	//remove the node in position k and return 0; or return -1 if k beyond the list span
		if(k < 0 || k >= size()){
			return -1;
		}
		else if ( k == size()-1 && k != 0)
		{
			Node *pTemp = pNode;
			for(int i = 0; i < k-1; ++i)
			{
				pTemp = pTemp->pNext;
			}
			delete pTemp->pNext;
			pTemp->pNext = NULL;
			return 0;
		}
		else if (k == 0)
		{
			if(size()>1)
			{
				Node *pTemp = pNode;
				pNode = pNode->pNext;
				delete pTemp;
			}
			else
			{
				delete pNode;
				pNode = NULL;
			}
			return 0;
		}
		else
		{
			
			Node *pTemp = pNode;
			for(int i = 0; i < k-1; ++i)
			{
				pTemp = pTemp->pNext;
			}
			Node *pDelete = pTemp->pNext;
			pTemp->pNext = pTemp->pNext->pNext;
			delete pDelete;
			return 0;
		}
	}
	void sort(){	// bubble sort algorith applied; element will be sorted in ascending order
		for(int i = size()-1; i > 0; --i)
		{
			Node *pTemp1 = pNode;
			Node *pTemp2 = pNode->pNext;
			for(int j = 0; j < i; ++j)
			{
				if(pTemp1->val > pTemp2->val)
				{
					int tem = pTemp1->val;
					pTemp1->val = pTemp2->val;
					pTemp2->val = tem;
				}
				pTemp1 = pTemp1->pNext;
				pTemp2 = pTemp2->pNext;
			}
		}
	}
	void traverse(){
		if(size() == 0)
		{
			cout<<"No element at all!!"<<endl;
			return;
		}
		Node *pTemp = pNode;
		int num = 0;
		for(int i = 0; i < size(); ++i)
		{
			cout<<"element "<<num++<<" : "<<pTemp->val<<endl;
			pTemp = pTemp->pNext;
		}
	}
	void create(){	//create the linked list according to user's input; input '-1' means complete
		int num;
		while(cin>>num && num != -1)
		{
			this->add(num);
		}
	}
};

int main(int argc, _TCHAR* argv[])
{
	int val;
	int num;
	char ch;
	LinkedList list;
	
	cout<<"enter the values to create the linked list please, type in -1 to terminate:"<<endl;
	list.create();	
	list.traverse();

	cout<<"Enter command to continue:\n";
	cout<<"S for sort,	A for add,	R for remove, I for insert, Q for quit:\n";
	
	
	while(cin>>ch && ch != 'Q')
	{
		switch (ch)
		{
		case 'S':
			cout<<endl<<endl<<"sort testing:"<<endl;	
			list.sort();
			list.traverse();
			cout<<endl;
			break;
		case 'A':
			cout<<"add testing:"<<endl;
			cout<<"enter value you want to add:"<<endl;
			while(cin>>val && val != -1)
			{
				list.add(val);
				list.traverse();
				cout<<endl;
				cout<<"enter value you want to add:"<<endl;
			}
			break;
		case 'R':
			cout<<endl<<endl<<"remove testing:"<<endl;	
			cout<<"enter position number you want to delete:"<<endl;
			while(cin>>val && val != -1){
				list.remove(val);
				list.traverse();
				cout<<endl<<"enter position number you want to delete:"<<endl;;
			}
			break;
		case 'I':
			cout<<endl<<endl<<"insert testing:"<<endl;	
			cout<<"enter position number and value you want to insert:"<<endl;
			while(cin>>num>>val && val != -1){
				list.insert(num,val);
				list.traverse();
				cout<<endl<<"enter position number and value you want to insert:"<<endl;;
			}
		}
		cout<<"Enter command to continue:\n";
		cout<<"S for sort,	A for add,	R for remove, I for insert, Q for quit:\n";
	}

	
	

	system("pause");
	return 0;
}

