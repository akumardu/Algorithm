#include<iostream>
#include<string>
#include<vector>
#include<map>

namespace topcoder
{
	using namespace std;

	class PenLift
	{
		class undirectedgraph
		{
		public :
			undirectedgraph( unsigned int numOfNodes)
			{
				while(numOfNodes--)
				{
					std::vector< std::pair< unsigned int, long> > temp;
					data.push_back(temp);
				}
			}

			void addEdge( unsigned long start, unsigned int end, long weight)
			{
				std::pair< unsigned int, long> temp(end, weight);
				data[start].push_back(temp);
				std::pair< unsigned int, long> temp2(start, weight);
				data[end].push_back(temp2);
			}
			void dfs(int start, vector<int>& component, bool* visited)
			{
				visited[start] = true;
				component.push_back(start);
				for(unsigned int i = 0; i < data[start].size(); i++)
				{
					if(visited[data[start][i].first] == false)
					{
						dfs(data[start][i].first,component,visited);
					}
				}
			}
			vector< vector < int > > connectedComponents()
			{
				vector<vector<int> > components;
				int numOfNodes = data.size();
				bool* visited = new bool[numOfNodes];
				for(int i = 0; i < numOfNodes; i++)
				{
					visited[i] = false;
				}
				for(int i = 0; i < numOfNodes; i++)
				{
					if(visited[i] == false)
					{
						vector<int> component;
						dfs(i,component,visited);
						components.push_back(component);
					}
				}
				return components;
			}

			int penlifts(vector<vector<int>>& components)
			{
				int sum = 0;
				for(unsigned int i = 0; i < components.size(); i++)
				{
					int oddvertices = 0;
					for(unsigned int j =0; j < components[i].size(); j++)
					{
						if(data[components[i][j]].size()%2 != 0)
						{
							oddvertices++;
						}
					}
					if(oddvertices == 0)
					{
						oddvertices = 1;
					}
					else
					{
						oddvertices = oddvertices/2;
					}
					sum += oddvertices;
				}
				return sum;
			}

