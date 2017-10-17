#include<stdio.h>
#include "Int.h"

void Imp1_f1()
{
	printf("imp1 f1\n");
}
void Imp2_f1()
{
	printf("imp2 f1\n");
}
void Imp1_f2()
{
	printf("imp1 f2\n");
}
void Imp3_f2()
{
	printf("imp2 f2\n");
}

void Generic_f1()
{
	printf("generic f1\n");
}

void Generic_f2()
{
	printf("generic f2\n");
}

I1 CreateI1(int val)
{
	I1 res;
	if( (val%3) == 0)
	{
		res.f1 = Imp1_f1;
		res.f2 = Imp1_f2;
	}
	else if ( (val %3) == 1)
	{
		res.f1 = Imp1_f1;
		res.f2 = Generic_f2;
	}
	else
	{
		res.f1 = Generic_f1;
		res.f2 = Imp3_f2;
	}
	return res;
}

