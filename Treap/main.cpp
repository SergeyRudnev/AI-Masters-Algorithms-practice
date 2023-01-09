#include <iostream>

using namespace std;

class TreapNode{
public:
    int key{};
    int prior{}; // приоритеты должны быть случайными для правильной глубины дерева
    TreapNode* right{};//right - переменная типа указатель на TreapNode, то есть переменная обозначающая адрес в памяти элемента типа TreapNode
    TreapNode* left{};
    TreapNode()= default;;
    TreapNode (int &k, int &p):
    key(k),
    prior(p),
    right(nullptr),
    left(nullptr)
    { }
};
class Treap{
public:
    TreapNode* root;
    Treap() = default;
    Treap(TreapNode* &tn){
        root = tn;
    }
    void split(TreapNode* T, int &key, TreapNode* &T1, TreapNode* &T2);
    void insert(TreapNode* &T, TreapNode* it);
    void merge(TreapNode* &T, TreapNode* T1, TreapNode* T2); // в T1 все ключи меньше, чем в T2
    void remove(TreapNode* &t, int &key);
    void print(TreapNode* &T);
    void extract(TreapNode *&T, int &key, int &res);
};



void Treap::split(TreapNode* T, int &key, TreapNode* &T1, TreapNode* &T2)
{
    if (!T)
    {
        T1 = nullptr;
        T2 = nullptr;
        return;
    }
    if (key > T->key)
    {
        split(T->right, key, T->right, T2); //T_2 = T_2_new, T_1.left = T.left, T_1.right = T_1_new, T_1_new,T_2_new=split(T.right)
        T1 = T;
    }
    else
    {
        split(T->left, key, T1, T->left);
        T2 = T;
    }
}

void Treap::merge(TreapNode* &T, TreapNode* T1, TreapNode* T2)
{
    if (!T1)
    {
        T = T2;
        return;
    }
    if (!T2)
    {
        T = T1;
        return;
    }
    if (T1->prior > T2->prior)
    {
        merge(T1->right, T1->right, T2);
        T = T1;
    }
    else
    {
        merge(T2->left, T1, T2->left);
        T = T2;
    }
}

void Treap::insert(TreapNode* &T, TreapNode* it)
{
    if (!T)
    {
        T = it;
        return;
    }
    TreapNode* t1;
    TreapNode* t2;
    split(T, it->key, t1, t2);
    merge(T, t1, it);
    merge(T, T, t2);
}

void Treap::remove(TreapNode* &T, int &key)
{
    if(T->key == key)
        merge(T, T->left, T->right);
    else
    {
        if(key < T->key)
            remove(T->left, key);
        if(key > T->key)
            remove(T->right, key);
    }
}

void Treap::extract(TreapNode* &T, int &key, int &res)
{
    if(T->key == key)
        res = T->prior;
    else
    {
        if(key < T->key)
            extract(T->left, key, res);
        if(key > T->key)
            extract(T->right, key, res);
    }
}

void Treap::print(TreapNode* &T)
{
    if(T)
    {
        cout<<T->key<<"."<<T->prior <<" ";
        if(T->left)
            cout << T->left->key<<"."<<T->left->prior<<" ";
        else
            cout << "None"<<" ";

        if(T->right)
            cout <<T->right->key<<"."<<T->right->prior<<" ";
        else
            cout << "None"<<" ";

        cout <<"\n";
        print(T->left);
        print(T->right);

    }
}

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(0);
    TreapNode* tn;
    Treap* treap;
    Treap* treap1;
    int n,k,p;
    cin >> n;
    treap = new Treap;
    for(int i =0;i<n;++i)
    {
        cin >> k >> p;
        tn = new TreapNode(k,p);
        treap->insert(treap->root,tn);
    }

    //treap->insert(treap->root,tn);

    /*cout << treap->root->key<<" "<<treap->root->prior<<"\n";
    cout << treap->root->right->key<<" "<<treap->root->right->prior<<"\n";
    cout << treap->root->left->key<<" "<<treap->root->left->prior<<"\n";
    cout << treap->root->left->right->key<<" "<<treap->root->left->right->prior<<"\n";
    //cout <<treap->root->right;
     */
    /*
    k = 7;
    p = 10;
    tn = new TreapNode(k,p);
    treap1 = new Treap;
    treap1->insert(treap1->root, tn);
    k = 8;
    p = 5;
    tn = new TreapNode(k,p);
    treap1->insert(treap1->root, tn);
    //treap1->print(treap1->root);
     */
    k = 1;
    treap->remove(treap->root, k);
    //treap->merge(treap->root, treap->root, treap1->root);
    treap->print(treap->root);
    k = 2;
    int y;
    treap->extract(treap->root,k, y);
    cout << y;
    return 0;
}
