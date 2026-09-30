#include <bits/stdc++.h>
using namespace std;

// =====================================================================
// PERSISTENT STACK
// push / pop en O(1) de tiempo y memoria.
// Version = puntero al tope. nullptr = pila vacia.
// =====================================================================

struct Nodo {
    int val;            // valor de este elemento
    long long suma;     // suma de toda la pila hasta este nodo
    int tam;            // cantidad de elementos de la pila
    Nodo* prev;         // nodo de abajo
};

Nodo* push(Nodo* top, int x) {
    long long s = top ? top->suma : 0;
    int t = top ? top->tam : 0;
    return new Nodo{x, s + x, t + 1, top};
}

Nodo* pop(Nodo* top) {      // OJO: top no debe ser nullptr
    return top->prev;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Ejemplo (formato del problema Snowmen):
    // "t m": clonar la version t y poner m; si m == 0, quitar el tope.
    int n;
    cin >> n;

    vector<Nodo*> v(1, nullptr);   // version 0 = pila vacia
    long long total = 0;

    for (int i = 0; i < n; i++) {
        int t, m;
        cin >> t >> m;
        Nodo* nuevo = (m == 0) ? pop(v[t]) : push(v[t], m);
        v.push_back(nuevo);
        if (nuevo) total += nuevo->suma;
    }

    cout << total << "\n";
    return 0;
}