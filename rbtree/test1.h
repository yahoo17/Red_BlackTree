#include "Rbtree.h"
#include <iostream>
using namespace std;
void test1()
{
	// �������Ĳ���ʹ�ӡ
	Rbtree  test1;
	


	test1.insert(5, test1.m_root);
	test1.insert(4, test1.m_root);
	test1.insert(23, test1.m_root);
	test1.printByLevel(test1.m_root);
	return;
	
}