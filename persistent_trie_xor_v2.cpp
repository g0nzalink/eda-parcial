#include <bits/stdc++.h>
using namespace std;

// =====================================================================
// MULTICONJUNTO PERSISTENTE (agregar, quitar, k-esimo menor)
// Trie binario persistente: cada nodo guarda cnt = cuantos elementos
// del multiconjunto pasan por el. Como se recorre del bit mas alto al
// mas bajo y el hijo 0 va antes que el 1, el trie esta ORDENADO por valor.
//
// Los nodos viven en un arreglo (pool) y se referencian por indice;
// el indice 0 es el nodo vacio (ch = 0, cnt = 0). Un nodo ocupa 12 bytes,
// asi que caben sobrados los ~6.2 millones de nodos (~75 MB).
// =====================================================================

const int BITS = 30;                          // valores <= 1e9 < 2^30
const int MAXQ = 200005;
const int MAXNODES = MAXQ * (BITS + 1) + 5;

struct Node {
    int ch[2];
    int cnt;
};

Node pool[MAXNODES];
int tot = 0;

// Nueva version = prev con delta (+1 agrega x, -1 quita x)
int update(int prev, int x, int delta) {
    int root = ++tot, cur = root;
    pool[cur] = pool[prev];                   // copia del nodo
    pool[cur].cnt += delta;
    for (int b = BITS - 1; b >= 0; b--) {
        int bit = (x >> b) & 1;
        int old = pool[prev].ch[bit];         // hijo en la version anterior
        int nw = ++tot;
        pool[nw] = pool[old];                 // copia del hijo
        pool[nw].cnt += delta;
        pool[cur].ch[bit] = nw;               // enlazamos la copia
        cur = nw;
        prev = old;
    }
    return root;
}

// k-esimo menor elemento (k desde 1) de la version root
int kth(int root, int k) {
    int res = 0, cur = root;
    for (int b = BITS - 1; b >= 0; b--) {
        int left = pool[cur].ch[0];
        int c = pool[left].cnt;               // cuantos elementos tienen bit b = 0
        if (k <= c) {
            cur = left;                       // el k-esimo esta entre los que tienen 0
        } else {
            k -= c;                           // nos saltamos esos c elementos
            res |= (1 << b);
            cur = pool[cur].ch[1];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;
    vector<int> roots(1, 0);                  // version 0 = vacio

    for (int i = 1; i <= Q; i++) {
        int t, v, y;
        cin >> t >> v >> y;
        if (t == 1) {
            roots.push_back(update(roots[v], y, +1));
        } else if (t == 2) {
            roots.push_back(update(roots[v], y, -1));
        } else {
            cout << kth(roots[v], y) << "\n";
            roots.push_back(roots[v]);        // la version i igual existe
        }
    }
    return 0;
}