#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Cấu trúc một nút trong cây mục lục 
struct Node {
    int index;          // Thuộc tính 1: Chỉ số dạng số
    string title;       // Thuộc tính 2: Tên mục dạng chuỗi
    Node *left, *right;

    Node(int idx, string t) : index(idx), title(t), left(NULL), right(NULL) {}
};

class BookManager {
public:
    // kiểm tra hai cây có giống hệt nhau không
    bool isCopy(Node* root1, Node* root2) {
        // Cả hai cùng rỗng -> Giống nhau
        if (root1 == NULL && root2 == NULL) return true;

        // Một bên rỗng, một bên có nút hoặc khác giá trị -> Không phải bản copy
        if (root1 == NULL || root2 == NULL) return false;
        if (root1->index != root2->index || root1->title != root2->title) return false;

        // kiểm tra song song các nhánh con trái và phải
        return isCopy(root1->left, root2->left) && isCopy(root1->right, root2->right);
    }

    // Hàm giải phóng bộ nhớ
    void clear(Node* t) {
        if (t == NULL) return;
        clear(t->left);
        clear(t->right);
        delete t;
    }
};

int main() {
    BookManager manager;
    
    // Tạo Cuốn sách 1
    Node* book1 = new Node(1, "Chuong 1");
    book1->left = new Node(11, "Muc 1.1");
    book1->right = new Node(12, "Muc 1.2");

    // Tạo Cuốn sách 2 
    Node* book2 = new Node(1, "Chuong 1");
    book2->left = new Node(11, "Muc 1.1");
    book2->right = new Node(12, "Muc 1.2");

    cout << "Kiem tra ban copy..." << endl;
    if (manager.isCopy(book1, book2)) {
        cout << "Ket luan: Hai cuon sach la ban copy cua nhau" << endl;
    } else {
        cout << "Ket luan: Hai cuon sach khac nhau" << endl;
    }

    // Giải phóng bộ nhớ
    manager.clear(book1);
    manager.clear(book2);

    return 0;
}