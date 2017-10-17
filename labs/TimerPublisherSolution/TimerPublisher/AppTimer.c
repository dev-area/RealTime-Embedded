#include<windows.h>
#include "publisher.h"

static Publisher *arr[100];
static int num = 0;

static void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) 
{
	arr[num]->NotifyAll(arr[num]);
	num++;
	if(num == 100) 
		num = 0;
}


void InitAppTimer()
{
	int i;
	for(i=0;i<100;i++)
	{
		arr[i] = CreatePublisher();
	}
}

void StartAppTimer()
{
	MSG Msg;
	// OS specific timer
	UINT TimerId = SetTimer(NULL, 0, 10, &TimerProc);
	while (GetMessage(&Msg, NULL, 0, 0)) {
		DispatchMessage(&Msg);
	}
}

void RegisterOnInterval(Subscriber *s,int interval)
{
	int i;
	int place = interval/10;
	for(i=1;i<=100;i++)
	{
		if( (i % place) == 0)
			arr[i - 1]->Register(arr[i-1],s);
	}
}
