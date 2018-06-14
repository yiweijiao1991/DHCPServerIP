//mad by yiweijiao 
#include "StdAfx.h"
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#include <iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")
#include "SearchNet.h"
CSearchNet::CSearchNet(void)
{
}

CSearchNet::~CSearchNet(void)
{
}
//yiweijiao
//***********************************************************
//�������ƣ�SearchNet
//�������ܣ� ��ȡ������������Ϣ
//���������num ��������С
//����������netmsg���ݱ��滺���� num:ɨ�赽������
//**********************************************************
int CSearchNet::SearchNet(SNetMsg *netmsg[],int *num)
{
	int i = 0;
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter=NULL;
	DWORD dwRetVal;

	pAdapterInfo=(IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	ULONG ulOutBufLen=sizeof(IP_ADAPTER_INFO);
	//�жϻ�����
	if (netmsg == NULL)
	{
		num = 0;
		return 0;
	}
	//��ȡ������Ϣ
	if (GetAdaptersInfo(pAdapterInfo,&ulOutBufLen)==ERROR_BUFFER_OVERFLOW)
	{
		free(pAdapterInfo);
		pAdapterInfo=(IP_ADAPTER_INFO *)malloc(ulOutBufLen);
	}
	if ((dwRetVal=GetAdaptersInfo(pAdapterInfo,&ulOutBufLen))==NO_ERROR)
	{
		pAdapter=pAdapterInfo;

		while(pAdapter)
		{
	
			//printf("Adapter Driver:\t%s\n",pAdapter->Description);		
			if (pAdapter->DhcpEnabled)
			{
				//��������
				if (i >=*num)
				{
					*num = i;
					return i;
				}
				//ȥ��Ĭ��ֵ
				if ((strcmp(pAdapter->DhcpServer.IpAddress.String,"0.0.0.0")==0)||(strcmp(pAdapter->DhcpServer.IpAddress.String,"255.255.255.255")==0))
				{
					pAdapter=pAdapter->Next;
					continue;
				}
				//sprintf(netmsg[i].name,"%s",pAdapter->Description);
				//����ip
				sprintf(netmsg[i]->ip,pAdapter->DhcpServer.IpAddress.String);
				
				i++;
			}
			pAdapter=pAdapter->Next;	
			
		}
	}
	*num = i;
	free(pAdapterInfo);
	return i;
}