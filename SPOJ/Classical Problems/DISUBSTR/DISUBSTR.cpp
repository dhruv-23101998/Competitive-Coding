#include <bits/stdc++.h>
using namespace std;
char s[1005];
int n,t;
int suffixarray[1005],lcp[1005],inverse[1005];
bool compare(int a,int b)
{
	return (strcmp(s+a,s+b)<0) ? 1 : 0;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",s);
		n=strlen(s);
		for(int i=0;i<n;i++)
		suffixarray[i]=i;
		sort(suffixarray,suffixarray+n,compare);
		for(int i=0;i<n;i++)
		inverse[suffixarray[i]]=i;
		int k=0;
		for(int i=0;i<n;i++)
		{	
			if(inverse[i]==n-1)
			{
				lcp[inverse[i]]=0;
				k=0;
				continue;
			}
			int j=suffixarray[inverse[i]+1];
			while(i+k<n && j+k<n && s[i+k]==s[j+k])
			k++;
			lcp[inverse[i]]=k;
			if(k>0)
			k--;
		}
		int ans=0;
		for(int i=0;i<n;i++)
		{
			int x=(i==0) ? 0 : lcp[i-1];
			ans+=n-suffixarray[i]-x;
		}
		printf("%d\n",ans);
	}
	return 0;
}
