#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<stdio.h>
#include<iomanip>
#include<stack>
#include<queue>
#include<limits.h>
#include<sstream>

namespace BinarySearchHeapConstruction
{
	using namespace std;
	struct node
	{
		string label;
		int data;
	};
	class labelComparator
	{
	public :
		bool operator()(const node& a, const node& b)
		{
			if(a.label.compare(b.label) < 0)
				return true;
			else return false;
		}
	};
	struct stackinput
	{
		int start;
		int end;
		int index;
	};
	void binarysearchheap()
	{
		int n;
		scanf("%d",&n);
		while(n)
		{
			vector<node> nodes;
			char temp[256];
			int data;
			
			for(int i = 0; i < n; i++)
			{
				node tempnode;
				scanf("%[^/]s",&temp);
				scanf("/%d",&data);
				tempnode.label = temp+1;
				tempnode.data = data;
				nodes.push_back(tempnode);
			}
			sort(nodes.begin(), nodes.end(), labelComparator());
			stack<stackinput> stk;
			string result;
			stackinput s;
			s.start = 0;
			s.end = n-1;
			s.index = 0;
			stk.push(s);
			while(!stk.empty())
			{
				s = stk.top();
				stk.pop();
				if(s.start > s.end)
					continue;
				int max = -1;
				int maxindex = -1;
				for(int i = s.start; i <= s.end; i++)
				{
					if(max < nodes[i].data)
					{
						max = nodes[i].data;
						maxindex = i;
					}
				}
				int rsize = 0;
				if(result.size() == 0)
				{
					char tempa[256];
					//ostringstream temp;  //temp as in temporary
					//temp<<nodes[maxindex].data;
					itoa(nodes[maxindex].data,tempa,10);
					result = result + "(" + nodes[maxindex].label + "/" ;
					result = result + tempa + ")";
					rsize = result.size();
				}
				else
				{
					char tempa[256];
					//ostringstream temp;  //temp as in temporary
					//temp<<nodes[maxindex].data;
					itoa(nodes[maxindex].data,tempa,10);
					string temps;
					temps = temps + "(" + nodes[maxindex].label + "/";
					temps = temps + tempa + ")";
					rsize = temps.size();
					result.insert(s.index,temps);
				}
				stackinput l;
				l.start = s.start;
				l.end = maxindex - 1;
				l.index = s.index + 1;
				stk.push(l);
				stackinput r;
				r.start = maxindex + 1;
				r.end = s.end;
				r.index = s.index + rsize - 1;
				stk.push(r);
				//cout<<result<<endl;
			}
			cout<<result<<endl;

			scanf("%d",&n);
		}
	}

};

namespace hackerearth
{
	using namespace std;
	typedef struct node
	{   
		int key;
		node* prev;
		node* next;
	}node;

	node* createNode(int x)
	{
		node *temp = new node;
		temp->key = x;
		temp->next = temp->prev = NULL;
		return temp;
	}

	node* createList(node* head, int n)
	{
		int x;
		node * last;
		for(int i = 0; i<n ;i++)
		{
			cin>>x;
			if(head == NULL)
			{
				head = createNode(x);
				last = head;
			}
			else
			{
				last->next = createNode(x);
				last->next->prev = last;
				last = last->next;
			}
		}
		return head;
	}

	void deleteNode(node* p)
	{
		p->next->prev = p->prev;

		if(p->prev)
			p->prev->next = p->next;
	}

	node* deleteFromBack(node *p, int cnt)
	{
		while(cnt)
		{
			p = p->prev;
			cnt--;
		}
		p->next = NULL;

		return p;
	}

	node* deleteList(node* head, int k, int n)
	{
		node* p1, *p2;
		int cnt =k;

		p1 = head;
		p2 = p1->next;

		while(p2 && cnt)
		{
			if((p1->key < p2->key) && p1)
			{
				deleteNode(p1);
				if(p2->prev)
					p1 = p2->prev;
				else
				{
					p1 = p2;
					p2 = p2->next;
				}
				cnt--;
			}
			else{
				p1 = p2;
				p2 = p2->next;
			}
		}

		if(cnt )
			p1 = deleteFromBack(p1, cnt);

		while(p1 && p1->prev)
			p1 = p1->prev;

		return p1;
	}

	int removefriends()
	{
		int t, n, k, i;
		node* head =NULL;
		cin>>t;

		while(t--){
			cin>>n>>k;
			head =NULL;
			head= createList(head, n);

			if(n==1)
			{
				cout<<head->key<<endl;
				continue;
			}

			head  = deleteList(head, k, n);

			while(head)
			{
				cout<<head->key<<" ";
				head = head->next;
			}
			cout<<endl;
		}

		return 0;
	}
	
	int hackb()
	{
		//cout << "Hello World!" << endl;
		int test = 0;
		cin>>test;

		while(test--)
		{
			int sz = 0, k = 0;
			cin>>sz;
			cin>>k;
			int c = k;
			vector<int> num(sz,0);
			for(int i = 0 ;i <sz; i++)
			{
				cin>>num[i];
			}
			while(k--)
			{
				bool deletelast = true;
				vector<int>::iterator j = num.begin();
				j++;
				for(vector<int>::iterator i = num.begin(); i != num.end(); i++, j++)
				{
					if(j == num.end())
						break;
					if(*(i) < *(j))
					{
						i = num.erase(i);
						deletelast = false;
						break;
					}
				}
				if(deletelast == true)
				{
					while(k)
					{
						j = num.end();
						j--;
						num.erase(j);
						k--;
					}
				}
			}
			int count = 0;
			for(int i = 0; i < num.size(); i++)
			{
				cout<<num[i]<<" ";
			}
			cout<<endl;
		}
		return 0;
	}

	int swapprob()
	{
		int t,n,i,k;
		cin>>t;
		while(t--){
			cin>>n>>k;
			int* a = new int[n];
			for(i=0;i<n;i++)
				cin>>a[i];
			for(i=0;i<n;i++){
				int pos=i;
				for(int j=i+1;j<n;j++){
					if((j-i)>k)
						break;
					if(a[j]<=a[pos])
						pos=j;
				}
				for(int j=pos;j>i;j--)
					a[j]=(a[j]+a[j-1])-(a[j-1]=a[j]);
				k-=(pos-i);
			}
			for(i=0;i<n;i++)
				cout<<a[i]<<" ";
			cout<<endl;
		}

		return 0;
	}

};

