/*
 * ID: jhuang1
 * PROG: Fine Dining
 * LANG: C++11
 * RESULT: 8/10
 * TIME: 1ms
 * COMMENT: test1
 * */

#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;
 
int n, m, k, H[100000], Y[100000];
vector<int> neighbors[100001];
map<pair<int,int>, int> val;
map<int,int> dist; 	
 
void spth(int s) {
	set<pair<int,int>> visited;
  	visited.insert(make_pair(0, s));
  	while (!visited.empty()) {
    	int i = visited.begin() -> second;
    	visited.erase(visited.begin());
    	for (auto j : neighbors[i]) {
      		if (dist.count(j) == 0 || dist[i] + val[make_pair(i, j)] < dist[j]) {
				dist[j] = dist[i] + val[make_pair(i, j)];
				visited.insert(make_pair(dist[j], j));
    		}
    	}
    }
}
 
int main() {
  	ifstream fin("dining.in");
  	fin >> n >> m >> k;
  	int a, b, t;
  	for (int i = 0; i < m; ++i) {
    	fin >> a >> b >> t;
    	a--; 
    	b--;
    	neighbors[a].push_back(b);
    	neighbors[b].push_back(a);
    	val[make_pair(a, b)] = t;
    	val[make_pair(b, a)] = t;
  	}
  	for (int i = 0; i < k; ++i) {
    	fin >> H[i] >> Y[i];
    	H[i]--;
  	}

  	spth(n - 1);

  	map<int, int> orig_dist = dist;

  	for (int i = 0; i < k; ++i) {
    	neighbors[n].push_back(H[i]);
    	val[make_pair(n, H[i])] = orig_dist[H[i]] - Y[i];
  	}

  	dist.clear();
  	spth(n);

  	ofstream fout("dining.out");
  	for (int i = 0; i < n - 1; ++i) {
    	fout << (dist[i] <= orig_dist[i]) << endl;
    }
  
  	return 0;
}


/*
Instructions:
git add dining_gold.cpp
git commit
git push
*/
