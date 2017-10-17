#include <iostream>
//extern "C"
//{
#include "MsgQ.h"
//}
using namespace std;

void main()
{
	cout << "Queues test\n";
	MSG_Q_ID id1 = msgQCreate(1,1,1);
	MSG_Q_ID id2 = msgQCreate(2,1,1);

	cout << id1 << "  " << id2 << endl;

}