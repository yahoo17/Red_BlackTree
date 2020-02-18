/*
	这个类是空类，应该是key-value的value
	在node里面，一个是key，一个是value，value应该是指向ValueDataStruct的指针
*/
#include <string>
using namespace  std ;
class ValueDataStruct
{
public:
	ValueDataStruct();
	~ValueDataStruct();
	string name;
private:

};

ValueDataStruct::ValueDataStruct()
{
}

ValueDataStruct::~ValueDataStruct()
{
}