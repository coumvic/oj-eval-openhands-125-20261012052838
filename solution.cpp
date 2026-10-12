#include <cstdio>
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

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<pair<int, int>> equalities;
        vector<pair<int, int>> inequalities;
        vector<int> all_vars;
        
        // Read all constraints
        for (int k = 0; k < n; k++) {
            int i, j, e;
            scanf("%d %d %d", &i, &j, &e);
            
            all_vars.push_back(i);
            all_vars.push_back(j);
            
            if (e == 1) {
                equalities.push_back({i, j});
            } else {
                inequalities.push_back({i, j});
            }
        }
        
        // Coordinate compression
        sort(all_vars.begin(), all_vars.end());
        all_vars.erase(unique(all_vars.begin(), all_vars.end()), all_vars.end());
        
        map<int, int> var_to_idx;
        for (int idx = 0; idx < (int)all_vars.size(); idx++) {
            var_to_idx[all_vars[idx]] = idx;
        }
        
        DSU dsu(all_vars.size());
        
        // Process all equality constraints
        for (const auto& eq : equalities) {
            int idx_i = var_to_idx[eq.first];
            int idx_j = var_to_idx[eq.second];
            dsu.unite(idx_i, idx_j);
        }
        
        // Check all inequality constraints
        bool possible = true;
        for (const auto& ineq : inequalities) {
            int idx_i = var_to_idx[ineq.first];
            int idx_j = var_to_idx[ineq.second];
            if (dsu.same(idx_i, idx_j)) {
                possible = false;
                break;
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}