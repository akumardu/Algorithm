#include<iostream>
#include<algorithm>
using namespace std;
#define MOD 1000000007
#define ft first
#define sd second
#define VI vector<int>
#define VLL vector<long long int>
#define PII pair<int,int>
#define pb push_back
#define rsz(v,n) v.resize(n)
// input and output
#define scan(x) scanf("%d",&x)
#define scanll(x) scanf("%lld",&x)
#define ll long long int
#define rep(i,x,y) for(i=x;i<y;i++)
#define print(x) printf("%d\n",x)
#define printll(x) printf("%lld\n",x)
#define all(v) v.begin(),v.end()
#define ms(v) memset(v,0,sizeof(v))
#define FOR(i,a,b)  for(i=a;i<b;i++)
#define f_in(st) freopen(st,"r",stdin)
#define f_out(st) freopen(st,"w",stdout)
#define PIE 3.14159265358979323846264338327950
#ifdef ONLINE_JUDGE
 inline void inp1( int &n )
 {
    n=0;
    int ch=getchar_unlocked();int sign=1;
    while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getchar_unlocked();}
    while(  ch >= '0' && ch <= '9' )
            n = (n<<3)+(n<<1) + ch-'0', ch=getchar_unlocked();
    n=n*sign;
  }
#else
inline void inp1(int &n){
 cin>>n;
}
#endif


#define MAX 101
struct BigNum
{
	int len;
	int d[MAX*2];
}f[MAX];


BigNum mul(BigNum &a,BigNum &b)
{
	BigNum c;
	memset(c.d,0,sizeof(c.d));
	int i,j;
	for(i=0;i<a.len;i++)
		for(j=0;j<b.len;j++)
		{
			c.d[i+j]+=a.d[i]*b.d[j];
		}
		for(i=0;i<MAX*2;i++)
			if(c.d[i]>10)
			{
				c.d[i+1]+=c.d[i]/10;
				c.d[i]%=10;
			}
			for(i=MAX*2-1;c.d[i]==0;i--);
			c.len=i+1;
			return c;
}
bool isdivisible(BigNum&a, int b)
{
	int dividend = 0, carry = 0, pow = 1;
	for(int i = a.len-1; i>= 0; )
	{
		dividend = carry;
		while(dividend < b && i >= 0)
		{
			dividend = dividend*10 + a.d[i];
			i--;
			pow = pow*10;
		}
		//dividend = dividend + carry*pow;
		if(dividend%b != 0 && i < 0)
			return false;
		carry = dividend%b;
	}
	if(dividend%b == 0)
		return true;
	else
		return false;
}
BigNum plus(BigNum &a,BigNum &b)
{
	BigNum c;
	int i,len;
	memset(c.d,0,sizeof(c.d));
	len=a.len>b.len?a.len:b.len;
	for(i=0;i<len;i++)
	{
		c.d[i]+=a.d[i]+b.d[i];
		if(c.d[i]>9)
		{
			c.d[i]-=10;
			c.d[i+1]++;
		}
	}
	if(c.d[len])
		len++;
	c.len=len;
	return c;
}
BigNum binaryincr(BigNum&a)
{
	BigNum c;
	memset(c.d,0,sizeof(c.d));
	int carry = 1;
	for(int i = 0; i < a.len; i++)
	{
		c.d[i] = a.d[i] + carry;
		if(c.d[i] > 1)
		{
			c.d[i] -= 2;
			carry = 1;
		}
		else
			carry = 0;
	}
	if(carry)
		c.d[a.len]=1;
	int len = a.len;
	if(c.d[a.len])
		len++;
	c.len = len;
	return c;
}
void printbignum(BigNum& a)
{
	for(int i = a.len-1; i>= 0; i--)
		cout<<a.d[i];
	cout<<endl;
}
void testBigNum()
{
	int divisor;
	cin>>divisor;
	vector<BigNum> bignums;
	BigNum one;
	memset(one.d,0,sizeof(one.d));
	one.len = 1;
	one.d[0] = 1;
	bignums.push_back(one);
	while(divisor != 0)
	{
		bool found = false;
		for(int i = 0; i < bignums.size(); i++)
		{
			if(isdivisible(bignums[i],divisor))
			{
				found = true;
				printbignum(bignums[i]);
				break;
			}
		}
		if(found)
		{
			cin>>divisor;
			continue;
		}
		BigNum a = bignums[bignums.size() - 1];
		a = binaryincr(a);
		bignums.push_back(a);
		while(!isdivisible(a,divisor))
		{
			a = binaryincr(a);
			bignums.push_back(a);
		}
		printbignum(a);
		cin>>divisor;
	}

}

int compareInt(const void* p1, const void* p2) {
  const int f1 = *(const int*) p1;
  const int f2 = *(const int*) p2;
  if (f1 == f2) return 0;
  return (f1 > f2) ? 1 : -1;
}


void tryagain()
{
	int testcases;
	cin>>testcases;
	while(testcases--)
	{
		int n;
		cin>>n;
		int* arr = new int[n];
		for(int i = 0; i < n; i++)
			cin>>arr[i];
		qsort(arr, n, sizeof arr[0], compareInt);
		bool killed = false;
		int i = 0,j=0;
		int miss = 0;
		int count = 1;
		for( i = -1; i < n;)
		{
			
			if((count)%7 != 0)
			{
				i++;
				if(i<n && (arr[i] - j - miss) <= 0)
				{
					killed = true;
					break;
				}
			}
			else
			{
				count = 0;
				miss++;
			}
			
			j++;
			count++;
		}
		if(killed)
		{
			printf("Goodbye Rick\n");
			printf("%d\n",i);
		}
		else
		{
			printf("Rick now go and save Carl and Judas\n");
		}
	}
}