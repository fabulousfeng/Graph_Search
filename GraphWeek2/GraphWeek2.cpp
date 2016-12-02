#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <climits>
using namespace std;
class Graph // directed graph implementation
{
public:
    int V;    // No. of vertices
    vector<vector<pair<int,int> > >adj;    // An array of adjacency lists
public:
    Graph(int V){
    	for(int i=0;i<V;i++){
    		vector<pair<int,int>> temp;
    		adj.push_back(temp);
    	}
        this->V = V;
    }
    void addEdge(int v, int w,int len)
    {
        adj[v].push_back(make_pair(w,len)); // Add w to v’s list.
    }
};

int djikstra(Graph G, int source, int target){
	vector<int> min_distance(G.V, INT_MAX); // initial all the distance to be infinite
	min_distance[source] = 0; 	// assign the start distance to be 0
	set<pair<int,int> > V; // distance and the source, set is sorted by the first element by default
	V.insert(make_pair(0,source));
	while(!V.empty()){
		int s = V.begin()->second; //  vertex we want to extract, we first store this vertex in s
		if (s == target) return min_distance[s];
		V.erase(V.begin()); // extract the minimal element from the set
		for(auto x : G.adj[s]){
			// x is pair<dest,distance>
			// for all the edges starts from s
			if(min_distance[x.first] > min_distance[s] + x.second){
				// if we find a shorter distance
				// update the new shorter distance
				min_distance[x.first] = min_distance[s] + x.second;
				V.insert(make_pair(min_distance[x.first],x.first));
			}
		}
	}
	return INT_MAX;// if no path is found
}
int main() {
	ifstream in("array.txt");
	string str;
	Graph G(200); // there are 200 vertices in the graph
	while (getline(in,str)){
		istringstream ss(str);
		string temp;
		int t;
		ss>>t; // the start vertex
		while (ss >> temp)
		{
			// separate the string by comma
			// the first integer is the end vertex and the second the integer is the length
			size_t found = temp.find(',');
			// cast each substring into integer
		    int dest = stoi(temp.substr(0,found));
		    int len = stoi(temp.substr(found+1));
		    G.addEdge(t-1,dest-1,len);
		}
	}
	vector<int> d ={7,37,59,82,99,115,133,165,188,197};
	vector<int> result;
	for(auto x:d){
		result.push_back(djikstra(G,0,x-1));
	}
	for(auto x: result){
		cout<< x <<" ";
	}
	cout<<endl;

	return 0;
}

