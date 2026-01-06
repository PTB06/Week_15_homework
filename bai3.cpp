#include <iostream>

using namespace std;

struct Node
{
    int value;    // gia tri nut
    Node* left;   // Con tro toi nut con trai
    Node* right;  // Con tro toi nut con phai

    // Ham tao
    Node(int v, Node* l = NULL, Node* r = NULL)
    {
        value = v;
        left = l;
        right = r;
    }
};

// Lop cay nhi phan tim kiem
class BSTree
{
private:
    Node *root;

public:
    // Ham tao (ban dau cay rong)
    BSTree()
    {
        root = NULL;
    }

    // Ham huy (xoa het cac nut tren cay)
    ~BSTree()
    {
        makeEmpty(root);
    }

    // Kiem tra cay co rong hay khong
    bool isEmpty()
    {
        return root == NULL;
    }

    // Xoa het cac nut tren cay
    void makeEmpty()
    {
        makeEmpty(root);
    }

    // Chen mot nut val1 moi vao cay
    void insert(int val1)
    {
        insert(val1, root);
    }

    // Tim nut val2 (tra ve dia chi nut de dung cho ham duyet trong main)
    Node* search(int val2)
    {
        return search(val2, root);
    }

    // Xoa rong cay (viet theo kieu de quy - Duyet sau)
    void makeEmpty(Node*& t)
    {
        if (t != NULL)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = NULL; // Tranh con tro ma (dangling pointer)
        }
    }

    // Chen mot nut val1 moi vao cay (viet theo kieu de quy)
    void insert(int val1, Node*& t)
    {
        if (t == NULL)
        {
            t = new Node(val1);
        }
        else if (val1 < t->value)
        {
            insert(val1, t->left);
        }
        else if (val1 > t->value)
        {
            insert(val1, t->right);
        }
        // Neu val1 == t->value thi khong lam gi (BST thuong khong chua gia tri trung)
    }

    // Tim kiem nut co gia tri cho truoc (viet theo kieu de quy)
    Node* search(int val2, Node* t)
    {
        if (t == NULL) return NULL;
        if (val2 < t->value) return search(val2, t->left);
        if (val2 > t->value) return search(val2, t->right);
        return t; // Tim thay
    }
};

// --- CAC HAM DUYET CAY ---

// Duyet thu tu truoc (NLR)
void PREORDER_travl(Node* t)
{
    if (t != NULL)
    {
        cout << t->value << " ";
        PREORDER_travl(t->left);
        PREORDER_travl(t->right);
    }
}

// Duyet thu tu giua (LNR) - Se ra day so tang dan
void INORDER_travl(Node* t)
{
    if (t != NULL)
    {
        INORDER_travl(t->left);
        cout << t->value << " ";
        INORDER_travl(t->right);
    }
}

// Duyet thu tu sau (LRN)
void POSTORDER_travl(Node* t)
{
    if (t != NULL)
    {
        POSTORDER_travl(t->left);
        POSTORDER_travl(t->right);
        cout << t->value << " ";
    }
}

int main()
{
    BSTree bst;

    // Chen cac node co gia tri
    bst.insert(5);
    bst.insert(6);
    bst.insert(3);
    bst.insert(8);
    bst.insert(7);
    bst.insert(4);
    bst.insert(2);

    // Lay nut goc (gia tri 5) de bat dau duyet
    Node *root = bst.search(5);

    cout << "Duyet cay thu tu truoc (Pre-order):" << endl;
    PREORDER_travl(root);
    cout << endl;

    cout << "Duyet cay thu tu giua (In-order - Day tang dan):" << endl;
    INORDER_travl(root);
    cout << endl;

    cout << "Duyet cay thu tu sau (Post-order):" << endl;
    POSTORDER_travl(root);
    cout << endl << endl;

    // Tim hai node co gia tri 4 va 9
    Node* n1 = bst.search(4);
    Node* n2 = bst.search(9);

    // In ket qua tim kiem
    if (n1 != NULL)
        cout << "Node co gia tri = 4 ton tai, gia tri doc duoc: " << n1->value << endl;
    
    if (n2 == NULL)
        cout << "Khong tim thay node co gia tri = 9" << endl;

    // Lam rong cay
    bst.makeEmpty();
    if (bst.isEmpty())
        cout << "Cay da bi xoa rong hoan toan" << endl;

    return 0;
}