#include <iostream>
#include <algorithm>

using namespace std;

// Hàm khởi tạo cây
struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

// --- CÁC KIỂU DUYỆT CÂY (NLR, LNR, LRN) ---
void NLR(Node* p) { if(p){ cout << p->data << " "; NLR(p->left); NLR(p->right); } }
void LNR(Node* p) { if(p){ LNR(p->left); cout << p->data << " "; LNR(p->right); } }
void LRN(Node* p) { if(p){ LRN(p->left); LRN(p->right); cout << p->data << " "; } }

// --- THUẬT TOÁN VUN ĐỐNG (Đẩy số lớn lên trên) ---
void Heapify(Node* p[], int n, int i) {
    int root = i, L = 2*i, R = 2*i + 1; // Công thức: con trái 2i, con phải 2i+1

    // Tìm xem trong 3 nút cha con, ai giữ số lớn nhất
    if (L <= n && p[L]->data > p[root]->data) root = L;
    if (R <= n && p[R]->data > p[root]->data) root = R;

    if (root != i) {
        swap(p[i]->data, p[root]->data); // Đổi số to lên trên
        Heapify(p, n, root);             // Kiểm tra tiếp các tầng dưới
    }
}

int main() {
    Node* p[11]; // quản lý 10 nút theo số thứ tự trong hình

    // 1. Khởi tạo 10 nút với giá trị y hệt đề bài
    p[1]=new Node(4);  p[2]=new Node(1);  p[3]=new Node(3);
    p[4]=new Node(2);  p[5]=new Node(16); p[6]=new Node(9);  p[7]=new Node(10);
    p[8]=new Node(14); p[9]=new Node(8);  p[10]=new Node(7);

    // 2. Nối các nút 
    p[1]->left = p[2]; p[1]->right = p[3]; // Nút 1 ra 2, 3
    p[2]->left = p[4]; p[2]->right = p[5]; // Nút 2 ra 4, 5
    p[3]->left = p[6]; p[3]->right = p[7]; // Nút 3 ra 6, 7
    p[4]->left = p[8]; p[4]->right = p[9]; // Nút 4 ra 8, 9
    p[5]->left = p[10];                    // Nút 5 ra 10

    // Câu 1: In 3 kiểu duyệt
    cout << "Duyet truoc: "; NLR(p[1]); 
    cout << "\nDuyet sau:   "; LRN(p[1]); 
    cout << "\nDuyet giua:  "; LNR(p[1]); 

    // Câu 2: Vun đống (Chạy ngược từ nút cha cuối cùng là nút số 5 lên gốc)
    for (int i = 5; i >= 1; i--) Heapify(p, 10, i);

    cout << "\n\nSau khi vun dong (Duyet truoc): "; 
    NLR(p[1]);

    return 0;
}