#include"stdafx.h"
using namespace std;

int* KMPNext(char* P)//ÇóKMPNEXTÊý×é
{
	size_t m=strlen(P),j=0;
	int* N=new int[m];
	int t=N[0]=-1;
	while(j<m-1)
		if(0>t || P[j]==P[t])
		{
			j++;
			t++;
			N[j]=(P[j]!=P[t])? t:N[t];
		}
		else
			t=N[t];
	return N;
}
int KMPmatch(char* T,char* P)//KMP
{
	int* next = KMPNext(P);
	int n=(int )strlen(T),i=0;
	int m=(int )strlen(P),j=0;
	while((j<m) && (i<n))
	{
		if(0>j || T[i] == P[j])
		{
			i++;
			j++;
		}
		else
		{
			j=next[j];
		}
		if(j==m)
			return i-j;
	}
	delete [] next;
	return -1;
}