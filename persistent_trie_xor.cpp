#include <bits/stdc++.h>
using namespace std;

// =====================================================================
// PERSISTENT TRIE BINARIO (problemas de XOR)
// Version i = trie con los primeros i numeros insertados.
// cnt = cuantos numeros pasan por ese nodo.
// Para un rango [l, r] de posiciones se recorren a la vez roots[r] y
// roots[l-1] y se restan los cnt.
// Version = puntero a la raiz. nullptr = trie vacio.
//
// MEMORIA: cada insercion crea BITS+1 = 31 nodos de ~32 bytes.
// Con n = 2e5 son ~200 MB: al limite de 256 MB. Si los valores son
// menores (por ejemplo <= 1e6), baja BITS a 20 y sobra memoria.
// =====================================================================

const int BITS = 30;                      // valores < 2^30 (~1e9)

struct Node {
    Node* ch[2];
    int cnt;
    Node() : cnt(0) { ch[0] = ch[1] = nullptr; }
};

int getCnt(Node* n) { return n ? n->cnt : 0; }

// Inserta x sobre la version prev y devuelve la nueva raiz.
Node* insert(Node* prev, int x, int b = BITS - 1) {
    Node* nuevo = new Node();
    nuevo->cnt = getCnt(prev) + 1;
    if (b < 0) return nuevo;              // llegamos a la hoja
    int bit = (x >> b) & 1;
    if (prev) {                           // copiamos los hijos de la version anterior
        nuevo->ch[0] = prev->ch[0];
        nuevo->ch[1] = prev->ch[1];
    }
    nuevo->ch[bit] = insert(prev ? prev->ch[bit] : nullptr, x, b - 1);
    return nuevo;
}

// Maximo (x XOR y) con y entre los numeros que estan en rootR pero no en rootL.
// Todos los elementos de la version v: maxXor(nullptr, roots[v], x)
// (el rango debe tener al menos un elemento)
int maxXor(Node* rootL, Node* rootR, int x) {
    int res = 0;
    for (int b = BITS - 1; b >= 0; b--) {
        int bit = (x >> b) & 1, want = bit ^ 1;   // ideal: el bit contrario
        Node* rw = rootR ? rootR->ch[want] : nullptr;
        Node* lw = rootL ? rootL->ch[want] : nullptr;
        if (getCnt(rw) - getCnt(lw) > 0) {
            res |= (1 << b);
            rootR = rw;
            rootL = lw;
        } else {
            rootR = rootR ? rootR->ch[bit] : nullptr;
            rootL = rootL ? rootL->ch[bit] : nullptr;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Ejemplo: dado a[1..n], responder "max de x ^ a[j], l <= j <= r"
    int n;
    cin >> n;
    vector<Node*> roots(n + 1, nullptr);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        roots[i] = insert(roots[i - 1], a);
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        cout << maxXor(roots[l - 1], roots[r], x) << "\n";
    }
    return 0;
}