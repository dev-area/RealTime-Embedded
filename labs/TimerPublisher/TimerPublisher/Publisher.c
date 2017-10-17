#include "publisher.h"

static void Init(Publisher *me)
{
	me->count = 0;
}

static int Register(Publisher *me,Subscriber *s)
{
	// TODO: implement
}

static int UnRegister(Publisher *me,Subscriber *s)
{
	// TODO: implement
}

static void NotifyAll(Publisher *me)
{
	// TODO: implement
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

