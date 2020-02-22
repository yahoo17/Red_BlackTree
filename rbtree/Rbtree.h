#ifndef RBTREE_H
#define RBTREE_H
#include "Node.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <windows.h>
#include <stdio.h>
using namespace std;
BOOL SetConsoleColor(WORD wAttributes);
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
	//左右旋转
	void leftRotate(Node* cur, Node* root);
	void rightRotate(Node* cur, Node* root);
public:
	//插入相关的
	void insert(int key,Node * & root);
	void insertFixUp(Node* node,Node *root);
	//使用方法，curNode的father通过返回的指针得到，curNode的uncle通过传进去的uncle得到
	Node * findFatherAndUncle(int curNodeKey, Node* root,Node * &father,Node*  & uncle,Node * &grandfather);
	Node* findFather(int curNodeKey, Node* root);
public:
	//打印相关的
	void printIn_order(Node* root)const;
	inline void printNode(Node* node)const
	{
		if (node->color == RED)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			/*	cout << "键是" << node->key << " 值是" << node->value << endl;*/
			cout << node->key << " ";
			SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		}

		else
			cout << node->key << " ";
	}
	void printByLevel(Node* node,int level)const;
};
void Rbtree::rightRotate(Node* cur, Node* root)
{
	Node* father = findFather(cur->key, root);
	if (father != nullptr)
	{
		if (father->leftChild == cur)
		{
			father->leftChild = cur->leftChild;
		}
		else
			father->rightChild = cur->leftChild;
	}
	Node* temp = cur->leftChild->rightChild;
	cur->leftChild->rightChild = cur;
	cur->leftChild = temp;


}
void Rbtree::leftRotate(Node *cur,Node *root)
{
	Node* father =findFather(cur->key, root);
	if (father != nullptr)
	{
		if (father->leftChild == cur)
		{
			father->leftChild = cur->rightChild;
		}
		else
			father->rightChild =cur->rightChild;
	}
	
	Node* temp = cur->rightChild->leftChild;
	cur->rightChild->leftChild = cur;
	cur->rightChild = temp;
	

}
Node* Rbtree::findFather(int curNodeKey, Node* root)
{
	Node* father = nullptr;
	int count = 1;

	while (root->key != curNodeKey)
	{

		
		father = root;
		if (curNodeKey < root->key)
			root = root->leftChild;
		else
			root = root->rightChild;
		count++;
	}
	if (count <= 1)
	{
		father = nullptr;
		
	}
	else
	{
		return father;
	}
	////没有父亲
	//if (root->key == curNodeKey)
	//	return nullptr;
	//while (curNodeKey != root->leftChild->key && curNodeKey != root->rightChild->key)
	//{
	//	
	//	if (curNodeKey <= root->key)
	//		root = root->leftChild;
	//	else
	//		root = root->rightChild;

	//}
	//
	//return root;
	//root 是指向curNode的父节点的指针
}
Node* Rbtree::findFatherAndUncle(int curNodeKey, Node* root,Node * &father,Node*  &uncle, Node*& grandfather)
{
	
	int count = 1;
	
	while (root->key!=curNodeKey)
	{

		grandfather = father;
		father = root;
		if (curNodeKey < root->key)
			root = root->leftChild;
		else
			root = root->rightChild;
		count++;
	}
	if (count <= 1)
	{
		father = nullptr;
		grandfather = nullptr;
		uncle = nullptr;
	}
	if (count <=2)
	{
		grandfather = nullptr;
		uncle = nullptr;
		return father;
	}
	else
	{
		if (grandfather->leftChild == father)
			uncle = grandfather->rightChild;
		else
			uncle = grandfather->leftChild;
		return father;
	}
	
	
	
	//root 是指向curNode的父节点的指针
	

}
void Rbtree::insertFixUp(Node* node,Node * root)
{
	/*
	① 情况说明：被插入的节点是根节点。
	  处理方法：直接把此节点涂为黑色。
	② 情况说明：被插入的节点的父节点是黑色。
      处理方法：什么也不需要做。节点被插入后，仍然是红黑树。
	③ 情况说明：被插入的节点的父节点是红色。
      处理方法：分六种情况
	  */

	//第一种情况，被插入的节点是根节点	
	if (root == node)
	{
		node->color = BLACK;
		return;
	}
	//情况二
	Node* father = nullptr;
	father = findFather(node->key, root);
	if (father->color == BLACK)
		return;

	Node* uncle = nullptr;
	Node* grandfather = nullptr;

	findFatherAndUncle(node->key, root, father,uncle,grandfather);
	
	
	//父亲红色 叔叔黑色的四种情况
	//“ /”这种形状
	if (father->color == RED && (uncle==nullptr||uncle->color == BLACK)&&father->leftChild==node&&father==grandfather->leftChild)
	{
		father->color = BLACK;
		grandfather->color = RED;
		rightRotate(grandfather, root);
	}
	//“\”这种形状		

	else if (father->color == RED && (uncle == nullptr || uncle->color == BLACK) && father->rightChild == node && father == grandfather->rightChild)
		{
			father->color = BLACK;
			grandfather->color = RED;
			leftRotate(grandfather, root);
		}
	//三角形
	else if (father->color == RED && (uncle==nullptr||uncle->color == BLACK )&& father->rightChild == node&&father==grandfather->leftChild)
	{
		
		leftRotate(father, root);
		insertFixUp(father, root);

	}
	else if (father->color == RED && (uncle == nullptr || uncle->color == BLACK) && father->leftChild == node && father == grandfather->rightChild)
	{

		rightRotate(father, root);
		insertFixUp(father, root);

	}
	//叔叔父亲都是红色
	else if (father->color == RED && uncle->color == RED)
	{
		father->color = BLACK;
		uncle->color = BLACK;
		grandfather->color = RED;
		insertFixUp(grandfather, root);
	}
	
}
void Rbtree::printByLevel(Node* node,int level)const
{
	vector<Node*> oneLevel;
	vector<Node*> twoLevel;
	oneLevel.push_back(node);
	for (int i = 0; i < level; i++) 
	{
		cout << "第" << i << "层:"<<endl;
		for (auto x : oneLevel)
		{
			printNode(x);
			if (x->leftChild != nullptr)
				twoLevel.push_back(x->leftChild);
			if (x->rightChild != nullptr)
				twoLevel.push_back(x->rightChild);
		}
		cout << endl;
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
void Rbtree::insert(int key,Node * &root)
{
	
	//非递归实现的
	if (root == nullptr)
	{
		root = new Node(key);
		root->color = BLACK;
		count++;
		return;
	}
	Node* cur = root;
	Node* father = nullptr;
	bool leftOrRight;
	while (cur!=nullptr)
	{
		father = cur;
		if (key < cur->key)
		{
			cur = cur->leftChild;
			leftOrRight = false;
		}
		else
		{
			cur = cur->rightChild;
			leftOrRight = true;
		}

	}
	//!!!这个bug，我醉了
	if (leftOrRight==false)
	{
		father->leftChild = new Node(key);
		father->leftChild->color = RED;
		insertFixUp(father->leftChild, root);

	}
				
	else
		
	{
		father->rightChild = new Node(key);
		father->rightChild->color = RED;
		insertFixUp(father->rightChild, root);

	}
	
	count++;
	
	return;

	//递归实现的insert
	/*if (root == nullptr)
	{
		root = new Node(key);
		root->color =RED;
		count++;
		return;
	}

	if (key <= root->key)
		insert(key, root->leftChild);
	else
		insert(key, root->rightChild);*/
}
BOOL SetConsoleColor(WORD wAttributes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;

	return SetConsoleTextAttribute(hConsole, wAttributes);
}
Rbtree::Rbtree():m_root(nullptr),count(0)
{
}

Rbtree::~Rbtree()
{
}

#endif // 