		private :
			std::vector< std::vector< std::pair< unsigned int, long> > > data;
		};
	class point
	{
	public:
		int x;
		int y;
	};
	class line
	{
	public:
		point start;
		point end;
		line(){}
		line( point a, point b)
		{
			if(a.x < b.x)
			{
				start = a;
				end = b;
			}
			else if(a.x > b.x)
			{
				start = b;
				end = a;
			}
			else if(a.y > b.y)
			{
				start = b;
				end = a;
			}
			else
			{
				start = a;
				end = b;
			}
		}
		bool intersects(line& another, point& intersection)
		{
			if(isCollinear(another))
			{
				return false;
			}
			// || to each other
			if((start.x == end.x ) && (another.start.x == another.end.x))
			{
				return false;
			}
			// || to each other
			if((start.y == end.y ) && (another.start.y == another.end.y))
			{
				return false;
			}
			// TODO: Find intersection
			if(start.y == end.y)
			{
				if(another.start.x < start.x || another.start.x > end.x)
				{
					return false;
				}
				intersection.x = another.start.x;
				intersection.y = start.y;
			}
			if(start.x == end.x)
			{
				if(another.start.y < start.y || another.start.y > end.y)
				{
					return false;
				}
				intersection.y = another.start.y;
				intersection.x = start.x;
			}
			return true;
		}
		bool isCollinear(line& another)
		{
			if( (start.y - end.y) * (another.start.x - another.end.x) != (start.x - end.x) * (another.start.y - another.end.y))
			{
				return false;
			}
			int first = (start.x * end.y - end.x * start.y) * (another.start.x - another.end.x);
			int second = (another.start.x * another.end.y - another.end.x * another.start.y) * (start.x - end.x);
			if (first != second)
			{
				return false;
			}
			return true;
		}
		bool isCollinearAndIntersects(line& another, line& final)
		{
			if(isCollinear(another) == false)
			{
				return false;
			}
			if((another.start.x < start.x && another.end.x < start.x) ||
				(another.start.x > end.x && another.end.x > end.x))
			{
				return false;
			}
			if((another.start.y < start.y && another.end.y < start.y) ||
				(another.start.y > end.y && another.end.y > end.y))
			{
				return false;
			}
			// || to y
			if(start.x == end.x)
			{
				final.start = (start.y < another.start.y)?(start):(another.start);
				final.end = (end.y < another.end.y)?(another.end):(end);
			}
			else
			{
				final.start = (start.x < another.start.x)?(start):(another.start);
				final.end = (end.x < another.end.x)?(another.end):(end);
			}
			return true;
		}
		bool containsPoint(point a)
		{
			if(start.x == end.x)
			{
				if(a.x == start.x && a.y > start.y && a.y < end.y)
				{
					return true;
				}
			}
			else if(start.y == end.y)
			{
				if(a.y == start.y && a.x > start.x && a.x < end.x)
				{
					return true;
				}
			}
			return false;
		}
		bool containsPointIncludingEnd(point a)
		{
			if(start.x == end.x)
			{
				if(a.x == start.x && a.y >= start.y && a.y <= end.y)
				{
					return true;
				}
			}
			else if(start.y == end.y)
			{
				if(a.y == start.y && a.x >= start.x && a.x <= end.x)
				{
					return true;
				}
			}
			return false;
		}
	};
	public:
		int numTimes(vector <string> segments, int n)
		{
			vector<point> nodes;
			vector<line> lines;
			// Parse segments
			for(unsigned int i = 0; i < segments.size(); i++)
			{
				point a,b;
				string input = segments[i];
				istringstream(input) >> a.x;
				input = input.substr(input.find_first_of(' ')+1);
				istringstream(input) >> a.y;
				input = input.substr(input.find_first_of(' ')+1);
				istringstream(input) >> b.x;
				input = input.substr(input.find_first_of(' ')+1);
				istringstream(input) >> b.y;
				line inputline(a,b);
				bool found = false;
				// Reduce collinear lines
				for(auto it = lines.begin(); it != lines.end();)
				{
					line finalline;
					if(it->isCollinearAndIntersects(inputline, finalline) == true)
					{
						it = lines.erase(it);
						lines.push_back(finalline);
						found = true;
						break;
					}
					else
						++it;
				}
				if(!found)
					lines.push_back(inputline);
			}
			// Fill up nodes with endpoints
			for(unsigned int i = 0; i < lines.size(); i++)
			{
				bool found = false;
				for(unsigned int j = 0; j < nodes.size(); j++)
				{
					if((lines[i].start.x == nodes[j].x) && (lines[i].start.y == nodes[j].y))
					{
						found = true;
						break;
					}
				}
				if(!found)
				{
					nodes.push_back(lines[i].start);
				}
				found = false;
				for(unsigned int j = 0; j < nodes.size(); j++)
				{
					if((lines[i].end.x == nodes[j].x) && (lines[i].end.y == nodes[j].y))
					{
						found = true;
						break;
					}
				}
				if(!found)
				{
					nodes.push_back(lines[i].end);
				}
			}
			// Calculate intersections and fill up nodes
			for(unsigned int i = 0; i < lines.size(); i++)
			{
				for(unsigned int j = i+1; j < lines.size(); j++)
				{
					point intersection;
					if(lines[i].intersects(lines[j], intersection) == true)
					{
						bool found = false;
						for(unsigned int k = 0; k < nodes.size(); k++)
						{
							if((intersection.x == nodes[k].x) && (intersection.y == nodes[k].y))
							{
								found = true;
								break;
							}
						}
						if(!found)
						{
							nodes.push_back(intersection);
						}
					}
				}
			}
			// Fill graph with edges
			undirectedgraph g(nodes.size());
			for(unsigned int i = 0; i < nodes.size(); i++)
			{
				for(unsigned int j = i+1; j < nodes.size(); j++)
				{
					if(nodes[i].x == nodes[j].x || nodes[i].y == nodes[j].y)
					{
						line temp(nodes[i], nodes[j]);
						bool found = false;
						for(unsigned int k = 0; k < nodes.size(); k++)
						{
							if(temp.containsPoint(nodes[k]))
							{
								found = true;
								break;
							}
						}
						if(!found)
						{
							for(unsigned int k = 0; k < lines.size(); k++)
							{
								if(lines[k].containsPointIncludingEnd(nodes[i]) && lines[k].containsPointIncludingEnd(nodes[j]))
								{
									g.addEdge(i,j,0);
								}
							}
						}
					}
				}
			}
			if(n%2 == 0)
			{
				return g.connectedComponents().size() - 1;
			}
			return g.penlifts(g.connectedComponents()) - 1;
		}
		static void testThis()
		{
			PenLift p;
			vector<string> segments;
			/*segments.push_back("-10 0 10 0");
			segments.push_back("0 -10 0 10");
			cout<<p.numTimes(segments, 1)<<endl;
			segments.clear();*/
			string input[] = {"-252927 -1000000 -252927 549481","628981 580961 -971965 580961",
								"159038 -171934 159038 -420875","159038 923907 159038 418077",
								"1000000 1000000 -909294 1000000","1000000 -420875 1000000 66849",
								"1000000 -171934 628981 -171934","411096 66849 411096 -420875",
								"-1000000 -420875 -396104 -420875","1000000 1000000 159038 1000000",
								"411096 66849 411096 521448","-971965 580961 -909294 580961",
								"159038 66849 159038 -1000000","-971965 1000000 725240 1000000",
								"-396104 -420875 -396104 -171934","-909294 521448 628981 521448",
								"-909294 1000000 -909294 -1000000","628981 1000000 -909294 1000000",
								"628981 418077 -396104 418077","-971965 -420875 159038 -420875",
								"1000000 -1000000 -396104 -1000000","-971965 66849 159038 66849",
								"-909294 418077 1000000 418077","-909294 418077 411096 418077",
								"725240 521448 725240 418077","-252927 -1000000 -1000000 -1000000",
								"411096 549481 -1000000 549481","628981 -171934 628981 923907",
								"-1000000 66849 -1000000 521448","-396104 66849 -396104 1000000",
								"628981 -1000000 628981 521448","-971965 521448 -396104 521448",
								"-1000000 418077 1000000 418077","-1000000 521448 -252927 521448",
								"725240 -420875 725240 -1000000","-1000000 549481 -1000000 -420875",
								"159038 521448 -396104 521448","-1000000 521448 -252927 521448",
								"628981 580961 628981 549481","628981 -1000000 628981 521448",
								"1000000 66849 1000000 -171934","-396104 66849 159038 66849",
								"1000000 66849 -396104 66849","628981 1000000 628981 521448",
								"-252927 923907 -252927 580961","1000000 549481 -971965 549481",
								"-909294 66849 628981 66849","-252927 418077 628981 418077",
								"159038 -171934 -909294 -171934","-252927 549481 159038 549481"};
			for(int i = 0; i < 50; i++)
			{
				segments.push_back(input[i]);
			}
			cout<<p.numTimes(segments, 824759)<<endl;
		}
	};

