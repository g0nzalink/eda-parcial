#include <bits/stdc++.h>
using namespace std;

// =====================================================================
// PERSISTENT SEGMENT TREE (update puntual + query de suma en rango)
// Version = puntero a la raiz. nullptr = arbol vacio (todo en 0).
// Cada update crea ~log(n)+1 nodos nuevos; el resto se comparte.
// =====================================================================

struct Node {
    Node *left, *right;
    long long sum;
    Node(Node* l = nullptr, Node* r = nullptr, long long s = 0)
        : left(l), right(r), sum(s) {}
};

long long getSum(Node* n) { return n ? n->sum : 0; }

// Devuelve la raiz de una nueva version donde a[pos] = val.
// (Para "sumar val": en la hoja usa getSum(prev) + val)
Node* update(Node* prev, int l, int r, int pos, long long val) {
    if (l == r) return new Node(nullptr, nullptr, val);
    int m = (l + r) / 2;
    Node* nl = prev ? prev->left : nullptr;
    Node* nr = prev ? prev->right : nullptr;
    if (pos <= m) nl = update(nl, l, m, pos, val);
    else          nr = update(nr, m + 1, r, pos, val);
    return new Node(nl, nr, getSum(nl) + getSum(nr));
}

// Suma en [ql, qr] en la version con raiz cur
long long query(Node* cur, int l, int r, int ql, int qr) {
    if (!cur || qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return cur->sum;
    int m = (l + r) / 2;
    return query(cur->left, l, m, ql, qr) + query(cur->right, m + 1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 10;                          // tamanio del arreglo (posiciones 1..n)
    vector<Node*> roots(1, nullptr);     // roots[0] = arreglo lleno de ceros

    // Crear version nueva a partir de la version t:
    //   roots.push_back(update(roots[t], 1, n, pos, val));
    // Consultar la suma en [l, r] de la version v:
    //   cout << query(roots[v], 1, n, l, r) << "\n";

    return 0;
}