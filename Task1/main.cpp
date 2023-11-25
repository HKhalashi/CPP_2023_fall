// implement a Set<T> using a binary search tree .
// implement friend function GetIntersection
// Using recursion is prohibited , but using stack and queue is allowed
#include <iostream>
#include <stack>

template <typename T>
class Node {
public:
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class Set {
private:

    Node<T>* root;

    void insert(Node<T>*& root, T val) {
        if (!root) {
            root = new Node<T>(val);
            return;
        }

        std::stack<Node<T>*> s;
        s.push(root);

        while (!s.empty()) {
            Node<T>* current = s.top();
            s.pop();

            if (val < current->data) {
                if (!current->left) {
                    current->left = new Node<T>(val);
                } else {
                    s.push(current->left);
                }
            } else if (val > current->data) {
                if (!current->right) {
                    current->right = new Node<T>(val);
                } else {
                    s.push(current->right);
                }
            }
        }
    }

    bool contains(Node<T>* root, T val) {
        std::stack<Node<T>*> s;
        s.push(root);

        while (!s.empty()) {
            Node<T>* current = s.top();
            s.pop();

            if (current) {
                if (current->data == val) {
                    return true;
                }
                s.push(current->left);
                s.push(current->right);
            }
        }

        return false;
    }

public:
    Set() : root(nullptr) {}

    void insert(T val) {
        insert(root, val);
    }

    bool contains(T val) {
        return contains(root, val);
    }

    friend Set<T> GetIntersection(Set<T>& set1, Set<T>& set2) {
        Set<T> intersectionSet;

        std::stack<Node<T>*> s1, s2;
        Node<T>* current1 = set1.root;
        Node<T>* current2 = set2.root;

        while ((current1 || !s1.empty()) && (current2  || !s2.empty())) {
            while (current1) {
                s1.push(current1);
                current1 = current1->left;
            }
            while (current2) {
                s2.push(current2);
                current2 = current2->left;
            }

            if (s1.empty() || s2.empty()) break;

            current1 = s1.top();
            current2 = s2.top();

            if (current1->data == current2->data) {
                intersectionSet.insert(current1->data);
                s1.pop();
                s2.pop();
                current1 = current1->right;
                current2 = current2->right;
            } else if (current1->data < current2->data) {
                s1.pop();
                current1 = current1->right;
                current2 = nullptr;
            } else {
                s2.pop();
                current2 = current2->right;
                current1 = nullptr;
            }
        }

        return intersectionSet;
    }

};

int main() {
    Set<int> set1, set2;

    set1.insert(3);
    set1.insert(9);
    set1.insert(2);
    set1.insert(4);
    set1.insert(5);
    set1.insert(8);

    set2.insert(3);
    set2.insert(5);
    set2.insert(3);
    set2.insert(4);
    set2.insert(8);
    set2.insert(2);
    set2.insert(9);

    Set<int> intersection = GetIntersection(set1, set2);

    for (int i = 0; i < 10; ++i)
    {
        if (intersection.contains(i))
        {
            std::cout << i << " ";
        }
    }
    return 0;
}
