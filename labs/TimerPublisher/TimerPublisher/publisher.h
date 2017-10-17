
#include "subscriber.h"

#define MAX_SUBSCRIBERS 10

typedef struct _Publisher
{
	Subscriber *subscribers[MAX_SUBSCRIBERS];
	int count;
	void (*init)(struct _Publisher *me);
	int (*Register)(struct _Publisher *me,Subscriber  *s);
	int (*UnRegister)(struct _Publisher *me,Subscriber  *s);
	void (*NotifyAll)(struct _Publisher *me);
}Publisher;