namespace navigationnightmare
{
const int MAXN = 40000, MAXK = 10000;
	struct link
	{
		int farma;
		int farmb;
		int length;
		char dist;
	}links[MAXN+1];
	struct query
	{
		int farma;
		int farmb;
		int queryindex;
		int distance;
		int index;
	}queries[MAXK+1];
	class queryindexcomp
	{
	public:
		bool operator()(query& a, query& b)
		{
			if(a.queryindex < b.queryindex)
				return true;
			else
				return false;
		}
	};
	class indexcomp
	{
	public:
		bool operator()(query& a, query& b)
		{
			if(a.index < b.index)
				return true;
			else
				return false;
		}
	};
	struct point
	{
		int x;
		int y;
	}farms[MAXN+1];
	void calculatePoint(point& a, point& b, int length, char dist)
	{
		b.x = a.x;
		b.y = a.y;
		switch(dist)
		{
		case 'N':
			b.y += length;
			break;
		case 'S':
			b.y = b.y - length;
			break;
		case 'W':
			b.x = b.x - length;
			break;
		case 'E':
			b.x += length;
			break;
		}
	}
	void calculateDistance(map<int,vector<link>>& farmmap, point* farms, int n, int index, bool* visited)
	{
		queue<int> que;
		que.push(index);
		while(!que.empty())
		{
			int ind = que.front();
			que.pop();
			visited[ind] = true;
			for(int i = 0; i < farmmap[ind].size(); i++)
			{
				int nextind = farmmap[ind][i].farmb;
				if(!visited[nextind])
				{
					calculatePoint(farms[ind],farms[nextind],farmmap[ind][i].length, farmmap[ind][i].dist);
					que.push(nextind);
				}
			}
		}
	}
	int calculateCoordDistance(point a, point b)
	{
		int dist = abs(a.x - b.x) + abs(a.y - b.y);
		return dist;
	}
	char returnreversedist(char a)
	{
		switch(a)
		{
		case 'E':
			return 'W';
		case 'W':
			return 'E';
		case 'N':
			return 'S';
		default:
			return 'N';
		}
	}
	void navigation()
	{
		map<int,vector<link> > farmmap;
		int n,m,k;
		cin>>n>>m;
		int* parent = new int[n+1];
		//point* farms = new point[n+1];
		bool * visited = new bool[n+1];
		for(int i = 0; i < n+1; i++)
		{
			parent[i] = i;
			visited[i] = false;
		}
		//link* links = new link[m];
		for(int i = 0; i < m; i++)
		{
			int farma;
			cin>>links[i].farma>>links[i].farmb>>links[i].length>>links[i].dist;
			farma = links[i].farma;
			if(farmmap.find(farma) != farmmap.end())
			{
				farmmap[farma].push_back(links[i]);
			}
			else
			{
				vector<link> temp;
				farmmap[farma] = temp;
				farmmap[farma].push_back(links[i]);
			}
			link temp;
			temp.farma = links[i].farmb;
			temp.farmb = links[i].farma;
			temp.length = links[i].length;
			temp.dist = returnreversedist(links[i].dist);
			if(farmmap.find(temp.farma) != farmmap.end())
			{
				farmmap[temp.farma].push_back(temp);
			}
			else
			{
				vector<link> tempV;
				farmmap[temp.farma] = tempV;
				farmmap[temp.farma].push_back(temp);
			}
		}
		farms[1].x = 0;
		farms[1].y = 0;
		calculateDistance(farmmap,farms,n+1,1, visited);
		cin>>k;
		//query* queries = new query[k];
		for(int i = 0; i < k; i++)
		{
			cin>>queries[i].farma>>queries[i].farmb>>queries[i].queryindex;
			queries[i].distance = -1;
			queries[i].index = i;
		}
		// sort the queries according to queryindex
		sort(queries,queries+k,queryindexcomp());
		int process = 0;
		for(int i = 0; i < k; i++)
		{
			int temp = queries[i].queryindex;
			while(process < m && process < temp)
			{
				int rootb = links[process].farmb;
				while(parent[rootb] != rootb)
					rootb = parent[rootb];
				int roota = links[process].farma;
				while(parent[roota] != roota)
					roota = parent[roota];
				parent[roota] = rootb;
				process++;
			}
			int roota = queries[i].farma,rootb = queries[i].farmb;
			while(parent[roota] != roota)
				roota = parent[roota];
			while(parent[rootb] != rootb)
				rootb = parent[rootb];
			if(roota != rootb)
				queries[i].distance = -1;
			else
				queries[i].distance = calculateCoordDistance(farms[queries[i].farma],farms[queries[i].farmb]);
		}
		sort(queries,queries+k,indexcomp());
		for(int i = 0; i < k; i++)
			cout<<queries[i].distance<<endl;
	}
}


namespace expressions
{
	struct node
	{
		node* left, *right;
		char val;
	}_pool[10000];
	// pool to avoid initialization costs at runtime
	int _ptr = 0;
	
	void init(){_ptr = 0;}
	
	node* createNode(node* left, node* right, char a)
	{
		_pool[_ptr].left = left;
		_pool[_ptr].right = right;
		_pool[_ptr].val = a;
		return &_pool[_ptr++];
	}
	bool islower(char a)
	{
		if(a >= 'a' && a <= 'z')
			return true;
		return false;
	}
	void evaluateExpression()
	{
		int tests;
		cin>>tests;
		while(tests--)
		{
			init();
			string input;
			cin>>input;
			stack<node*> stk;
			queue<node*> que;
			// Create the expression tree
			for(int i = 0; i < input.size(); i++)
			{
				if(islower(input[i]))
				{
					stk.push(createNode(NULL, NULL, input[i]));
				}
				else
				{
					node* left = stk.top();
					stk.pop();
					node* right = stk.top();
					stk.pop();
					stk.push(createNode(left,right,input[i]));
				}
			}
			node* root = stk.top();
			string ans;
			// Level order traversal to get answer
			que.push(root);
			while(!que.empty())
			{
				node* temp = que.front();
				que.pop();
				ans += temp->val;
				if(temp->right != NULL)
					que.push(temp->right);
				if(temp->left != NULL)
					que.push(temp->left);
			}
			reverse(ans.begin(),ans.end());
			cout<<ans<<endl;
		}
	}
}

namespace peking
{
	using namespace std;

	void ncs()
	{
		int tests;
		cin>>tests;
		while(tests--)
		{
			map<int, int> parent;
			int numNodes;
			cin>>numNodes;
			for(int i = 0; i <= numNodes; i++)
				parent[i] = 0;
			for(int i = 0; i < numNodes-1; i++)
			{
				int c, p;
				cin>>p>>c;
				parent[c]=p;
			}
			int nodea, nodeb;
			cin>>nodea>>nodeb;
			int counta=0,countb=0;
			int tempa = nodea,tempb = nodeb;
			while(tempa != 0)
			{
				counta++;
				tempa = parent[tempa];
			}
			while(tempb != 0)
			{
				countb++;
				tempb = parent[tempb];
			}
			tempa = nodea;
			tempb = nodeb;
			if(counta > countb)
			{
				while(counta > countb)
				{
					tempa = parent[tempa];
					counta--;
				}
			}
			else
			{
				while(countb > counta)
				{
					tempb = parent[tempb];
					countb--;
				}
			}
			while(countb != 0)
			{
				if(tempb == tempa)
				{
					cout<<tempb<<endl;
					break;
				}
				tempb = parent[tempb];
				tempa = parent[tempa];
				countb--;
			}
		}
	}

