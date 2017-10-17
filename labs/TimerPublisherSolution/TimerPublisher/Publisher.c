#include "publisher.h"

static void Init(Publisher *me)
{
	me->count = 0;
}

static int Register(Publisher *me,Subscriber *s)
{
	if(MAX_SUBSCRIBERS == me->count)
		return -1;
	me->subscribers[me->count++] = s;
	return 0;
}

static int UnRegister(Publisher *me,Subscriber *s)
{
	int i;
	for(i=0;i<MAX_SUBSCRIBERS;i++)
	{
		if(me->subscribers[i] == s)
		{
			me->subscribers[i] = me->subscribers[--(me->count)];
			return 0;
		}
	}
	return -1;
}

static void NotifyAll(Publisher *me)
{
	int i;
	for(i=0;i<me->count;i++)
	{
		me->subscribers[i]->update();
	}
}

Publisher *CreatePublisher()
{
	Publisher *p=(Publisher *)malloc(sizeof(Publisher));
	p->init = &Init;
	p->NotifyAll = &NotifyAll;
	p->Register = &Register;
	p->UnRegister = &UnRegister;
	p->init(p);
	return p;
}

