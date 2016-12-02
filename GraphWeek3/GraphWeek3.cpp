/*
 * GraphWeek3.cpp
 *
 *  Created on: Nov 24, 2016
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
class minheap{
private:
	vector<int> heap;
public:
	void insert(int x){
		heap.push_back(x);
		auto num = heap.size()-1;
		while(num >= 1 && heap[num] < heap[(num-1)/2]){
			swap(heap[num],heap[(num-1)/2]);
			num = (num - 1) / 2;
		}
	}
	void extract_min(){
		if(heap.empty()) return;
		swap(heap[0],heap[heap.size() - 1]);
		heap.pop_back();
		int index = 0;
		int minval = 0;
		int minindex = 0;
		while((2 * index +1) < heap.size()){
			if(2 * index +2 == heap.size()){
	            minval = heap[2*index + 1];
	            minindex = 2*index + 1;
			}
			else if (heap[2*index + 1] < heap[2*index + 2]) {
	            minval = heap[2*index + 1];
	            minindex = 2*index + 1;
			}
			else{
	            minval = heap[2*index + 2];
	            minindex = 2*index + 2;
			}
			if (heap[index] > minval) {
	            swap(heap[index],heap[minindex]);
	            index = minindex;
			}
			else
			     break;
		}
	}
	int getmin(){
		if(heap.empty()) return 0;
		else
			return heap[0];
	}
	int getsize(){
			return heap.size();
		}

};


class maxheap{
private:
	vector<int> heap;
public:
	void insert(int x){
		heap.push_back(x);
		auto num = heap.size()-1;
		while(num >= 1 && heap[num] > heap[(num-1)/2]){
			swap(heap[num],heap[(num-1)/2]);
			num = (num - 1) / 2;
		}
	}
	void extract_max(){
		if(heap.empty()) return;
		swap(heap[0],heap[heap.size() - 1]);
		heap.pop_back();
		int index = 0;
		int maxval = 0;
		int maxindex = 0;
		while((2 * index +1) < heap.size()){
			if(2 * index +2 == heap.size()){
	            maxval = heap[2*index + 1];
	            maxindex = 2*index + 1;
			}
			else if (heap[2*index + 1] > heap[2*index + 2]) {
	            maxval = heap[2*index + 1];
	            maxindex = 2*index + 1;
			}
			else{
	            maxval = heap[2*index + 2];
	            maxindex = 2*index + 2;
			}
			if (heap[index] < maxval) {
	            swap(heap[index],heap[maxindex]);
	            index = maxindex;
			}
			else
			     break;
		}
	}
	int getmax(){
		if(heap.empty()) return INT_MAX;
		else
			return heap[0];
	}
	int getsize(){
		return heap.size();
	}

};
int main() {
	vector<int> median;
	maxheap H_low;
	minheap H_high;
	ifstream in("array.txt");
	int tmp;
	while (in >> tmp){

		if(tmp < H_low.getmax()){
			H_low.insert(tmp);
		}
		else{
			H_high.insert(tmp);
		}
		if(H_high.getsize() - H_low.getsize() == 2){
			int temp = H_high.getmin();
			H_high.extract_min();
			H_low.insert(temp);
		}
		else if(H_low.getsize() - H_high.getsize() == 2){
					int temp = H_low.getmax();
					H_low.extract_max();
					H_high.insert(temp);
				}
		if((H_low.getsize() + H_high.getsize()) % 2 == 1){
			if(H_low.getsize() < H_high.getsize())
				median.push_back(H_high.getmin());
			else
				median.push_back(H_low.getmax());
		}
		else{
			median.push_back(H_low.getmax());
		}
	}
		int result = 0;
		for(auto x : median){
			result += x;
		}
		cout<< result % 10000 <<endl;

	return 0;
}

