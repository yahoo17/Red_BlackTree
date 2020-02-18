#ifndef NODE_H
#define NODE_H
#include "ValueDataStruct.h"
/*���ﲹ��һ�£��������ʱ��key��key����������������ô�õ�key��value��
���ǿ�������
template<typename T>
T * getValue(Node *node )
{
	return node.value
}
���ư�
*/
#define RED false
#define BLACK true
class Node
{
public:
	Node();
	Node(int key);
	~Node();
public:

	Node* leftChild;
	Node* rightChild;
	bool color;
	int key;
	int value;
private:
	
	ValueDataStruct* realvalue;
public:
	
	
};

Node::Node(int key):key(key),leftChild(nullptr),rightChild(nullptr),value(key),color(BLACK)
{

}
Node::Node():leftChild(nullptr),rightChild(nullptr),color(BLACK)
{
	
}

Node::~Node()
{
}
#endif