	class PowerOutage_1
	{
	public:
		class tree
		{
		public:
			vector<tree*> children;
			vector<int> dist;
			int noOfChildren;
			int id;
			tree()
			{
				noOfChildren = 0;
			}
			void addChild(tree* child, int distance)
			{
				children.push_back(child);
				dist.push_back(distance);
				noOfChildren = dist.size();
			}
		};
		int findMinDistance(tree* root, bool isRoot = true)
		{
			int distance = 0;
			if(root->noOfChildren == 0)
				return 0;
			multimap<int, int> distanceToChild;
			for(int i = 0; i < root->noOfChildren; i++)
			{
				long dist = findMinDistance(root->children[i], false);
				distanceToChild.insert(std::pair<int,int>(dist + 2* (root->dist[i]),i));
			}
			auto iter2 = distanceToChild.begin();
			for(auto iter = distanceToChild.begin(); iter != distanceToChild.end(); iter++)
			{
				iter2++;
				if(isRoot == true && iter2 == distanceToChild.end())
				{
					distance += root->dist[(*iter).second] + findMinDistance(root->children[iter->second], true);
					break;
				}
				distance += (*iter).first;
			}
			return distance;
		}

		int estimateTimeOut(vector<int> fromJunction, vector<int> toJunction, vector<int> ductLength)
		{
			vector<tree*> junctions;
			tree* root = NULL;
			for(unsigned int i = 0; i < fromJunction.size(); i++)
			{
				tree* origin = NULL;
				tree* end = NULL;
				for(unsigned int j = 0; j < junctions.size(); j++)
				{
					if(fromJunction[i] == (junctions[j]->id))
					{
						origin = junctions[j];
					}
					if(toJunction[i] == (junctions[j]->id))
					{
						end = junctions[j];
					}
				}
				if(origin == NULL)
				{
					origin = new tree();
					origin->id = fromJunction[i];
					junctions.push_back(origin);
				}
				if(end == NULL)
				{
					end = new tree();
					end->id = toJunction[i];
					junctions.push_back(end);
				}
				if(root == NULL && origin->id == 0)
				{
					root = origin;
				}
				origin->addChild(end,ductLength[i]);
				
			}
			return findMinDistance(root);
		}
		static void testThis()
		{
			PowerOutage_1 p;
			vector<int> fromJunction;
			vector<int> toJunction;
			vector<int> ductLength;
			fromJunction.push_back(0);
			fromJunction.push_back(0);
			fromJunction.push_back(0);
			fromJunction.push_back(1);
			fromJunction.push_back(4);
			fromJunction.push_back(4);
			fromJunction.push_back(6);
			fromJunction.push_back(7);
			fromJunction.push_back(7);
			fromJunction.push_back(7);
			fromJunction.push_back(20);
			toJunction.push_back(1);
			toJunction.push_back(3);
			toJunction.push_back(4);
			toJunction.push_back(2);
			toJunction.push_back(5);
			toJunction.push_back(6);
			toJunction.push_back(7);
			toJunction.push_back(20);
			toJunction.push_back(9);
			toJunction.push_back(10);
			toJunction.push_back(31);
			ductLength.push_back(10);
			ductLength.push_back(10);
			ductLength.push_back(100);
			ductLength.push_back(10);
			ductLength.push_back(5);
			ductLength.push_back(1);
			ductLength.push_back(1);
			ductLength.push_back(100);
			ductLength.push_back(1);
			ductLength.push_back(1);
			ductLength.push_back(5);
			cout<<p.estimateTimeOut(fromJunction, toJunction, ductLength)<<endl;
		}
	};

