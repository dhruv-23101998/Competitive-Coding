#include <bits/stdc++.h>
using namespace std;
const int d=256;
const int q=101;
int main()
{
	int n,h,p,t;
	bool firstcase=true;
	while(scanf("%d",&n)!=EOF)
	{
		if(!firstcase)
		printf("\n");
		firstcase=false;
		string s,m;
		getline(cin,s);
		getline(cin,s);
		getline(cin,m);
		int y=s.length();
		p=t=0;
		h=1;
		int j,x=m.length();
		for(int i=1;i<y;i++)
		h=(h*d)%q;
		for(int i=0;i<y;i++)
		{
			p=(p*d+s[i])%q;
			t=(t*d+m[i])%q;
		}
		for(int i=0;i<=x-y;i++)
		{
			if(p==t)
			{
				for(j=0;j<y;j++)
				if(m[i+j]!=s[j])
				break;
				if(j==y)
				printf("%d\n",i);
			}
			if(i<x-y)
			t=(d*(t-h*m[i])+m[i+y])%q;
			if(t<0)
			t+=q;
		}
	}
	return 0;
}
