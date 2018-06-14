#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
map<int,int> cordcomp;
int marray[100001],bitl[100001],bitr[100001];
int cnt1[100001],cnt2[100001];
int num;
int query(int *bit,int idx)
{
	int sum=0;
	while(idx>0)
	{
		sum+=bit[idx];
		idx-=idx & (-idx);
	}
	return sum;
}
void update(int n,int *bit,int idx)
{
	while(idx<=n)
	{
		bit[idx]++;
		idx+=idx & (-idx);
	}
}
int main()
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
	for(int i=0;i<n+1;i++)
	bitl[i]=bitr[i]=0;
	long long int cnt=0;
	for(int i=1;i<=n;i++)
	{
		cnt1[i]=query(bitl,num)-query(bitl,cordcomp[marray[i]]);
		update(num,bitl,cordcomp[marray[i]]);
	}
	for(int i=n;i>=1;i--)
	{
		cnt2[i]=query(bitr,cordcomp[marray[i]]-1);
		update(num,bitr,cordcomp[marray[i]]);
	}
	for(int i=1;i<=n;i++)
	cnt+=(ll)cnt1[i]*(ll)cnt2[i];
	printf("%lld\n",cnt);
	return 0;
}
