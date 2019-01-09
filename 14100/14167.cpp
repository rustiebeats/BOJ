#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
const int MAX = 1000;
typedef tuple<int, int, int> Edge;

struct UnionFind{
    int p[MAX];
    UnionFind(){ fill(p, p+MAX, -1); }
    int f(int a){
        if(p[a] < 0) return a;
        return p[a] = f(p[a]);
    }
    bool u(int a, int b){
        a = f(a);
        b = f(b);
        if(a == b) return false;
        if(p[a] < p[b]){
            p[a] += p[b];
            p[b] = a;
        }
        else{
            p[b] += p[a];
            p[a] = b;
        }
        return true;
    }
};

int main(){
    int N, x[MAX], y[MAX];
    vector<Edge> edge;
    scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%d %d", x+i, y+i);
        for(int j = 0; j < i; ++j)
            edge.push_back(Edge((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]), i, j));
    }
    sort(edge.begin(), edge.end());

    int result = 0, cnt = 0;
    UnionFind UF;
    for(auto &e: edge){
        int u, v, w;
        tie(w, u, v) = e;
        if(UF.u(u, v)){
            result = w;
            if(++cnt == N-1) break;
        }
    }
    printf("%d\n", result);
}