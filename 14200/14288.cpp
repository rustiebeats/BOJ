#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 100000;
const int MAX_ST = 1<<18;

struct SegTree{
	int arr[MAX_ST], lazy[MAX_ST];
	SegTree(){
		fill(arr, arr+MAX_ST, 0);
		fill(lazy, lazy+MAX_ST, 0);
	}
	void construct(){
		for(int i = MAX_ST/2-1; i > 0; --i)
			arr[i] = arr[i*2] + arr[i*2+1];
	}
	void propagate(int node, int ns, int ne){
		if(lazy[node] != 0){
			if(node < MAX_ST/2){
				lazy[node*2] += lazy[node];
				lazy[node*2+1] += lazy[node];
			}
			arr[node] += lazy[node] * (ne-ns);
			lazy[node] = 0;
		}
	}
	void add(int s, int e, int k){ add(s, e, k, 1, 0, MAX_ST/2); }
	void add(int s, int e, int k, int node, int ns, int ne){
		propagate(node, ns, ne);
		if(e <= ns || ne <= s) return;
		if(s <= ns && ne <= e){
			lazy[node] += k;
			propagate(node, ns, ne);
			return;
		}
		int mid = (ns+ne)/2;
		add(s, e, k, node*2, ns, mid);
		add(s, e, k, node*2+1, mid, ne);
		arr[node] = arr[node*2] + arr[node*2+1];
	}
	int sum(int s, int e){ return sum(s, e, 1, 0, MAX_ST/2); }
	int sum(int s, int e, int node, int ns, int ne){
		propagate(node, ns, ne);
		if(e <= ns || ne <= s) return 0;
		if(s <= ns && ne <= e) return arr[node];
		int mid = (ns+ne)/2;
		return sum(s, e, node*2, ns, mid) + sum(s, e, node*2+1, mid, ne);
	}
};

int N, M, vcnt, L[MAX], R[MAX];
vector<int> child[MAX];

void dfs(int curr){
	L[curr] = R[curr] = vcnt++;
	for(int next: child[curr]){
		dfs(next);
		R[curr] = R[next];
	}
}

int main(){
	bool mode = false;
	scanf("%d %d", &N, &M);
	for(int i = 0; i < N; ++i){
		int k;
		scanf("%d", &k);
		if(k > 0) child[k-1].push_back(i);
	}
	dfs(0);
	SegTree ST1, ST2;
	for(int i = 0; i < M; ++i){
		int o, p, q;
		scanf("%d", &o);
		if(o == 3) mode = !mode;
		else{
			scanf("%d", &p);
			--p;
			if(o == 1){
				scanf("%d", &q);
				if(mode) ST2.add(L[p], L[p]+1, q);
				else ST1.add(L[p], R[p]+1, q);
			}
			else printf("%d\n", ST1.sum(L[p], L[p]+1) + ST2.sum(L[p], R[p]+1));
		}
	}
}