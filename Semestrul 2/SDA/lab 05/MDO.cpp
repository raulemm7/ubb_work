#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>
#include <stack>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) :comp{r}{
    /* de adaugat */
    root = -1;
    firstFree = 0;
    capacity = MAX_CAP;
    elems = new NodABC[capacity];
    for(int i = 0; i < capacity; ++i){
        elems[i].parent = elems[i].right=-1;
        elems[i].left = i + 1;               //il folosim pe post de urmator
    }
    elems[capacity - 1].left = -1;
}


void MDO::adauga(TCheie c, TValoare v) {
    /* de adaugat */
    TElem val = make_pair(c,v);

    // daca arborele nu are niciun element, initializez radacina
    if(root == -1) {
        root = firstFree;
        int nw_ff = elems[firstFree].left;
        elems[firstFree] = aloca(val);
        elems[firstFree].parent = -1;
        firstFree = nw_ff;
        return;
    }

    // ajung la o frunza
    int prev;
    int act = root;
    while(act != -1) {
        prev = act;
        if (comp(val.first, elems[act].elem.first)) {
            act = elems[act].left;
        } else {
            act = elems[act].right;
        }
    }

    // determin unde pozitionez noul element, in stanga sau in dreapta
    if(comp(val.first, elems[prev].elem.first)) {
        elems[prev].left = firstFree;
        int next = elems[firstFree].left;
        elems[firstFree] = aloca(val);
        elems[firstFree].parent = prev;
        firstFree = next;
    } else {
        elems[prev].right = firstFree;
        int next = elems[firstFree].left;
        elems[firstFree] = aloca(val);
        elems[firstFree].parent = prev;
        firstFree = next;
    }

    // daca in urma alocarii vectorul a ramas fara spatiu, redimensionez
    if(firstFree == -1) {
        redim();
    }
}

vector<TValoare> MDO::cauta(TCheie c) const {
    /* de adaugat */
    vector<TValoare> rez;
    rez.clear();
    int node = root;
    while (node != -1) {
        if (elems[node].elem.first == c) {
            rez.push_back(elems[node].elem.second);
        }
        if (comp(c, elems[node].elem.first)) {
            node = elems[node].left;
        } else {
            node = elems[node].right;
        }
    }
    return rez;
}

bool MDO::sterge(TCheie c, TValoare v) {
    /* de adaugat */
    int node = root;
    int victim = -1;
    while (node != -1) {
        if (elems[node].elem.first == c && elems[node].elem.second == v) {
            victim = node;
            break;
        }
        if (comp(c, elems[node].elem.first)) {
            node = elems[node].left;
        } else {
            node = elems[node].right;
        }
    }
    if (victim == -1) {
        return false;
    }
    if (elems[victim].left == -1) {
        translate(victim, elems[victim].right);
    } else if (elems[victim].right == -1) {
        translate(victim, elems[victim].left);
    } else {
        node = tree_min(elems[victim].right);
        if (elems[node].parent != victim) {
            translate(node, elems[node].right);
            elems[node].right = elems[victim].right;
            elems[elems[node].right].parent = node;
        }
        translate(victim, node);
        elems[node].left = elems[victim].left;
        elems[elems[node].left].parent = node;
    }
    del_node(victim);
    return true;
}

int MDO::dim() const {
    /* de adaugat */
    stack<int> st;
    int len = 0;
    int node = root;
    st.push(node);
    while (!st.empty()) {
        node = st.top();
        st.pop();
        if (node != -1) {
            ++len;
            st.push(elems[node].left);
            st.push(elems[node].right);
        }
    }
    return len;
}

bool MDO::vid() const {
    /* de adaugat */
    return root == -1;
}

IteratorMDO MDO::iterator() const {
    return IteratorMDO(*this);
}

MDO::~MDO() {
    /* de adaugat */
    delete elems;
}

NodABC MDO::aloca(TElem info) {
    NodABC ret;
    ret.elem = info;
    ret.left = -1;
    ret.right = -1;
    return ret;
}

int MDO::tree_min(int node) const {
    stack<TCheie> st;
    st.push(node);
    int ret = (1 << 30);
    while (!st.empty()) {
        int act = st.top();
        st.pop();
        if (ret == (1 << 30)) {
            ret = act;
            continue;
        }
        if (comp(elems[act].elem.first, elems[ret].elem.first)) {
            ret = act;
        }
        st.push(elems[act].left);
    }
    return ret;
}

void MDO::translate(int to, int from) {
    if (elems[to].parent == -1) {
        root = from;
    } else if (elems[elems[to].parent].left == to) {
        elems[elems[to].parent].left = from;
    } else {
        elems[elems[to].parent].right = from;
    }
    if (from != -1) {
        elems[from].parent = elems[to].parent;
    }
}

void MDO::del_node(int index) {
    int prm = firstFree;
    firstFree = index;
    elems[index].right = elems[index].parent = -1;
    elems[index].left = prm;
}

int MDO::succesor(int index) const {
    if (elems[index].right != -1) {
        return tree_min(elems[index].right);
    }
    int ex = elems[index].parent;
    while (ex != -1 && elems[ex].right == index) {
        index = ex;
        ex = elems[ex].parent;
    }
    return ex;
}

void MDO::redim() {
    int old_cp = capacity;
    capacity *= 2;
    auto *temp = new NodABC[capacity];
    for (int i = 0; i < old_cp; ++i) {
        temp[i] = elems[i];
    }
    firstFree = old_cp;
    for (int i = firstFree; i < capacity; ++i) {
        temp[i].parent = temp[i].right = -1;
        temp[i].left = i + 1;
    }
    temp[capacity - 1].left = -1;
    delete elems;
    elems = temp;
}

TCheie MDO::ceaMaiFreqCheie() const {
    struct {
        TCheie cheie;
        int frecventa;
    } vec_data[this->capacity + 1];
    int nr_chei = 0;

    for(int i = 0; i < this->capacity; i++) {
        auto elem = this->elems[i].elem;

        if(elem.first != NULL_TCHEIE or elem.second != NULL_TVALOARE) {
            int j;
            for (j = 1; j <= nr_chei; j++) {
                if (elem.first == vec_data[j].cheie)
                    vec_data[j].frecventa++;
            }
            if (j > nr_chei) {
                nr_chei++;
                vec_data[nr_chei].frecventa = 1;
                vec_data[nr_chei].cheie = elem.first;
            }
        }
    }

    // determin cheia cu frecventa maxima
    int max_frecv = vec_data[1].frecventa;
    int max_cheie = vec_data[1].cheie;
    for(int i = 2; i <= nr_chei; i++) {
        if(vec_data[i].frecventa > max_frecv) {
            max_frecv = vec_data[i].frecventa;
            max_cheie = vec_data[i].cheie;
        }
    }

    return max_cheie;
}



