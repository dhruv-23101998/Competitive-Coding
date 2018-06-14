#include <bits/stdc++.h>
using namespace std;
char s1[300005],s2[300005];
const double pi=4*atan(1);
typedef complex<double> base;
vector<base> omega;
vector<int> bitrev;
long long fft,k;
void initialisefft(long long n,int sign)
{
	fft=n;
	omega.resize(n);
	bitrev.resize(n);
	bitrev[0]=0;
	k=0;
	while((1<<k)<n)
	k++;
	for(int i=1;i<n;i++)
	bitrev[i]=(bitrev[i>>1] >> 1) | ((i & 1) << k-1);
	double angle=2.0*pi/n;
	for(int i=0;i<n;i++)
	omega[i]=base(cos(i*angle),sign*sin(i*angle));
}
void performfft(vector<base> &a)
{
	long long n=(long long)a.size();
	for(int i=0;i<n;i++)
	if(i<bitrev[i])
	swap(a[i],a[bitrev[i]]);
	base omeg,twiddle,x;
	for(long long m=2;m<=n;m<<=1)
	{
		base w=omega[fft/m];
		for(int i=0;i<n;i+=m)
		{
			omeg=1;
			for(int j=0;j<(m>>1);j++)
			{
				twiddle=a[i+j+(m>>1)]*omeg;
				x=a[i+j];
				a[i+j]=x+twiddle;
				a[i+j+(m>>1)]=x-twiddle;
				omeg=omeg*w;
			}
		}
	}
}
void multiply(const vector<long long> &a,const vector<long long> &b,vector<long long> &ans)
{
	vector<base> dfta(a.begin(),a.end());
	vector<base> dftb(b.begin(),b.end());
	long long n=1;
	while(n<2*max(a.size(),b.size()))
	n<<=1;
	dfta.resize(n);
	dftb.resize(n);
	initialisefft(n,1);
	performfft(dfta);
	performfft(dftb);
	for(int i=0;i<n;i++)
	dfta[i]=dfta[i]*dftb[i];
	initialisefft(n,-1);
	performfft(dfta);
	ans.resize(n);
	for(int i=0;i<n;i++)
	ans[i]=(long long)(dfta[i].real()/n+0.5);
}
int main()
{
	int t,n;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s %s",s1,s2);
		vector<long long> a,b,ans;
		n=strlen(s1);
		for(int i=n-1;i>=0;i--)
		a.push_back((int)s1[i]-'0');
		n=strlen(s2);
		for(int i=n-1;i>=0;i--)
		b.push_back((int)s2[i]-'0');
		multiply(a,b,ans);
		a.clear();
		for(int i=0;i<ans.size();i++)
		{
			int x=ans[i],j=1;
			ans[i]=x%10;
			x/=10;
			while(x)
			{
				if(i+j>ans.size()-1)
				ans.resize(i+j+1);
				ans[i+j]+=x%10;
				x/=10;
				j++;
			}
		}
		for(int i=ans.size()-1;i>=0;i--)
		a.push_back(ans[i]);
		int i=0;
		while(a[i]==0 && i<a.size())
		i++;
		if(i==a.size())
		printf("0");
		for(;i<a.size();i++)
		printf("%lld",a[i]);
		printf("\n");
	}
	return 0;
}
