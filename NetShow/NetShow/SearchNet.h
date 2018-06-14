#pragma once
#ifndef _SEARCHNET_
#define _SEARCHNET_

typedef struct _SNetMsg{
	//char name[300];
	char ip[32];
	char mask[32];
	char getway[32];
}SNetMsg;

class CSearchNet
{
public:
	CSearchNet(void);
	~CSearchNet(void);
	int SearchNet(SNetMsg *netmsg[],int *num);

};
#endif