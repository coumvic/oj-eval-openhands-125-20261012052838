#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
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
        
        vector<Constraint> constraints;
        vector<int> all_vars;
        
        // Read all constraints and collect variables
        for (int k = 0; k < n; k++) {
            int i, j, e;
            scanf("%d %d %d", &i, &j, &e);
            constraints.push_back({i, j, e});
            all_vars.push_back(i);
            all_vars.push_back(j);
        }
        
        // Coordinate compression
        sort(all_vars.begin(), all_vars.end());
        all_vars.erase(unique(all_vars.begin(), all_vars.end()), all_vars.end());
        
        map<int, int> var_to_idx;
        for (int idx = 0; idx < (int)all_vars.size(); idx++) {
            var_to_idx[all_vars[idx]] = idx;
        }
        
        DSU dsu(all_vars.size());
        
        // First pass: process all equality constraints
        for (const auto& constraint : constraints) {
            if (constraint.e == 1) {  // equality constraint
                int idx_i = var_to_idx[constraint.i];
                int idx_j = var_to_idx[constraint.j];
                dsu.unite(idx_i, idx_j);
            }
        }
        
        // Second pass: check all inequality constraints
        bool possible = true;
        for (const auto& constraint : constraints) {
            if (constraint.e == 0) {  // inequality constraint
                int idx_i = var_to_idx[constraint.i];
                int idx_j = var_to_idx[constraint.j];
                if (dsu.same(idx_i, idx_j)) {
                    possible = false;
                    break;
                }
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}