	void hardwood()
	{
		map<string,int> hashmap;
		string input;
		long total = 0;
		while(getline(cin,input))
		{
			//string input(inp);
			if(input == "")
				break;
			total++;
			if(hashmap.find(input) == hashmap.end())
			{
				hashmap[input] = 1;
			}
			else
				hashmap[input] = hashmap[input] + 1;
		}
		for(map<string,int>::iterator it = hashmap.begin(); it!= hashmap.end(); it++)
		{
			printf("%s %.4f\n",it->first.c_str(),it->second*100/double(total));
		}
	}

	int tempInversion()
	{

		int  N, m; 
		int  P, temp, i; 
		while (scanf ( "%d%d" , &N, &m)  &&  N > 0 ) 
		{         
			P = 1 ; 
			while ((P * (P - 1 )) / 2 < m) P++ ;         
			temp = (P * (P - 1 )) / 2 ; 
			for (i = 1 ; i <= N - P; i ++ )             
				printf ( "%d " , i);         
			printf ( "%d " , N - temp + m); 
			for (i = N; i >= N - P + 1 ; i--) 
			{ 
				if (i != N - temp + m)
					printf ( "%d " , i);         
			}

			printf ( "\n" );     
		}

		return  0 ; 
	}
	int count_Inversions(int* arr, int sz)
	{
		int count = 0;
		for(int i = 0; i < sz; i++)
		{
			for(int j = i+1; j < sz; j++)
			{
				if(arr[i] > arr[j])
					count++;
			}
		}
		return count;
	}
	void nextInversion()
	{
		int n;
		long m;
		cin>>n>>m;
		int* vect = new int[50000];
		while(n != -1)
		{
			for(int i = 0; i < n; i++)
				vect[i] = i+1;
			
			do {
				std::next_permutation(vect,vect+n);
			} while ( count_Inversions(vect,n) < m );
			for(int i = 0; i < n; i++)
				cout<<vect[i]<<" ";
			cout<<endl;
			cin>>n>>m;
		}
	}
	void swapper(int* vect, int& end, int maxn, int& start, int swap)
	{
		if(swap)
		{
			for(int i = end, j = end - maxn; i>j; i--,j++)
			{
				int temp = vect[i];
				vect[i] = vect[j];
				vect[j] = temp;
			}
			start = end - maxn;
		}
		else
		{
			for(int i = start, j = start + maxn; i<j; i++,j--)
			{
				int temp = vect[i];
				vect[i] = vect[j];
				vect[j] = temp;
			}
			end = start + maxn;
		}
	}
	void anotherNextInversion()
	{
		long n;
		long m;
		cin>>n>>m;
		long inv = m;
		int* vect = new int[50000];
		while(n != -1)
		{
			for(int i = 0; i < n; i++)
				vect[i] = i+1;
			int swap = 1;
			int start = 0;
			int end = n-1;
			while(m)
			{
				int maxn = 1;
				while((maxn*(maxn+1))/2 < m)
					maxn++;
				if(swap)
					swapper(vect,end,maxn,start,swap);
				else
					swapper(vect,end,m,start,swap);

				if(swap)
					m = (maxn*(maxn+1))/2 - m;
				else
				{
					m = (m*(m+1)/2) - m;
				}
				swap = !swap;
			}
			//cout<<count_Inversions(vect,n)<<endl;
			for(int i = 0; i < n; i++)
				cout<<vect[i]<<" ";
			cout<<endl;
			cin>>n>>m;
			inv = m;
		}
	}

	void gameofconnections()
	{
		long long arc[201];
		arc[0] = 1;
		arc[1] = 0;
		arc[2] = 1;
		for(int i = 3; i < 201; i++)
		{
			if(i%2 == 1)
			{
				arc[i] = 0;
				continue;
			}
			long long sum = 0;
			for(int j = 0; j < i-1; j++)
			{
				sum += arc[j] * arc[i - j - 2];
			}
			arc[i] = sum;
		}
		int num;
		cin>>num;
		while(num != -1)
		{
			cout<<arc[num*2]<<endl;
			cin>>num;
		}
	}

	bool insideCircle(double cx, double cy, double r, double x, double y)
	{
		if((cx-x)*(cx-x) + (cy-y)*(cy-y) - r*r > 1e-6)
			return false;
		else
			return true;
	}
	
	void chocolatechipcookies()
	{
		vector<double> x;
		vector<double> y;
		double tempx, tempy;
		int c = 0;
		while(c++ < 8)
		{
			cin>>tempx>>tempy;
			x.push_back(tempx);
			y.push_back(tempy);
		}

		int max = 0;
		for(int i = 0; i < x.size(); i++)
		{
			for(int j = i+1; j<x.size(); j++)
			{
				double q = sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]) );
				if(2.5*2.5 - q*q/4 < 1e-6)
					continue;
				double cx = (x[i] + x[j])/2 + sqrt(2.5*2.5 - q*q/4 + 1e-6)*(y[i]-y[j])/q;
				double cy = (y[i] + y[j])/2 + sqrt(2.5*2.5 - q*q/4 + 1e-6)*(x[j]-x[i])/q;
				int count = 0;
				for(int k = 0; k < x.size(); k++)
				{
					if(insideCircle(cx,cy,2.5,x[k],y[k]))
						count++;
				}
				//cout<<x[i]<<":"<<y[i]<<":"<<x[j]<<":"<<y[j]<<":"<<count<<endl;
				if(max < count)
					max = count;
				cx = (x[i] + x[j])/2 - sqrt(2.5*2.5 - q*q/4 + 1e-6)*(y[i]-y[j])/q;
				cy = (y[i] + y[j])/2 - sqrt(2.5*2.5 - q*q/4 + 1e-6)*(x[j]-x[i])/q;
				count = 0;
				for(int k = 0; k < x.size(); k++)
				{
					if(insideCircle(cx,cy,2.5,x[k],y[k]))
						count++;
				}
				//cout<<x[i]<<":"<<y[i]<<":"<<x[j]<<":"<<y[j]<<":"<<count<<endl;
				if(max < count)
					max = count;
			}
		}
		cout<<max<<endl;
	}

	void minmax()
	{
		int testcases = 0;
		cin>>testcases;
		while(testcases--)
		{
			int num = 0;
			cin>>num;
			if((num %2) == 1)
			{
				cout<<num<<" "<<num<<endl;
				continue;
			}
			else
			{
				int pow = 2;
				while(num%pow == 0)
				{
					pow = pow * 2;
				}
				pow = pow/2;
				cout<<num-pow+1<<" "<<num+pow-1<<endl;
			}
		}
	}

	void tritilling()
	{
		long* d = new long[31];
		long* a = new long[31];
		for(int i = 0; i < 31; i++)
		{
			d[i] = 0;
			a[i] = 0;
		}
		d[0] = 1;
		a[0] = 0;
		d[1] = 0;
		a[1] = 1;
		for(int i = 2; i < 31; i++)
		{
			a[i] = d[i-1] + a[i-2];
			d[i] = d[i-2] + 2*a[i-1];
		}
		int num = 0;
		while(true)
		{
			cin>>num;
			if(num == -1) break;
			cout<<d[num]<<endl;
		}
	}

