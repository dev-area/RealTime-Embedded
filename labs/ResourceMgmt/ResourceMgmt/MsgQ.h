#ifndef MSMQ_HEADER
#define MSMQ_HEADER

typedef unsigned int MSG_Q_ID;
typedef int STATUS;


MSG_Q_ID msgQCreate(int maxMsgs,int maxMsgLength, int options);

STATUS msgQDelete(MSG_Q_ID msgQId);

STATUS msgQSend (MSG_Q_ID msgQId, char * buffer, unsigned int nBytes, int timeout, int priority );

STATUS msgQReceive(MSG_Q_ID msgQId, char * buffer, unsigned int maxNBytes, int timeout );

#endif