	class PowerOutage
	{
	public:
		class tree
		{
		public:
			vector<tree*> children;
			vector<int> dist;
			int noOfChildren;
			int id;
			tree()
			{
				noOfChildren = 0;
			}
			void addChild(tree* child, int distance)
			{
				children.push_back(child);
				dist.push_back(distance);
				noOfChildren = dist.size();
			}
		};
		int findMaxDistanceToLeaf(tree* root, int distanceTillNow)
		{
			int distance = 0;
			if(root->noOfChildren == 0)
			{
				return distanceTillNow;
			}
			int max = 0;
			for(int i = 0; i < root->noOfChildren; i++)
			{
				long dist = findMaxDistanceToLeaf(root->children[i], distanceTillNow + root->dist[i]);
				if(dist > max)
				{
					max = dist;
				}
			}
			
			return max;
		}

		int estimateTimeOut(vector<int> fromJunction, vector<int> toJunction, vector<int> ductLength)
		{
			vector<tree*> junctions;
			tree* root = NULL;
			int total = 0;
			for(unsigned int i = 0; i < fromJunction.size(); i++)
			{
				total += ductLength[i];
				tree* origin = NULL;
				tree* end = NULL;
				for(unsigned int j = 0; j < junctions.size(); j++)
				{
					if(fromJunction[i] == (junctions[j]->id))
					{
						origin = junctions[j];
					}
					if(toJunction[i] == (junctions[j]->id))
					{
						end = junctions[j];
					}
				}
				if(origin == NULL)
				{
					origin = new tree();
					origin->id = fromJunction[i];
					junctions.push_back(origin);
				}
				if(end == NULL)
				{
					end = new tree();
					end->id = toJunction[i];
					junctions.push_back(end);
				}
				if(root == NULL && origin->id == 0)
				{
					root = origin;
				}
				origin->addChild(end,ductLength[i]);
				
			}
			int maxLeafLength = findMaxDistanceToLeaf(root,0);
			return 2*total - maxLeafLength;
		}
		static void testThis()
		{
			PowerOutage p;
			vector<int> fromJunction;
			vector<int> toJunction;
			vector<int> ductLength;
			fromJunction.push_back(0);
			fromJunction.push_back(0);
			fromJunction.push_back(0);
			fromJunction.push_back(1);
			fromJunction.push_back(4);
			fromJunction.push_back(4);
			fromJunction.push_back(6);
			fromJunction.push_back(7);
			fromJunction.push_back(7);
			fromJunction.push_back(7);
			fromJunction.push_back(20);
			toJunction.push_back(1);
			toJunction.push_back(3);
			toJunction.push_back(4);
			toJunction.push_back(2);
			toJunction.push_back(5);
			toJunction.push_back(6);
			toJunction.push_back(7);
			toJunction.push_back(20);
			toJunction.push_back(9);
			toJunction.push_back(10);
			toJunction.push_back(31);
			ductLength.push_back(10);
			ductLength.push_back(10);
			ductLength.push_back(100);
			ductLength.push_back(10);
			ductLength.push_back(5);
			ductLength.push_back(1);
			ductLength.push_back(1);
			ductLength.push_back(100);
			ductLength.push_back(1);
			ductLength.push_back(1);
			ductLength.push_back(5);
			cout<<p.estimateTimeOut(fromJunction, toJunction, ductLength)<<endl;
		}
	};
	
