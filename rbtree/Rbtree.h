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
	//������ת
	void leftRotate(Node* cur, Node* root);
	void rightRotate(Node* cur, Node* root);
public:
	//������ص�
	void insert(int key,Node * & root);
	void insertFixUp(Node* node,Node *root);
	//ʹ�÷�����curNode��fatherͨ�����ص�ָ��õ���curNode��uncleͨ������ȥ��uncle�õ�
	Node * findFatherAndUncle(int curNodeKey, Node* root,Node * &father,Node*  & uncle,Node * &grandfather);
	Node* findFather(int curNodeKey, Node* root);
public:
	//��ӡ��ص�
	void printIn_order(Node* root)const;
	inline void printNode(Node* node)const
	{
		if (node->color == RED)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			/*	cout << "����" << node->key << " ֵ��" << node->value << endl;*/
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
	////û�и���
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
	//root ��ָ��curNode�ĸ��ڵ��ָ��
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
	
	
	
	//root ��ָ��curNode�ĸ��ڵ��ָ��
	

}
void Rbtree::insertFixUp(Node* node,Node * root)
{
	/*
	�� ���˵����������Ľڵ��Ǹ��ڵ㡣
	  ��������ֱ�ӰѴ˽ڵ�ͿΪ��ɫ��
	�� ���˵����������Ľڵ�ĸ��ڵ��Ǻ�ɫ��
      ��������ʲôҲ����Ҫ�����ڵ㱻�������Ȼ�Ǻ������
	�� ���˵����������Ľڵ�ĸ��ڵ��Ǻ�ɫ��
      �����������������
	  */

	//��һ�������������Ľڵ��Ǹ��ڵ�	
	if (root == node)
	{
		node->color = BLACK;
		return;
	}
	//�����
	Node* father = nullptr;
	father = findFather(node->key, root);
	if (father->color == BLACK)
		return;

	Node* uncle = nullptr;
	Node* grandfather = nullptr;

	findFatherAndUncle(node->key, root, father,uncle,grandfather);
	
	
	//���׺�ɫ �����ɫ���������
	//�� /��������״
	if (father->color == RED && (uncle==nullptr||uncle->color == BLACK)&&father->leftChild==node&&father==grandfather->leftChild)
	{
		father->color = BLACK;
		grandfather->color = RED;
		rightRotate(grandfather, root);
	}
	//��\��������״		

	else if (father->color == RED && (uncle == nullptr || uncle->color == BLACK) && father->rightChild == node && father == grandfather->rightChild)
		{
			father->color = BLACK;
			grandfather->color = RED;
			leftRotate(grandfather, root);
		}
	//������
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
	//���常�׶��Ǻ�ɫ
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
		cout << "��" << i << "��:"<<endl;
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
	
	//�ǵݹ�ʵ�ֵ�
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
	//!!!���bug��������
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

	//�ݹ�ʵ�ֵ�insert
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

