#include "MsgQ.h"

static int qID;

MSG_Q_ID msgQCreate(int maxMsgs,int maxMsgLength, int options)
{
	return ++qID;
}

STATUS msgQDelete(MSG_Q_ID msgQId)
{
	return 0;
}

STATUS msgQSend (MSG_Q_ID msgQId, char * buffer, unsigned int nBytes, int timeout, int priority )
{
	return 0;
}

STATUS msgQReceive(MSG_Q_ID msgQId, char * buffer, unsigned int maxNBytes, int timeout )
{
	return 0;
}