	class Lottery
	{
	public:
		vector<string> sortByOdds(vector<string> rules)
		{
			map<long long,string> resultmap;
			for(int i = 0; i < rules.size(); i++)
			{
				string rule = rules[i];
				int pos = rule.find_first_of(':');
				string name = rule.substr(0,pos);
				rule = rule.substr(pos+1);
				int choices = stoi(rule);
				pos = rule.find_first_of(' ',1);
				rule = rule.substr(pos+1);
				int blanks = stoi(rule);
				pos = rule.find_first_of(' ',1);
				rule = rule.substr(pos+1);
				bool sorted = (rule[0] == 'F')?false:true;
				bool unique = (rule[2] == 'F')?false:true;
				long long validResults = 0;
				if(sorted == false && unique == false)
				{
					validResults = (long long)pow(choices,blanks);
				}
				else if( sorted == false && unique == true)
				{
					validResults = 1;
					for(int i = choices; i > choices-blanks; i--)
					{
						validResults *= i;
					}
				}
				else
				{
					if(unique == false)
						validResults = RecursiveCase(blanks, choices);
					else
						validResults = RecursiveCaseUnique(blanks, choices);
				}
				cout<<validResults<<":"<<name<<endl;
				if(resultmap.find(validResults) == resultmap.end())
					resultmap[validResults] = name;
				else
				{
					string thisname = resultmap[validResults];
					if(thisname.compare(name) < 0)
						resultmap[validResults+1] = name;
					else
						resultmap[validResults-1] = name;
				}
			}
			vector<string> results;
			for(auto iter = resultmap.begin(); iter != resultmap.end(); iter++)
			{
				results.push_back((*iter).second);
			}
			return results;
		}
		long long RecursiveCaseUnique(int BM, int CM)
		{
			long long count = 1;
			for(int i = CM; i > CM-BM; i--)
				count *= i;
			long long temp = 1;
			for(int i = 2; i <= BM; i++)
				temp *= i;
			count = count / temp;
			return count;
		}
		long long RecursiveCase(int BM, int CM)
		{
			long long count = 1;
			for(int i = CM + BM - 1; i > (CM-1); i--)
				count *= i;
			long long temp = 1;
			for(int i = 2; i <= BM; i++)
				temp *= i;
			count = count / temp;
			return count;
		}
		static void testThis()
		{
			vector<string> rules;
			/*rules.push_back("PICK ANY TWO: 10 2 F F");
			rules.push_back("PICK TWO IN ORDER: 10 2 T F");
			rules.push_back("PICK TWO DIFFERENT: 10 2 F T");
			rules.push_back("PICK TWO LIMITED: 10 2 T T");*/
			rules.push_back("INDIGO: 93 8 T F");
			rules.push_back("ORANGE: 29 8 F T");
			rules.push_back("VIOLET: 76 6 F F");
			rules.push_back("BLUE: 100 8 T T");
			rules.push_back("RED: 99 8 T T");
			rules.push_back("GREEN: 78 6 F T");
			rules.push_back("YELLOW: 75 6 F F");
			Lottery lot;
			vector<string> result = lot.sortByOdds(rules);
			for(unsigned int i = 0; i< result.size(); i++)
			{
				cout<<result[i]<<endl;
			}
		}
	};
	
