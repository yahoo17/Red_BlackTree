#include "Rbtree.h"
#include <iostream>
using namespace std;
void test5()
{
	//左旋的测试
	Rbtree  test2;
	test2.insert(6, test2.m_root);
	test2.insert(4, test2.m_root);
	test2.insert(10, test2.m_root);
	test2.insert(2, test2.m_root);
	test2.insert(5, test2.m_root);
	test2.insert(9, test2.m_root);
	test2.insert(8, test2.m_root);
	test2.insert(11, test2.m_root);
	test2.printIn_order(test2.m_root);
	test2.printByLevel(test2.m_root, 5);
	
	
	
	//test2.printIn_order(test2.m_root);
	//test2.printByLevel(test2.m_root, 5);
	//test2.insert(12, test2.m_root);
	

	
}
void test1()
{
	// 二叉树的插入和打印
	Rbtree  test1;
	


	test1.insert(5, test1.m_root);
	test1.insert(4, test1.m_root);
	test1.insert(23, test1.m_root);
	test1.printByLevel(test1.m_root,2);
	bool a = true;
	cout << sizeof(a);
	return;
	
}
void test2()
{
	//检查查找父亲叔叔祖父功能是不是可行；
	Rbtree test2;

	test2.insert(6, test2.m_root);
	test2.insert(4, test2.m_root);
	test2.insert(10, test2.m_root);
	test2.insert(2, test2.m_root);
	test2.insert(5, test2.m_root);
	Node* uncle = nullptr;
	Node* father = nullptr;
	Node* grandfather = nullptr;
	father=test2.findFatherAndUncle(2, test2.m_root, father,uncle,grandfather);

	test2.printNode(father);
	cout << endl;
	test2.printNode(uncle);
	cout << endl;
	test2.printNode(grandfather);

	//2020/2/20 23:01 测试成功；


}
void test3()
{
	//左旋的测试
	Rbtree test2;

	test2.insert(6, test2.m_root);
	test2.insert(4, test2.m_root);
	test2.insert(10, test2.m_root);
	test2.insert(2, test2.m_root);
	test2.insert(5, test2.m_root);
	test2.leftRotate(test2.m_root->leftChild, test2.m_root);
	test2.printByLevel(test2.m_root,4);
	//2020/2/20 23:40
}
void test4()
{
	//右旋的测试
	Rbtree test2;

	test2.insert(6, test2.m_root);
	test2.insert(4, test2.m_root);
	test2.insert(10, test2.m_root);
	test2.insert(2, test2.m_root);
	test2.insert(5, test2.m_root);
	test2.insert(9, test2.m_root);
	test2.insert(8, test2.m_root);
	test2.insert(12, test2.m_root);
	test2.insert(11, test2.m_root);
	test2.insert(13, test2.m_root);
	test2.rightRotate(test2.m_root->rightChild, test2.m_root);
	test2.printByLevel(test2.m_root, 5);
}