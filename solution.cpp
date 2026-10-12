#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class DSU {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
    
public:
    int find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

struct Constraint {
    int i, j, e;
};

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<Constraint> equality_constraints;
        vector<Constraint> inequality_constraints;
        
        // Read all constraints and separate them
        for (int k = 0; k < n; k++) {
            int i, j, e;
            scanf("%d %d %d", &i, &j, &e);
            
            if (e == 1) {
                equality_constraints.push_back({i, j, e});
            } else {
                inequality_constraints.push_back({i, j, e});
            }
        }
        
        DSU dsu;
        
        // Process all equality constraints
        for (const auto& constraint : equality_constraints) {
            dsu.unite(constraint.i, constraint.j);
        }
        
        // Check all inequality constraints
        bool possible = true;
        for (const auto& constraint : inequality_constraints) {
            if (dsu.same(constraint.i, constraint.j)) {
                possible = false;
                break;
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}