	class BinaryCode
	{
	public:
		vector<string> decode(string message)
		{
			vector<string> result;
			result.push_back(decodeWithPrefix(0,message));
			result.push_back(decodeWithPrefix(1,message));
			return result;
		}
	private:
		string decodeWithPrefix(int prefix, string message)
		{
			if(message.length() == 0)
				return "NONE";
			string result;
			result = result + (char)(prefix + '0');
			int prevval = prefix;
			for(unsigned int i = 0; i < message.length() - 1; i++)
			{
				prevval = message[i] - (result[i]);
				if(i != 0)
				{
					prevval = prevval - (result[i-1] - '0');
				}
				if(prevval != 1 && prevval != 0)
				{
					return "NONE";
				}
				result = result + (char)(prevval + '0');
			}
			prevval = message[message.length() - 1] - (result[result.length() - 1] + ((result.length() > 1)?(result[result.length() - 2] - '0'):0));
			if(prevval != 0)
			{
				return "NONE";
			}
			return result;
		}
	};

	class Masterbrain
	{
	public:
		void parseSecretKey(string key, int& black, int& white)
		{
			black = atoi(key.c_str());
			key = key.substr(3);
			white = atoi(key.c_str());
		}
		bool calculateKey(string secret, string guess, int& black, int& white)
		{
			bool blackmap[] = {false,false,false,false};
			bool whitemap[] = {false,false,false,false};
			for(unsigned int i = 0; i < secret.size(); i++)
			{
				if(secret[i] == guess[i])
				{
					black++;
					blackmap[i] = true;
				}
			}
			for(unsigned int i = 0; i < secret.size(); i++)
			{
				if(blackmap[i] == true)
				{
					continue;
				}
				for(unsigned int j = 0; j < guess.size(); j++)
				{
					if(blackmap[j] == true || whitemap[j] == true)
					{
						continue;
					}
					if(secret[i] == guess[j])
					{
						white++;
						whitemap[j] = true;
						break;
					}
				}
			}
			return true;
		}
		bool isSecretValid(string secret, string guess, string key, bool invert)
		{
			int black = 0, white = 0;
			parseSecretKey(key, black, white);
			int blackguess = 0, whiteguess = 0;
			calculateKey(secret, guess, blackguess, whiteguess);
			if(blackguess != black || whiteguess != white)
			{
				return invert^false;
			}
			return invert^true;
		}
		vector<string> generateAllSecrets()
		{
			vector<string> secrets;
			for(int i = 1; i<= 7; i++)
			{
				for(int j = 1; j <= 7; j++)
				{
					for(int k = 1; k <= 7; k++)
					{
						for(int m = 1; m <= 7; m++)
						{
							string secret = "";
							secret += ('0' + i);
							secret += ('0' + j);
							secret += ('0' + k);
							secret += ('0' + m);
							secrets.push_back(secret);
						}
					}
				}
			}
			return secrets;
		}
		vector<string> useSecretsAndTest(vector<string> inputSecrets, string guess, string key, bool invert)
		{
			vector<string> secrets;
			for(unsigned int i = 0; i< inputSecrets.size(); i++)
			{
				if(isSecretValid(inputSecrets[i], guess, key, invert))
				{
					secrets.push_back(inputSecrets[i]);
				}
			}
			return secrets;
		}
		int possibleSecrets(vector <string> guesses, vector <string> results)
		{
			vector<string> secrets = generateAllSecrets();
			for(unsigned int i = 0; i < guesses.size(); i++)
			{
				secrets = useSecretsAndTest(secrets,guesses[i],results[i], false);
				if(secrets.size() == 0)
					break;
			}
			if(guesses.size() == 1)
			{
				return 2401 - secrets.size();
			}
			vector<string> alltrue = secrets;
			int sum = 0;
			for(unsigned int i = 0; i < guesses.size(); i++)
			{
				secrets = useSecretsAndTest(generateAllSecrets(),guesses[i],results[i],true);
				for(unsigned int j = 0; j < guesses.size(); j++)
				{
					if(j == i)
					{
						continue;
					}
					secrets = useSecretsAndTest(secrets,guesses[j],results[j], false);
					if(secrets.size() == 0)
						break;
				}
				sum += secrets.size();
			}
			//sum = sum - alltrue.size() * guesses.size();
			return sum;
		}

		void static testSecrets()
		{
			vector<string> guesses;
			vector<string> results;
			guesses.push_back("6162");
			results.push_back("2b 1w");
			guesses.push_back("6172");
			results.push_back("3b 0w");
			guesses.push_back("3617");
			results.push_back("0b 3w");
			Masterbrain b;
			cout<<b.possibleSecrets(guesses,results)<<endl;
		}
	};

