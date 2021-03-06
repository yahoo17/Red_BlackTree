#ifndef NODE_H
#define NODE_H
#include "ValueDataStruct.h"
/*这里补充一下，建红黑树时，key是key，是索引，具体怎么得到key的value呢
我们可以这样
template<typename T>
T * getValue(Node *node )
{
	return node.value
}
类似吧
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
	//定义一下颜色，红黑树 01树，红用color=0表示；黑用color=1表示；
	bool color;
	int key;
	int value;
private:
	
	ValueDataStruct* realvalue;
public:
	
	
};

Node::Node(int key):key(key),leftChild(nullptr),rightChild(nullptr),value(key),color(RED)
{

}
Node::Node():leftChild(nullptr),rightChild(nullptr),color(RED)
{
	
}

Node::~Node()
{
}
#endif