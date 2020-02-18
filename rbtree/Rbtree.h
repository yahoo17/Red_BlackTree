#ifndef RBTREE_H
#define RBTREE_H
#include "Node.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <windows.h>
#include <stdio.h>
using namespace std;
class Rbtree
{
public:
	Rbtree();
	~Rbtree();

public:
	Node* m_root;
	int count;
public:
	inline Node* getRoot ()const
	{
		return m_root;
	}
public:
	void insert(int key,Node * &root);
	void printIn_order(Node* root)const;
	inline void printNode(Node* node)const
	{
		if (node->color == RED)
		{
		
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			cout << "����" << node->key << " ֵ��" << node->value << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf(" Default color.");
		}
		putchar(10);
	
		
	}
	void printByLevel(Node* node)const;
};
void Rbtree::printByLevel(Node* node)const
{
	vector<Node*> oneLevel;
	vector<Node*> twoLevel;
	oneLevel.push_back(node);
	for (int i = 0; i < log2(count); i++) 
	{
		cout << "��" << i << "��:"<<endl;
		for (auto x : oneLevel)
		{
			printNode(x);
			if (x->leftChild != nullptr)
				twoLevel.push_back(x->leftChild);
			if (x->rightChild != nullptr)
				twoLevel.push_back(x->rightChild);
		}
		oneLevel = twoLevel;
		twoLevel.clear();
	}
	

}
void Rbtree::printIn_order(Node* root)const
{
	if (root == nullptr)
		return;
	if (root->leftChild != nullptr)
	{
		printIn_order(root->leftChild);
	}
	
	printNode(root);
		
	if (root->rightChild != nullptr)
	{
		printIn_order(root->rightChild);
	}

	
}
void Rbtree::insert(int key,Node * & root)
{
	if (root == nullptr)
	{
		root = new Node(key);
		root->color =RED;
		count++;
		return;
	}

	if (key <= root->key)
		insert(key, root->leftChild);
	else
		insert(key, root->rightChild);
	

}
Rbtree::Rbtree():m_root(nullptr),count(0)
{
}

Rbtree::~Rbtree()
{
}

#endif // 
