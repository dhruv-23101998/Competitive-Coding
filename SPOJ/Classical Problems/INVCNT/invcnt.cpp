#include <bits/stdc++.h>
using namespace std;
int marray[200001],bit[200001],num;
map<int,int> cordcomp;
int query(int idx)
{
	int sum=0;
	while(idx>0)
	{
		sum+=bit[idx];
		idx-=idx & (-idx);
	}
	return sum;
}
void update(int n,int idx)
{
	while(idx<=n)
	{
		bit[idx]++;
		idx+=idx & (-idx);
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		vector<int> v;
		map<int,int> exist;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",marray+i);
			if(exist[marray[i]]==0)
			{
				exist[marray[i]]++;
				v.push_back(marray[i]);
			}
		}
		num=0;
		sort(v.begin(),v.end());
		for(int i=0;i<v.size();i++)
		cordcomp[v[i]]=++num;
		long long int invcnt=0;
		for(int i=0;i<n+1;i++)
		bit[i]=0;
		for(int i=n;i>=1;i--)
		{
			invcnt+=(long long)query(cordcomp[marray[i]]-1);
			update(num,cordcomp[marray[i]]);
		}
		printf("%lld\n",invcnt);
	}
	return 0;
}
