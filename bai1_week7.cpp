#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    string title;
    int pages;
    vector<Node*> children;

    Node(string t, int p) : title(t), pages(p) {}
};

class Book {
    Node* root;
    // Hàm giải phóng bộ nhớ 
    void clearMemory(Node* node) {
        if (node == NULL) return;
        for (Node* child : node->children) {
            clearMemory(child);
        }
        delete node;
    }

    int calculateTotalPages(Node* current) {
        if (current == NULL) return 0;
        int total = current->pages;
        for (Node* child : current->children) {
            total += calculateTotalPages(child);
        }
        return total;
    }

    bool findAndRemove(Node* parent, string target) {
        for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
            if ((*it)->title == target) {
                // Giải phóng bộ nhớ của toàn bộ nhánh bị xóa
                clearMemory(*it); 
                parent->children.erase(it);
                return true;
            }
            if (findAndRemove(*it, target)) return true;
        }
        return false;
    }

public:
    Book(string bookTitle) {
        root = new Node(bookTitle, 0);
    }

    // dọn dẹp bộ nhớ khi chương trình kết thúc
    ~Book() {
        clearMemory(root);
    }

    Node* getRoot() { return root; }

    int countChapters() { return root->children.size(); }

    void findLongestChapter() {
        if (root->children.empty()) return;
        Node* longest = NULL;
        int maxPages = -1;
        for (Node* chapter : root->children) {
            int currentTotal = calculateTotalPages(chapter);
            if (currentTotal > maxPages) {
                maxPages = currentTotal;
                longest = chapter;
            }
        }
        if (longest) 
            cout << "Chuong dai nhat: " << longest->title << " (" << maxPages << " trang)" << endl;
    }

    void deleteSection(string title) {
        if (findAndRemove(root, title)) cout << "Da xoa muc: " << title << endl;
        else cout << "Khong tim thay muc: " << title << endl;
    }

    void printChapterOutline(string chapterTitle) {
        Node* target = NULL;
        for (Node* chapter : root->children) {
            if (chapter->title == chapterTitle) { target = chapter; break; }
        }
        if (!target) return;

        cout << "--- Muc luc: " << chapterTitle << " ---" << endl;
        // in cả mục con của mục
        for (Node* section : target->children) {
            cout << "+ " << section->title << " (" << calculateTotalPages(section) << " trang)" << endl;
            for (Node* sub : section->children) {
                cout << "  - " << sub->title << endl;
            }
        }
    }
};

int main() {
    // Khoi tao cuon sach
    Book myBook("Giao trinh Cau truc du lieu");

    // Tao du lieu mau
    // Chuong 1
    Node* c1 = new Node("Chuong I", 5); 
    c1->children.push_back(new Node("Section 1.1", 10));
    c1->children.push_back(new Node("Section 1.2", 15));

    // Chuong 2
    Node* c2 = new Node("Chuong II", 10);
    Node* s21 = new Node("Section 2.1", 20);
    s21->children.push_back(new Node("Subsection 2.1.1", 30)); // Muc rat dai
    c2->children.push_back(s21);
    c2->children.push_back(new Node("Section 2.2", 5));

    // Them cac chuong vao sach
    myBook.getRoot()->children.push_back(c1);
    myBook.getRoot()->children.push_back(c2);

    cout << "1. So chuong cua sach: " << myBook.countChapters() << endl;

    cout << "2. ";
    myBook.findLongestChapter();

    cout << "3. ";
    myBook.deleteSection("Section 1.1"); // Xoa thu mot muc

    cout << "4. In de muc chuong sau khi xoa:" << endl;
    myBook.printChapterOutline("Chuong I");
    
    cout << "\nIn de muc chuong co Section dai:" << endl;
    myBook.printChapterOutline("Chuong II");

    return 0;
}