#include<windows.h>
#include "publisher.h"

static Publisher *arr[100];
static int num = 0;

static void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) 
{
	// TODO: implement
}


void InitAppTimer()
{
	// TODO: implement
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
	// TODO: implement
}
