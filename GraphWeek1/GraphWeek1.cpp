/*
 * GraphWeek1.cpp
 *
 *  Created on: Nov 23, 2016
 *      Author: Feng
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int t = 1;			// count the size of each SCC
vector<int> cnt;   // array to count the size of every SCC
vector<int> order; // get the magic order after the first DFS
class Graph // directed graph implementation
{
public:
    int V;    // No. of vertices
    vector<bool> visited;
    vector<vector<int> >adj;    // An array of adjacency lists
public:
    Graph(int V){
    	for(int i=0;i<V;i++){
    		vector<int> temp;
    		adj.push_back(temp);
    		visited.push_back(false);
    	}
        this->V = V;
    }
    void addEdge(int v, int w)
    {
        adj[v].push_back(w); // Add w to v’s list.
    }
};

void DFS(Graph &G,int V){
	G.visited[V] = true;
	for(auto x: G.adj[V]){
		if(G.visited[x] == false){
			DFS(G,x);
		}
	}
	order.push_back(V);
}
void DFS1(Graph &G,int V){
	G.visited[V] = true;
	for(auto x: G.adj[V]){
		if(G.visited[x] == false){
			t++;
			DFS1(G,x);
		}
	}
}
void DFSloop1(Graph &G){
	// reversed Graph
	for(int n = G.V - 1;n >= 0;n--){
		if(G.visited[n] == false){
			DFS(G,n);
		}
	}
}
void DFSloop2(Graph &G){
	// forward Graph
	reverse(order.begin(),order.end());
	for(int i = 0 ;i<order.size();i++){
		if(G.visited[order[i]] == false){
			// if not visited
			DFS1(G,order[i]);
			cnt.push_back(t);
			t = 1;
		}
	}
}
void MyAlg(Graph G, Graph G_inv){
	cout<< "Begin my Algorithm"<<endl;
	DFSloop1(G_inv);
	DFSloop2(G);
	cout<<"Number of SCC: "<<cnt.size()<<endl;
	sort(cnt.begin(),cnt.end());
	if(cnt.size()>=5){
		for(int i =0 ;i<5;i++){
			cout<< cnt[cnt.size()-1-i] <<" ";
		}
	}
	else{
		for(int i = 0; i<cnt.size();i++){
			cout<< cnt[cnt.size()-1-i] <<" ";
		}
		for(int i=0 ; i< 5-cnt.size();i++){
			cout<< 0 <<" ";
		}
	}
	cout<<endl;
}
int main() {
	vector<int> v;
	ifstream in("array1.txt");
	string str;
	Graph G(875714);
	Graph G_inv(875714);
	while (getline(in,str)){
		istringstream ss(str);
		int temp;
		while (ss >> temp)
		{
			v.push_back(temp);
		}
		G.addEdge(v[0]-1,v[1]-1);
		G_inv.addEdge(v[1]-1,v[0]-1);
		v.clear();
	}
	MyAlg(G,G_inv);
	return 0;
}
