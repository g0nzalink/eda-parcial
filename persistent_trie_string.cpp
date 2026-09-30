#include <bits/stdc++.h>
using namespace std;

// =====================================================================
// PERSISTENT TRIE DE STRINGS (letras minusculas 'a'..'z')
// Cada nodo guarda:
//   pref = cuantas palabras pasan por ese nodo (sirve para prefijos)
//   fin  = cuantas palabras terminan exactamente en ese nodo
// update(prev, s, +1) inserta s, update(prev, s, -1) la elimina
// (solo si existe). Cada operacion crea |s| + 1 nodos nuevos.
// Version = puntero a la raiz. nullptr = trie vacio.
//
// MEMORIA: cada nodo ocupa ~220 bytes (26 punteros). Con 256 MB caben
// ~1 millon de nodos como maximo. Calcula (suma de los largos de los
// strings + numero de operaciones) antes de usarlo.
// Si el alfabeto es distinto, cambia ALF y el 'a' en c - 'a'.
// =====================================================================

const int ALF = 26;

struct Node {
    Node* ch[ALF];
    int pref, fin;
    Node() : pref(0), fin(0) {
        for (int i = 0; i < ALF; i++) ch[i] = nullptr;
    }
};

// Devuelve la raiz de la nueva version. delta = +1 (insertar) o -1 (borrar)
Node* update(Node* prev, const string& s, int delta) {
    // "new Node(*prev)" copia el nodo entero (hijos y contadores)
    Node* root = prev ? new Node(*prev) : new Node();
    root->pref += delta;

    Node* cur = root;      // nodo nuevo en el que estamos
    Node* p = prev;        // el mismo nodo en la version anterior
    for (char c : s) {
        int x = c - 'a';
        Node* old = p ? p->ch[x] : nullptr;
        Node* nw = old ? new Node(*old) : new Node();   // copia del hijo
        nw->pref += delta;
        cur->ch[x] = nw;   // enlazamos la copia (el resto de hijos se comparte)
        cur = nw;
        p = old;
    }
    cur->fin += delta;     // la palabra termina aqui
    return root;
}

// Cuantas palabras de la version root empiezan con el prefijo s
int countPrefix(Node* root, const string& s) {
    Node* cur = root;
    for (char c : s) {
        if (!cur) return 0;
        cur = cur->ch[c - 'a'];
    }
    return cur ? cur->pref : 0;
}

// Cuantas veces aparece exactamente la palabra s en la version root
int countWord(Node* root, const string& s) {
    Node* cur = root;
    for (char c : s) {
        if (!cur) return 0;
        cur = cur->ch[c - 'a'];
    }
    return cur ? cur->fin : 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Ejemplo de uso:
    vector<Node*> roots(1, nullptr);                  // version 0 = vacia
    roots.push_back(update(roots[0], "hola", +1));    // version 1
    roots.push_back(update(roots[1], "holanda", +1)); // version 2
    roots.push_back(update(roots[1], "sol", +1));     // version 3 (sale de la 1)
    roots.push_back(update(roots[2], "hola", -1));    // version 4

    cout << countPrefix(roots[2], "hol") << "\n";     // 2
    cout << countPrefix(roots[3], "hol") << "\n";     // 1
    cout << countWord(roots[4], "hola") << "\n";      // 0
    return 0;
}