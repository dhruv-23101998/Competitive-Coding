#include <bits/stdc++.h>
using namespace std;
int marray[10001];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,u,q;
		scanf("%d %d",&n,&u);
		memset(marray,0,sizeof(marray));
		while(u--)
		{
			int l,r,val;
			scanf("%d %d %d",&l,&r,&val);
			marray[l]+=val;
			marray[r+1]-=val;
		}
		for(int i=1;i<n;i++)
		marray[i]+=marray[i-1];
		scanf("%d",&q);
		while(q--)
		{
			int idx;
			scanf("%d",&idx);
			printf("%d\n",marray[idx]);
		}
	}
	return 0;
}