	// Difficult Simulation Problem
	class Roundabout
	{
	public:
		enum Position
		{
			WEST = 0,
			SOUTH = 1,
			EAST = 2,
			NORTH = 3
		};
		Position intToPos(int pos)
		{
			switch(pos)
			{
			case 1:
				return SOUTH;
			case 0:
				return WEST;
			case 3:
				return NORTH;
			default:
				return EAST;
			};
		}
		Position StringToPos(char pos)
		{
			switch(pos)
			{
			case 'S':
				return SOUTH;
			case 'W':
				return WEST;
			case 'N':
				return NORTH;
			default:
				return EAST;
			};
		}
		class car
		{
		public:
			Position now;
			Position destination;
			bool entered;
		};
		bool canEnter(vector<car> roundabout, Position entry)
		{
			for(unsigned int i = 0; i <roundabout.size(); i++)
			{
				if((entry + 3)%4 == roundabout[i].now)
				{
					return false;
				}
			}
			return true;
		}
		void enterRoundabout(string dir, int& index, Position pos, vector<car>& roundabout, string left, int leftindex)
		{
			if(index < dir.size())
			{
				if(dir[index] != '-')
				{
					if(leftindex < left.size() && left[leftindex] != '-')
					{
					}
					else if(canEnter(roundabout,pos) )
					{
						car c;
						c.now = pos;
						c.destination = StringToPos(dir[index]);
						c.entered = true;
						roundabout.push_back(c);
						index++;
					}
				}
				else
				{
					index++;
				}
			}
		}
		int clearUpTime(string north, string east, string south, string west)
		{
			vector<car> roundabout;
			int count = 0;
			int w = 0, e = 0, s = 0, n = 0;
			while(true)
			{
				if(roundabout.size() == 0 && w == west.size() && e == east.size() && s == south.size() && n == north.size())
				{
					break;
				}
				count++;
				enterRoundabout(north, n, NORTH, roundabout, east, e);
				enterRoundabout(west, w, WEST, roundabout, north, n);
				enterRoundabout(south, s, SOUTH, roundabout, west, w);
				enterRoundabout(east, e, EAST, roundabout, south, s);
				for(vector<car>::iterator iter = roundabout.begin(); iter != roundabout.end(); )
				{
					if(iter->entered == true)
					{
						iter->entered = false;
						iter++;
					}
					else if(iter->now == iter->destination)
					{
						iter = roundabout.erase(iter);
					}
					else
					{
						iter->now = intToPos((iter->now + 1)%4);
						iter++;
					}
				}
				
			}
			return count;
		}
		static void testThis()
		{
			string north = "--";
			string east = "--";
			string south = "WE";
			string west = "-S";
			Roundabout r;
			cout<<r.clearUpTime(north,east,south,west);
		}
	};

	class BridgeCrossing
	{
	public:
		int minTime(vector <int> times)
		{
			int size = times.size();
			switch(size)
			{
			case 1:
				return times[0];
			case 2:
				return max(times[0],times[1]);
			case 3:
				return times[0] + times[1] + times[2];
			case 4:
				return times[0] + 3*times[1] + times[3];
			case 5:
				return 2*times[0] + 3*times[1] + times[2] + times[4];
			case 6:
				return 3*times[0] + 3*times[1] + times[2] + times[3] + times[5];
			default:
				return 0;
			}
		}
	};

	class PeopleCircle
	{
	public:
		string order(int numMales, int numFemales, int K)
		{
			int sum = numMales + numFemales;
			string result;
			int initial = 0;
			for(int i = 0; i < sum ; i++)
			{
				result = result + ' ';
			}
			for(int i = 0; i < numFemales; i++)
			{
				int j = 1;
				while( j <= K)
				{
					if( result[(initial + j - 1)%sum] != 'F')
					{
						j++;
					}
					else
						initial = (initial + 1)%sum;;
				}
				initial = (initial + K)%sum;
				if(initial != 0)
                    result[(initial-1)%sum] = 'F';
                else
                    result[sum-1] = 'F';
			}
			for(int i = 0; i < sum; i++)
			{
				if(result[i] != 'F')
					result[i] = 'M';
			}
			return result;
		}
		static void testThis()
		{
			PeopleCircle p;
			cout<<p.order(5,5,3)<<endl;
		}
	};



}
