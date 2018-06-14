#include <bits/stdc++.h>
using namespace std;
int marray[101];
vector<int> vx,vy;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	scanf("%d",marray+i);
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	for(int k=0;k<n;k++)
	{
		int x=marray[i]*marray[j]+marray[k];
		int y=marray[i]*(marray[j]+marray[k]);
		vx.push_back(x);
		if(marray[i]==0)
		continue;
		vy.push_back(y);
	}
	long long int ans=0;
	sort(vx.begin(),vx.end());
	sort(vy.begin(),vy.end());
	for(int i=0;i<vx.size();i++)
	{
		int x=lower_bound(vy.begin(),vy.end(),vx[i])-vy.begin();
		int y=upper_bound(vy.begin(),vy.end(),vx[i])-vy.begin();
		ans+=(long long)(y-x);
	}
	printf("%lld\n",ans);
	return 0;
}
