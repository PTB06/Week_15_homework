#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

// Hàm in cây theo thứ tự tiền tố (NLR) để kiểm tra
void printTree(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    printTree(root->left);
    printTree(root->right);
}

// sSo sánh 2 cây
bool isIdentical(Node* root1, Node* root2) {
    // Cả hai cùng rỗng -> Giống nhau
    if (root1 == NULL && root2 == NULL) return true;

    // Một trong hai rỗng hoặc giá trị khác nhau -> Khác nhau
    if (root1 == NULL || root2 == NULL) return false;
    if (root1->data != root2->data) return false;

    // kiểm tra song song các nhánh con
    return isIdentical(root1->left, root2->left) && 
           isIdentical(root1->right, root2->right);
}

int main() {
    
    // Cây thứ nhất
    Node* tree1 = new Node(10);
    tree1->left = new Node(20);
    tree1->right = new Node(30);
    tree1->left->left = new Node(40);

    // Cây thứ hai 
    Node* tree2 = new Node(10);
    tree2->left = new Node(20);
    tree2->right = new Node(30);
    tree2->left->left = new Node(40);

    cout << "Cay 1 (NLR): "; 
    printTree(tree1); 
    cout << endl;

    cout << "Cay 2 (NLR): "; 
    printTree(tree2); 
    cout << endl;

    if (isIdentical(tree1, tree2)) {
        cout << "=> Ket qua: Hai cay giong het nhau." << endl;
    } else {
        cout << "=> Ket qua: Hai cay khac nhau." << endl;
    }

    return 0;
}