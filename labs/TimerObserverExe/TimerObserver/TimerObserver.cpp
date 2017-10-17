#include<iostream>
#include<vector>
#include<windows.h>
#include "stdafx.h"

using namespace std;

class Observer {   
protected:
	int count;
public:
	Observer():count(0){}
    virtual void update() = 0;
};

class Subject {                      
   vector<class Observer*> views;    
   int value;
public:
   void attach( Observer* obs ) 
   { 
	   // TODO: add the observer to the list
   }
   void notify()
   {
	   // TODO: send all the observers the notification
   }
};

class A:public Observer
{

public:
	virtual void update()
	{
		count++;
		cout << "A:" << count << endl;
	}
};

class B:public Observer
{
public:
	virtual void update()
	{
		count++;
		cout << "B:" << count << endl;
	}
};

class C:public Observer
{
public:
	virtual void update()
	{
		count++;
		cout << "C:" << count << endl;
	}
};

class ApplicationTimer
{
public:
	static Subject arr[100];
	static int num;

	static void RegisterOnInterval(Observer *p,int interval)
	{
		// TODO: find the places in the array and attach
	}

	static void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) 
	{
		// TODO: send notification at the requiered places
	}
};

Subject ApplicationTimer::arr[100];
int ApplicationTimer::num = 0;

int _tmain(int argc, char *argv[], char *envp[])
{
	A a1;
	B b1;
	C c1;
	ApplicationTimer::RegisterOnInterval(&a1,500);
	ApplicationTimer::RegisterOnInterval(&b1,200);
	ApplicationTimer::RegisterOnInterval(&c1,100);


	int Counter=0;
	MSG Msg;
	// OS specific timer 
	UINT TimerId = SetTimer(NULL, 0, 10, &ApplicationTimer::TimerProc);
	while (GetMessage(&Msg, NULL, 0, 0)) {
		DispatchMessage(&Msg);
	}

	return 0;
}