#define max(a,b) (((a)>(b))?(a):(b))
	void thetriangle()
	{
		int size = 0;
		cin>>size;
		int**num = new int*[size];
		int** dp = new int*[size];
		int max = 0;
		for(int i = 0; i < size; i++)
		{
			num[i] = new int[i+1];
			dp[i] = new int[i+1];
			for(int j = 0; j <= i; j++)
			{
				cin>>num[i][j];
				if(i == 0)
				{
					dp[i][j] = num[i][j] ;
				}
				else
				{
					if(j==0)
					{
						dp[i][j] = dp[i-1][j] + num[i][j];
					}
					else if(i == j)
					{
						dp[i][j] = dp[i-1][j-1] + num[i][j];
					}
					else
					{
						dp[i][j] = max(dp[i-1][j],dp[i-1][j-1]) + num[i][j];
					}
				}
				if(dp[i][j] > max)
					max = dp[i][j];
			}
		}
		cout<<max<<endl;
	}
	int dist[310][310];
		int dp[310][310];
		int w[310][310];
	void postoffice()
	{
		int numvillages = 0, numpostoffices = 0;
		cin>>numvillages;
		cin>>numpostoffices;
		int villages[400];
		for(int i = 0; i < numvillages; i++)
		{
			scanf("%d",&(villages[i]));
		}
		
		memset(dp,0x3f,sizeof(dp));
		memset(dist,0x3f,sizeof(dist));
		// Finding the lowest cost of placing one postoffice between i and j village
		for(int i = 0; i < numvillages; i++)
		{
			dist[i][i] = 0;
			for(int j = i+1; j < numvillages; j++)
			{
				int mindistance = 3000000;
				for(int k = i; k <= j; k++)
				{
					int distancesum = 0;
					for(int l = i; l <= j; l++)
					{
						distancesum += abs(villages[k] - villages[l]);
					}
					if(distancesum < mindistance)
						mindistance = distancesum;
				}
				dist[i][j] = mindistance;
				cout<<dist[i][j]<<'\t';
			}
			cout<<endl;
		}
		for(int i = 0; i < numpostoffices; i++)
		{
			for(int j = i + 1; j < numvillages; j++)
			{
				if(i == 0)
				{
					dp[i][j] = dist[0][j];
					cout<<dp[i][j]<<'\t';
					continue;
				}
				int mindistance = 30000000;
				for(int k = i-1; k < j ; k++)
				{
					int distance = 0;
					
					distance += dist[k+1][j];
					distance += dp[i-1][k];
					
					if(distance < mindistance)
					{
						mindistance = distance;
					}
				}
				dp[i][j] = mindistance;
				cout<<mindistance<<'\t';
			}
			cout<<endl;
		}
		cout<<dp[numpostoffices-1][numvillages-1]<<endl;
		
		memset(w,0x3f,sizeof(w));
		for (int i=1;i<=numvillages;i++)
		{
			int left=0;
			for (int j=i;j<=numvillages;j++)
			{
				left+=villages[j-1];
				int right=0;
				for (int k=j;k<=numvillages;k++)
				{
					right+=villages[k-1];
					if ((j-i+1)*villages[j-1]-left+right-(k-j+1)*villages[j-1]<w[i][k])	
						w[i][k]=(j-i+1)*villages[j-1]-left+right-(k-j+1)*villages[j-1];

				}
			}
		}
		for(int i = 1; i <= numvillages+1; i++)
		{
			for(int j = 1; j <= numvillages+1; j++)
			{
				cout<<w[i][j]<<'\t';
			}
			cout<<endl;
		}
		memset(dp,0x3f,sizeof(dp));
		dp[0][0]=0;
		int V = numvillages, P = numpostoffices;
		for (int i=1;i<=V;i++)
			for (int j=1;j<=P;j++)
				for (int k=0;k<i;k++)
					if (dp[k][j-1]+w[k+1][i]<dp[i][j])
						dp[i][j]=dp[k][j-1]+w[k+1][i];
		cout << endl;
		for (int i=1;i<=V;i++)
		{
			for (int j=1;j<=V;j++)
				if (dp[i][j]<0x3f3f3f3f)
					printf("%4d",dp[i][j]);
				else
					printf("   M");
			printf("\n");
		} 
		printf("%d\n",dp[V][P]);
	}

	bool validDigit(char a, char b)
	{
		if(a > '2' || a == '0')
			return false;
		if(a == '2' && b > '6')
			return false;
		return true;
	}
	void alphaCode()
	{
		string input;
		cin>>input;
		while(input[0] != '0')
		{
			int* dp = new int[input.size()];
			dp[0] = 1;
			dp[1] = 0;
			if(input.size() > 1 && validDigit(input[0],input[1]))
				dp[1] = 1;
			if(input[1] != '0')
				dp[1]++;
			for(int i = 2; i < input.size(); i++)
			{
				dp[i] = 0;
				if(input[i] != '0')
					dp[i] += dp[i-1];
				if(validDigit(input[i-1],input[i]))
					dp[i] += dp[i-2];
			}
			cout<<dp[input.size()-1]<<endl;
			cin>>input;
		}
	}

	void pallindrome()
	{
		int length;
		string input;
		cin>>length;
		cin>>input;
		int**dp = new int*[length+1];
		for(int i = 0; i < length+1; i++)
		{
			dp[i] = new int[length+1];
			for(int j = 0; j < length+1; j++)
			{
				dp[i][j] = 0;
			}
		}
		for(int t = 1; t < length; t++)
		{
			for(int i = 1, j = i+t; j<=length; i++,j++)
			{
				if(input[i-1] == input[j-1])
					dp[i][j] = dp[i+1][j-1];
				else
				{
					if(dp[i+1][j] > dp[i][j-1])
						dp[i][j] = 1 + dp[i][j-1];
					else
						dp[i][j] = 1 + dp[i+1][j];
				}
				//cout<<dp[i][j]<<'\t';
			}
			//cout<<endl;
		}
		cout<<dp[1][length]<<endl;
	}
	
	int kadane(int* arr, int& start, int& end, int size)
	{
		int maxsofar = arr[0], maxglobal = arr[0];
		int begin_temp=0;
		for(int i = 1; i < size; i++)
		{
			if(maxsofar < 0)
			{
				maxsofar = arr[i];
				begin_temp = i;
			}
			else
			{
				maxsofar += arr[i];
			}
			if(maxglobal < maxsofar)
			{
				maxglobal = maxsofar;
				end = i;
				start = begin_temp;
			}
		}
		return maxglobal;
	}

	void tothemax()
	{
		int size = 0;
		cin>>size;
		int ** arr = new int*[size];
		int*temp = new int[size];
		for(int i = 0; i < size; i++)
		{
			arr[i] = new int[size];
			temp[i] = 0;
			for(int j = 0; j < size; j++)
				cin>>arr[i][j];
		}
		for(int i = 0; i < size; i++)
		{
			for(int j = 1; j < size; j++)
			{
				arr[i][j] += arr[i][j-1];
			}
		}
		int start = 0, end = 0, finalstart=0,finalend=0,finalleft = 0, finalright = 0;
		int finalresult = 0;
		for(int left = 0; left<size; left++)
		{
			for(int right = left; right < size; right++)
			{
				for(int i = 0; i < size; i++)
				{
					if(left != 0)
						temp[i] = arr[i][right] - arr[i][left-1];
					else
						temp[i] = arr[i][right];
				}
				int sum = kadane(temp,start,end,size);
				if(finalresult < sum)
				{
					finalresult = sum;
					finalstart = start;
					finalend = end;
					finalleft = left;
					finalright = right;
				}
			}
		}
		cout<<finalresult<<endl;
	}

	int binarysearchlower(double* overhangs, int size, double key)
	{
		int low = 0, high = size-1;
		while(low <= high)
		{
			int mid = (low + high)/2;
			//if(abs(overhangs[mid] - key) < 0.0001)
			//	return mid;
			if(overhangs[mid] - key > 0.0)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		return low;
	}
	void hangover()
	{
		int max = 300;
		double *overhangs = new double[max];
		overhangs[0] = 0.0;
		for(int i = 1; i < max; i++)
		{
			overhangs[i] = overhangs[i-1] + 1.0/(1+i); 
			cout<<i<<":"<<overhangs[i]<<endl;
		}
		double input;
		cin>>input;
		while(input - 0.0 > 0.01)
		{
			cout<<binarysearchlower(overhangs,max,input)<<" card(s)"<<endl;
			cin>>input;
		}
	}
	
	int merge(char* arr, int start, int middle, int end)
	{
		char* temparr = new char[end-start+1];
		int i = 0,j = 0, ind = 0;
		int inv = 0;
		for( i = start, j = middle+1; i <= middle && j <= end; )
		{
			while(i <= middle && arr[i] <= arr[j])
			{
				temparr[ind] = arr[i];
				i++;
				ind++;
			}
			int temp = j;
			while(j <= end && arr[i] > arr[j])
			{
				temparr[ind] = arr[j];
				j++;
				ind++;
			}
			inv += j - temp ;
			//ind++;
		}
		int b = 1;
		for(;i <= middle;i++)
		{
			temparr[ind] = arr[i];
			ind++;
			if ( !b)
			{
				inv += end - middle ;
			}
			b = 0;
		}
		for(;j<=end; j++)
		{
			temparr[ind] = arr[j];
			ind++;
		}
		for(int i = start; i <= end; i++)
			arr[i] = temparr[i-start];
		delete[] temparr;
		return inv;
	}

	
	int merge_sort(char* arr, int start, int end)
	{
		int inv = 0;
		if(start < end)
		{
			int middle = (start + end) / 2;
			inv += merge_sort(arr,start,middle);
			inv += merge_sort(arr,middle+1,end);
			inv += merge(arr,start,middle,end);
		}
		return inv;
	}
	
	/* This funt merges two sorted arrays and returns inversion count in
	the arrays.*/
	int _merge(char arr[], char temp[], int left, int mid, int right)
	{
		int i, j, k;
		int inv_count = 0;

		i = left; /* i is index for left subarray*/
		j = mid;  /* i is index for right subarray*/
		k = left; /* i is index for resultant merged subarray*/
		while ((i <= mid - 1) && (j <= right))
		{
			if (arr[i] <= arr[j])
			{
				temp[k++] = arr[i++];
			}
			else
			{
				temp[k++] = arr[j++];

				/*this is tricky -- see above explanation/diagram for merge()*/
				inv_count = inv_count + (mid - i);
			}
		}

		/* Copy the remaining elements of left subarray
		(if there are any) to temp*/
		while (i <= mid - 1)
			temp[k++] = arr[i++];

		/* Copy the remaining elements of right subarray
		(if there are any) to temp*/
		while (j <= right)
			temp[k++] = arr[j++];

		/*Copy back the merged elements to original array*/
		for (i=left; i <= right; i++)
			arr[i] = temp[i];

		return inv_count;
	}

	/* An auxiliary recursive function that sorts the input array and
	returns the number of inversions in the array. */
	int _mergeSort(char arr[], char temp[], int left, int right)
	{
		int mid, inv_count = 0;
		if (right > left)
		{
			/* Divide the array into two parts and call _mergeSortAndCountInv()
			for each of the parts */
			mid = (right + left)/2;

			/* Inversion count will be sum of inversions in left-part, right-part
			and number of inversions in merging */
			inv_count  = _mergeSort(arr, temp, left, mid);
			inv_count += _mergeSort(arr, temp, mid+1, right);

			/*Merge the two parts*/
			inv_count += _merge(arr, temp, left, mid+1, right);
		}
		return inv_count;
	}

	int mergeSort(char arr[], int array_size)
	{
		char *temp = (char *)malloc(sizeof(char)*array_size);
		return _mergeSort(arr, temp, 0, array_size - 1);
	}

	void dnasort()
	{
		int length = 0, num = 0;
		cin>>length;
		cin>>num;
		map<int, string> sortedorder;
		char* input = new char[length];
		for(int i = 0; i < num ; i++)
		{
			cin>>input;
			string temp(input);
			int order = mergeSort(input,length)*100;
			while(sortedorder.find(order) != sortedorder.end())
				order++;
			sortedorder[order] = temp;
		}
		for(map<int,string>::iterator itr = sortedorder.begin(); itr != sortedorder.end(); itr++)
		{
			cout<<itr->second<<endl;
		}
	}

	int* lisfunction(int* arr, int length)
	{
		int* lis = new int[length];
		lis[0] = 1;
		for(int i = 1; i < length; i++)
		{
			int max = 0;
			for(int j = 0; j < i; j++)
			{
				if(arr[j] < arr[i] && max < lis[j])
					max = lis[j];
			}
			lis[i] = max + 1;
		}
		return lis;
	}
	int* fastlisfunction(int* arr, int length, int& size)
	{
		int* s = new int[length];
		s[0] = 0;
		int sz = 1;
		for(int i = 1; i < length; i++)
		{
			
			if(arr[i] < arr[s[0]])
			{
				s[0] = i;
			}
			else if(arr[i] > arr[s[sz-1]])
			{
				s[sz] = i;
				sz++;
			}
			else
			{
				int low = 0, high = sz;
				while(low < high)
				{
					int mid = (low + high)/2;
					if(arr[i] <= arr[s[mid]])
						high = mid-1;
					else
						low = mid+1;
				}
				s[high] = i;
			}
			for(int j = 0; j < sz; j++)
			{
				cout<<arr[s[j]]<<' ';
			}
			cout<<endl;
		}
		size = sz;
		return s;
	}
	void fastlistest()
	{
		int arr[] = {2, 5, 3, 7, 11, 8, 10, 13, 6};
		int sz = 0;
		int* helper = fastlisfunction(arr,sizeof(arr)/sizeof(arr[0]), sz);
		for(int i = 0; i < sz; i++)
			cout<<helper[i]<<":"<<arr[helper[i]]<<' ';
	}
	int** lcsfunction(int* arr1, int* arr2, int length1, int length2, int**& lcsdir)
	{
		int** lcs = new int*[length1 + 1];
		int** lcsd = new int*[length1 + 1];
		for(int i = 0; i < length1+1; i++)
		{
			lcs[i] = new int[length2 + 1];
			lcs[i][0] = 0;
			lcsd[i] = new int[length2 + 1];
			lcsd[i][0] = 0;
		}
		for(int i = 0; i < length2+1; i++)
		{
			lcs[0][i] = 0;
			lcsd[0][i] = 0;
		}
		for(int i = 1; i < length1+1; i++)
		{
			for(int j = 1; j < length2+1; j++)
			{
				if(arr1[i-1] == arr2[j-1])
				{
					lcs[i][j] = 1 + lcs[i-1][j-1];
					lcsd[i][j] = 1;
				}
				else if(lcs[i-1][j] > lcs[i][j-1])
				{
					lcsd[i][j] = 2;
					lcs[i][j] = lcs[i-1][j];
				}
				else
				{
					lcsd[i][j] = 3;
					lcs[i][j] = lcs[i][j-1];
				}
			}
		}
		lcsdir = lcsd;
		return lcs;
	}
	void gcis_amar()
	{
		int m = 0, n = 0;
		cin>>m;
		int* arr1 = new int[m];
		for(int i = 0; i < m; i++)
			cin>>arr1[i];
		cin>>n;
		int* arr2 = new int[n];
		for(int i = 0; i < n; i++)
			cin>>arr2[i];
		int* lis1 = lisfunction(arr1,m);
		int* lis2 = lisfunction(arr2,n);
		int** lcsroot;
		int** lcs = lcsfunction(arr1,arr2,m,n,lcsroot);
		/*for(int i = 0; i < m; i++)
			cout<<lis1[i]<<'\t';
		cout<<endl;
		for(int i = 0; i < n; i++)
			cout<<lis2[i]<<'\t';
		cout<<endl;
		for(int i = 0; i <= m; i++)
		{
			for(int j = 0; j <= n; j++)
			{
				cout<<lcs[i][j]<<'\t';
			}
			cout<<endl;
		}
		cout<<endl;
		for(int i = 0; i <= m; i++)
		{
			for(int j = 0; j <= n; j++)
			{
				cout<<lcsroot[i][j]<<'\t';
			}
			cout<<endl;
		}
		cout<<endl;*/
		int max = 0;
		vector<int> result;
		for(int i = m; i>=0; i--)
		{
			for(int j = n; j>=0; j--)
			{
				if(lcsroot[i][j] == 1)
				{
					if(lcs[i][j] > max)
					{
						int temp = lcs[i][j];
						if(temp > lis1[i-1])
							temp = lis1[i-1];
						if(temp > lis2[j-1])
							temp = lis2[j-1];
						if(temp > max)
						{
							max = temp;
							int a = i, b = j;
							result.clear();
							while(lcsroot[a][b] != 0)
							{
								if(lcsroot[a][b] == 1)
								{
									result.push_back(arr1[a-1]);
									a--;
									b--;
								}
								else if(lcsroot[a][b] == 2)
								{
									a--;
								}
								else
								{
									b--;
								}
							}
						}
					}
				}
			}
		}
		cout<<max<<endl;
		if(max == result.size())
		{
			for(int i = result.size() - 1; i >= 0; i--)
			{
				cout<<result[i]<<' ';
			}
			cout<<endl;
		}
		else
		{
			int* arr = new int[result.size()];
			for(int i = 0; i < result.size(); i++)
				arr[i] = result[result.size() - i - 1];
			int* lishelp = new int[result.size()];
			int* lisarr = new int[result.size()];
			lisarr[0] = 1;
			lishelp[0] = -1;
			for(int i = 1; i < result.size(); i++)
			{
				int index = -1;
				int maxj = 0;
				for(int j = 0; j < i; j++)
				{
					if(arr[j] < arr[i] && maxj < lisarr[j])
					{
						maxj = lisarr[j];
						index = j;
					}
				}
				lisarr[i] = maxj + 1;
				lishelp[i] = index;
			}
			/*for(int i = 0; i < result.size(); i++)
			{
				cout<<arr[i]<<'\t';
			}
			cout<<endl;
			for(int i = 0; i < result.size(); i++)
			{
				cout<<lisarr[i]<<'\t';
			}
			cout<<endl;
			for(int i = 0; i < result.size(); i++)
			{
				cout<<lishelp[i]<<'\t';
			}
			cout<<endl;*/
			int x = result.size() - 1;
			vector<int> newresult;
			bool found_first = false;
			while(x != -1)
			{
				if(x == 0 || lishelp[x] != -1)
				{
					found_first = true;
					newresult.push_back(arr[x]);
					x = lishelp[x];
				}
				else if(found_first == false)
				{
					x--;
				}
				else
				{
					break;
				}
			}
			for(int i = newresult.size() - 1; i>= 0; i--)
			{
				cout<<newresult[i]<<' ';
			}
			cout<<endl;
		}
	}

	// Longest Common Increasing Subsequence
	int LCIS_size( vector< int> A, vector< int> B)
	{
		int N = ( int) A.size(), M = ( int) B.size(), len = 0;
		vector< int> C(M, 0);
		for( int i = 0; i < N; i++)
			for( int cur = 0, j = 0; j < M; j++)
				if( A[i] == B[j] && cur + 1 > C[j]) C[j] = cur + 1;
				else if(C[j] > cur && B[j] < A[i]) cur = C[j];
				for( int i = 0; i < M; i++) if(C[i] > len) len = C[i];
				return len;
	}

	// Longest Common Increasing Subsequence
	vector< int> LCIS( vector< int> A, vector< int> B)
	{
		int N = ( int) A.size(), M = ( int) B.size(), len = 0, idx = -1;
		vector< int> C(M, 0), res;
		vector< vector< pair< int, int> > > possible(M);

		for( int i = 0; i < N; i++)
			for( int cur = 0, last = -1, j = 0; j < M; j++)
				if( A[i] == B[j])
				{
					possible[j].push_back(make_pair(cur + 1, last));
					if(cur + 1 > C[j]) C[j] = cur + 1;
				}
				else if( B[j] < A[i] && C[j] > cur) { cur = C[j]; last = j; }

				for( int i = 0; i < M; i++)
					if(C[i] > len) { len = C[i]; idx = i; }

					while(len)
					{
						res.push_back( B[idx]);
						for( int i = 0; i < (int)possible[idx].size(); i++)
							if(possible[idx][i].first == len)
							{
								idx = possible[idx][i].second;
								break;
							}
							len--;
					}
					reverse(res.begin(),res.end());
					return res;
	}

	void gcis()
	{
		int N,M;
		vector< int> A,B;
		// Leer A
		scanf( "%d",&N); A.clear(); A.resize(N);
		for( int i = 0; i < N; i++) scanf( "%d",&A[i]);
		// Leer B
		scanf( "%d",&M); B.clear(); B.resize(M);
		for( int i = 0; i < M; i++) scanf( "%d",&B[i]);
		// Calcular LCIS
		//printf("%d\n",LCIS_size(A,B));
		vector< int> ans = LCIS(A,B);
		printf( "%d\n",(int )ans.size());
		for( int i = 0; i < ( int)ans.size(); i++)
			if(i == 0) printf( "%d",ans[i]);
			else printf( " %d",ans[i]);
			if(( int)ans.size() != 0) printf( "\n");
	}


	int dfsgraphbalancingact(vector< vector< pair<int, int> > >& data, bool* visited, int index, int& pidx, int pindex)
	{
		visited[index] = true;
		int count = 1;
#ifdef DEBUG
		//printf("N: %d\n",index);
#endif
		
		for(unsigned int i = 0; i < data[index].size(); i++)
		{
			if(!visited[data[index][i].first])
			{
				int idx = -1;
				int temp = dfsgraphbalancingact(data, visited, data[index][i].first, idx, index);
				count += temp;
				data[index][i].second = temp;
				if(idx != -1)
					data[data[index][i].first][idx].second = data.size() - temp;
				
			}
			if(pindex != -1 && pindex == data[index][i].first)
				pidx = i;
		}
		return count;
	}

	int dfsbalance(vector< vector< pair<int, int> > >& data, int& minbalance, bool* visited)
	{
		int numOfNodes = data.size();
		int time = 0;
		
		std::memset(visited,0,sizeof(bool)*numOfNodes);

		for(int i = 0;i<numOfNodes; i++)
		{
			if(!visited[i])
			{
				int pidx=0;
				dfsgraphbalancingact(data, visited, i,pidx,-1);
			}
		}
		
		//std::memset(visited,0,sizeof(bool)*numOfNodes);

		int globalmin = 10000000;
		int globalindex = 0;
		for(int index = 0;index<numOfNodes; index++)
		{
			int max = 0;
			for(unsigned int i = 0; i < data[index].size(); i++)
			{
				if(data[index][i].second > max)
					max = data[index][i].second;
			}
			if(max < globalmin)
			{
				globalmin = max;
				globalindex = index;
			}
		}
		minbalance = globalmin;
		return globalindex;
	}

	void balancingact()
	{
		int testcases = 0;
		cin>>testcases;
		bool* visited = new bool[20000];
		while(testcases--)
		{
			int numnodes = 0;
			cin>>numnodes;
			vector<vector < pair<int,int> > > graph;
			for(int i = 0; i < numnodes; i++)
			{
				std::vector< std::pair<int, int> > temp;
				graph.push_back(temp);
			}
			for(int i = 1; i < numnodes; i++)
			{
				int start = 0, end = 0;
				cin>>start>>end;
				std::pair<int, int> temp(end-1, 0);
				graph[start-1].push_back(temp);
				pair<int,int> temp2(start-1,0);
				graph[end-1].push_back(temp2);
			}
			int minbalance = 0;
			cout<<dfsbalance(graph,minbalance,visited)+1<<" ";
			cout<<minbalance<<endl;
		}
	}

	void verticalhistogram()
	{
		const int start = 65;
		int numstrings = 4;
		string input;
		map<char,int> histogram;
		for(int i = 0; i <26; i++)
			histogram[i+start] = 0;
		int maxCount = 0;
		while(numstrings--)
		{
			getline(cin,input);
			for(int i = 0; i < input.size(); i++)
			{
				if(input[i] >= start && input[i] <= start + 25)
					histogram[input[i]]++;
			}
		}
		for(int i = 0; i < 26; i++)
		{
			if(maxCount < histogram[i + start])
				maxCount = histogram[i + start];
		}
		while(maxCount)
		{
			for(int i = 0; i < 26; i++)
			{
				if(histogram[i + start] == maxCount)
				{
					cout<<"*";
					histogram[i + start]--;
				}
				else
					cout<<" ";
				cout<<" ";
			}
			cout<<endl;
			maxCount--;
		}
		for(int i = 0; i < 26; i++)
			cout<<char(i+start)<<" ";
		cout<<endl;
	}

	void herdsums()
	{
		unsigned int i,j,n,ways=0;
		long int remain;
		scanf("%u", &n);

		for (i=n; i!=0; --i) {
			remain = n;
			for (j=i; remain>0; --j)
				remain -= j;
			if (remain == 0)
				++ways;
		}

		printf("%u\n", ways);
	}

	int reversenum(int input)
	{
		int result = 0;
		while(input)
		{
			result = result*10 + input%10;
			input = input/10;
		}
		return result;
	}
	void addreversenum()
	{
		int testcases;
		cin>>testcases;
		while(testcases--)
		{
			int a,b;
			cin>>a>>b;
			cout<<reversenum(reversenum(a) + reversenum(b))<<endl;
		}
	}

	void ridetoschool_amar()
	{
		int testcases = 1;
		cin>>testcases;
		while(testcases)
		{
			double *speed = new double[testcases];
			double *dist = new double[testcases];
			int *starttime = new int[testcases];

			int rider = -1;

			for(int i = 0; i < testcases; i++)
			{
				cin>>speed[i]>>starttime[i];
				speed[i] = (speed[i]*5)/18;
				if(starttime[i] > 0)
				{
					dist[i] = 0;
				}
				else if(starttime[i] == 0)
				{
					if(rider == -1)
					{
						rider = i;
					}
					else if(speed[rider] < speed[i])
					{
						rider = i;
					}
					dist[i] = 0;
				}
				else
				{
					dist[i] = -1 * starttime[i] * speed[i];
				}
				
			}
			int time = 0;

			while(true)
			{
				for(int i = 0; i < testcases; i++)
				{
					if(starttime[i] <= time)
						dist[i] += speed[i];
				}
				for(int i = 0; i < testcases; i++)
				{
					if(rider == -1)
					{
						if(starttime[i] == time)
						{
							rider = i;
						}
					}
					else
					{
						if(speed[rider] < speed[i] && dist[rider] <= dist[i] && dist[rider] >= (dist[i]-speed[i]))
						{
							rider = i;
						}
					}	
				}
				if(rider != -1 && dist[rider] >= 4500)
				{
					cout<<time+1<<endl;
					//return;
					break;
				}
				time++;
			}
			cin>>testcases;
		}
	}

	void ridetoschool()
	{
		int N;//number of riders
		int v,t;
		int output;
		double min;
		double time;
		while(1)
		{
			scanf("%d",&N); // input number of riders
			if(N==0) // need to break in case of last test case otherwisw infinite loop
				break;
			min = 3600 * 4.5;  //this is the maximum time that a rider can takes assuming speed of 1km.hr
			while(N--)
			{
				scanf("%d%d",&v,&t);//input velocity and set off time of each rider
				if(t<0)//if rider sets off even before charley reached gates of Wanliu,then we do not    need to consider
					continue;
				time = 4.5 / v * 3600 + t; //calculate total time taken by this rider
				if(time<min) //if it is minimum time,consider it
					min=time;
			}
			t=(int)ceil(min);//print output for this test case as an integer
			cout<<t<<endl;//print output in a new line
		}
		//return 0;
	}

	int formsvalidsquare(char** arr, int size, int x, int y)
	{
		int i = x-1, j = y-1;
		int squaresize = 0;
		while(i >= 0 && j >= 0)
		{
			if(arr[i][y] == 'J' && arr[i][j] == 'J' && arr[x][j] == 'J')
			{
				if(squaresize < x-i)
					squaresize = x - i;
			}
			i--;
			j--;
		}
		i = x-1;
		j = y+1;
		while(i >= 0 && j < size)
		{
			if(arr[i][y] == 'J' && arr[i][j] == 'J' && arr[x][j] == 'J')
			{
				if(squaresize < x-i)
					squaresize = x - i;
			}
			i--;
			j++;
		}
		i = x+1;
		j = y+1;
		while(i < size && j < size)
		{
			if(arr[i][y] == 'J' && arr[i][j] == 'J' && arr[x][j] == 'J')
			{
				if(squaresize < i - x)
					squaresize = i - x;
			}
			i++;
			j++;
		}
		i = x+1;
		j = y-1;
		while(i < size && j >= 0)
		{
			if(arr[i][y] == 'J' && arr[i][j] == 'J' && arr[x][j] == 'J')
			{
				if(squaresize < i - x)
					squaresize = i - x;
			}
			i++;
			j--;
		}
		return squaresize;
	}

	void bigsquare()
	{
		int size = 0;
		cin>>size;
		char ** arr = new char*[size];
		for(int i = 0; i < size; i++)
		{
			arr[i] = new char[size];
			for(int j = 0; j < size; j++)
			{
				cin>>arr[i][j];
			}
		}
		int maxsquare = 0;
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
			{
				if(arr[i][j] == 'B')
					continue;
				int tempsquare = formsvalidsquare(arr,size,i,j); 
				if(maxsquare < tempsquare)
				{
					maxsquare = tempsquare;
				}
			}
		}
		cout<<maxsquare*maxsquare<<endl;
	}

	#define PI 3.141592653589793
	void yeehaw()
	{
		int testcases;
		cin>>testcases;
		int i = 0;
		while(testcases--)
		{
			i++;
			int n = 0;
			double R = 0;
			cin>>R>>n;
			double r = (R * sin(PI/n))/(1 + sin(PI/n));
			printf("Scenario #%d:\n",i);
			printf("%.3f\n",r);
		}
	}

	bool binarysearchforgoldbach(vector<int> & primes, int num)
	{
		int low = 0, high = primes.size() -1;
		while(low <= high)
		{
			int mid = low + (high - low)/2;
			if(primes[mid] == num)
				return true;
			else if(primes[mid] < num)
			{
				low = mid + 1;
			}
			else
			{
				high = mid - 1 ;
			}
		}
		return false;
	}

	void goldbach()
	{
		int n = 1000000;
		vector<int> primes;
		bool* ok = new bool[n];
		std::memset(ok,0,n*sizeof(bool));
        for (int i = 2; i < n; ++i) // primes up to 1000000 (only need up to sqrt of 1 000 000 actually)
        {
            if (!ok[i])
            {
                primes.push_back(i);

                for (long long j = i; j < n; j += i)
                    ok[j] = true;
            }
        }
		int testcases;
		cin>>testcases;
		while(testcases)
		{
			for(int i = 0; i < primes.size(); i++)
			{
				if(binarysearchforgoldbach(primes,testcases - primes[i]))
				{
					cout<<testcases<<" = "<<primes[i]<<" + "<<testcases - primes[i]<<endl;
					break;
				}
			}
			cin>>testcases;
		}
	}

	void circumference()
	{
		double x1,y1,x2,y2,x3,y3;
		while(cin>>x1>>y1>>x2>>y2>>x3>>y3)
		{
			double a=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));  
			double b=sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));  
			double c=sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));  
			double s=(a+b+c)/2.0;  
  
			double r=a*b*c/(4*sqrt(s*(s-a)*(s-b)*(s-c)));  

			printf("%.2f\n",2*r*PI);
		}
	}

	struct point
	{
		int x;
		int y;
	};
	double area(vector<point>& points)
	{
		int s1 = 0, s2 = 0;
		for(int i = 0; i < points.size()-1; i++)
		{
			s1 += points[i].x*points[i+1].y;
			s2 += points[i].y*points[i+1].x;
		}
		s1 += points[points.size() -1].x * points[0].y;
		s2 += points[points.size() -1].y*points[0].x;
		double area = abs(s1-s2)/2.0;
		return area;
	}
	void area(point& pointa, point pointb, int& s1, int& s2)
	{
		s1 += pointa.x*pointb.y;
		s2 += pointa.y*pointb.x;
	}
	void polygonarea()
	{
		int testcases;
		cin>>testcases;
		while(testcases--)
		{
			string input;
			cin>>input;
			point startpoint;
			startpoint.x = 0;
			startpoint.y = 0;
			//vector<point> points;
			//points.push_back(startpoint);
			point prevpoint = startpoint;
			int s1 = 0, s2 = 0;
			for(int i = 0; i < input.size(); i++)
			{
				point nextpoint;
				nextpoint.x = 0;
				nextpoint.y = 0;
				switch(input[i])
				{
				case '8':
					nextpoint.x = prevpoint.x;
					nextpoint.y = prevpoint.y + 1;
					break;
				case '2':
					nextpoint.x = prevpoint.x;
					nextpoint.y = prevpoint.y - 1;
					break;
				case '6':
					nextpoint.x = prevpoint.x+1;
					nextpoint.y = prevpoint.y;
					break;
				case '4':
					nextpoint.x = prevpoint.x - 1;
					nextpoint.y = prevpoint.y;
					break;
				case '1':
					nextpoint.x = prevpoint.x - 1;
					nextpoint.y = prevpoint.y - 1;
					break;
				case '3':
					nextpoint.x = prevpoint.x + 1;
					nextpoint.y = prevpoint.y - 1;
					break;
				case '7':
					nextpoint.x = prevpoint.x - 1;
					nextpoint.y = prevpoint.y + 1;
					break;
				case '9':
					nextpoint.x = prevpoint.x + 1;
					nextpoint.y = prevpoint.y + 1;
					break;
				default:
					break;
				};
				//points.push_back(nextpoint);
				area(prevpoint,nextpoint,s1,s2);
				prevpoint = nextpoint;
			}
			area(prevpoint,startpoint,s1,s2);
			double area = abs(s1-s2)/2.0;
			cout<<area<<endl;
		}
	}

};
