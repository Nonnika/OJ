#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

// 并查集实现，同时维护连通分量的最大权值
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    vector<long long> maxVal; // 每个连通分量的最大权值
    
public:
    UnionFind(int n, const vector<long long>& a) {
        parent.resize(n + 1);                                    
        rank.resize(n + 1, 0);
        maxVal.resize(n + 1);
        
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            maxVal[i] = a[i]; // 初始时每个节点独立，最大权值就是自己的权值
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;
        
        // 按秩合并
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
            maxVal[rootY] = max(maxVal[rootY], maxVal[rootX]);
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
            maxVal[rootX] = max(maxVal[rootX], maxVal[rootY]);
        } else {
            parent[rootY] = rootX;
            maxVal[rootX] = max(maxVal[rootX], maxVal[rootY]);
            rank[rootX]++;
        }
    }
    
    long long getMaxValue(int x) {
        return maxVal[find(x)];
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    UnionFind uf(n, a);
    
    // 处理已有的边
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        uf.unite(u, v);
    }
    
    // 收集所有连通分量的最大权值
    vector<long long> maxValues;
    vector<bool> visited(n + 1, false);
    
    for (int i = 1; i <= n; i++) {
        int root = uf.find(i);
        if (!visited[root]) {
            visited[root] = true;
            maxValues.push_back(uf.getMaxValue(root));
        }
    }
    
    // 如果只有一个连通分量，不需要加边
    if (maxValues.size() <= 1) {
        cout << 0 << endl;
        return 0;
    }
    
    // 对最大权值排序
    sort(maxValues.begin(), maxValues.end());
    
    // 计算总代价：第二小的 + 第三小的 + ... + 最大的
    long long totalCost = 0;
    for (size_t i = 1; i < maxValues.size(); i++) {
        totalCost += maxValues[i];
    }
    
    cout << totalCost << endl;
    
    return 0;
}