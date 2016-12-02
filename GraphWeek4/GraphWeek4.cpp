/*
 * GraphWeek4.cpp
 *
 *  Created on: Nov 26, 2016
 *      Author: Feng
 */


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

int main() {

	ifstream in("array.txt");
	unordered_map<long,vector<long > > hash;
	vector<long> nums;
	int count = 0;
	long tmp;
	unordered_map<int,bool> b;
	for(int t = -10000;t<=10000;t++){
		b[t] = false;
	}
	while (in >> tmp){
		nums.push_back(tmp);
		hash[tmp/10000].push_back(tmp);
	}
	//cout<<hash.size()<<endl;
	for(auto x : nums){
		for(auto y : hash[-x/10000-1]){
			if (-10000<=(y+x) && (x+y)<=10000 && x!=y){
				b[x+y] = true;
			}
		}
		for(auto y : hash[-x/10000]){
			if (-10000<=(y+x) && (x+y)<=10000 && x!=y){
				b[x+y] = true;
			}
		}
		for(auto y : hash[-x/10000+1]){
			if (-10000<=(y+x) && (x+y)<=10000 && x!=y){
				b[x+y] = true;
			}
		}
	}
	for(auto iter = b.begin(); iter!= b.end();iter++){
		if( iter->second == true){
			count++;
		}

	}
	cout<<"The number is:"<<count<<endl;
	return 0;
}
