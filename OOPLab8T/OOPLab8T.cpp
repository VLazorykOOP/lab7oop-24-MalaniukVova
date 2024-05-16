#include <iostream>
using namespace std;

template<typename T>
int search(const T* array, int size, const T& key) {
    for (int i = size - 1; i >= 0; --i) {
        if (array[i] == key) {
            return i;
        }
    }
    return -1;
}

void task1() {
    const char* Array[] = { "apple", "banana", "cherry", "date", "fig", "grape" };

    const char* key = "date";
    int index = search(Array, 6, key);

    if (index != -1) {
        cout << "Element '" << key << "' in " << index << " place" << endl;
    }
    else {
        cout << "Element '" << key << "not find" << endl;
    }
}
//task2
template<typename T>
void swapElements(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
int divideArray(T* array, int low, int high) {
    T pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (array[j] < pivot) {
            i++;
            swapElements(array[i], array[j]);
        }
    }
    swapElements(array[i + 1], array[high]);
    return (i + 1);
}

template<typename T>
void quickSortArray(T* array, int low, int high) {
    if (low < high) {
        int pivotIndex = divideArray(array, low, high);
        quickSortArray(array, low, pivotIndex - 1);
        quickSortArray(array, pivotIndex + 1, high);
    }
}

void sortArray(const char** array, int size) {
    quickSortArray(array, 0, size - 1);
}

void displayArray(const char** array, int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

void task2() {
    const char* charArray[] = { "date", "apple", "cherry", "banana", "fog", "grape" };
    int size = 6;

    cout << "Before sorting:" << endl;
    displayArray(charArray, size);

    sortArray(charArray, size);

    cout << "After sorting:" << endl;
    displayArray(charArray, size);
}
//task3
template<typename T>
class Array {
protected:
    T* data;
    int m_size;

public:
    Array() {
        m_size = 1;
        data = new T[m_size];
        data[0] = 0;
    }

    Array(int size, T numb) {
        m_size = size;
        data = new T[m_size];
        for (int i = 0; i < m_size; i++) {
            data[i] = numb;
        }
    }

    Array(const Array& other) {
        m_size = other.m_size;
        data = new T[m_size];
        for (int i = 0; i < m_size; ++i) {
            data[i] = other.data[i];
        }
    }

    ~Array() {
        if (data != nullptr) delete[] data;
    }

    T& operator[](int index) {
        return data[index];
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            m_size = other.m_size;
            data = new T[m_size];
            for (int i = 0; i < m_size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Array operator+(const Array& other) {
        Array result(m_size, 0);
        for (int i = 0; i < m_size; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    Array& operator+=(const Array& other) {
        for (int i = 0; i < m_size; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    Array operator-(const Array& other) {
        Array result(m_size, 0);
        for (int i = 0; i < m_size; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    Array& operator-=(const Array& other) {
        for (int i = 0; i < m_size; ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    int size() const {
        return m_size;
    }
};

void task3() {
    Array<int> arr1(3, 1);
    Array<int> arr2 = arr1;
    Array<int> arr3 = arr1 + arr2;

    cout << "arr3 = ";
    for (int i = 0; i < arr3.size(); ++i) {
        cout << arr3[i] << " ";
    }
    cout << endl;
}

template<typename T>
class BinaryTreeNode {
public:
    T data;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;

    BinaryTreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
class BinaryTree {
public:
    BinaryTreeNode<T>* root;

    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        clear(root);
    }

    void clear(BinaryTreeNode<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

private:
    BinaryTreeNode<T>* insert(BinaryTreeNode<T>* node, const T& value) {
        if (!node) {
            return new BinaryTreeNode<T>(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else {
            node->right = insert(node->right, value);
        }
        return node;
    }
};

template<typename T>
class Stack {
    struct Node {
        T data;
        Node* next;
        Node(T d, Node* n) : data(d), next(n) {}
    };
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(T data) {
        top = new Node(data, top);
    }

    T pop() {
        if (isEmpty()) {
            cerr << "Stack underflow" << endl;
            return T();
        }
        Node* temp = top;
        T data = temp->data;
        top = top->next;
        delete temp;
        return data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }
};

template<typename T>
class BinaryTreeIterator {
    Stack<BinaryTreeNode<T>*> stack;

public:
    BinaryTreeIterator(BinaryTreeNode<T>* root) {
        pushLeft(root);
    }

    bool hasNext() {
        return !stack.isEmpty();
    }

    T next() {
        if (stack.isEmpty()) {
            cerr << "No more elements" << endl;
            return T();
        }
        BinaryTreeNode<T>* node = stack.pop();
        T result = node->data;
        if (node->right) {
            pushLeft(node->right);
        }
        return result;
    }

private:
    void pushLeft(BinaryTreeNode<T>* node) {
        while (node) {
            stack.push(node);
            node = node->left;
        }
    }
};

void task4() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(90);
    tree.insert(6);
    tree.insert(8);

    BinaryTreeIterator<int> it(tree.root);
    cout << "In-order traversal of binary tree: ";
    while (it.hasNext()) {
        cout << it.next() << " ";
    }
    cout << endl;
}


int main()
{
    int choice;
    cout << "Choose task" << endl;
    cout << "1.Task 1 (Search)" << endl;
    cout << "2.Task 2 (Sorting)" << endl;
    cout << "3.Task 3(Array)" << endl;
    cout << "4.Task 4(Tree)" << endl;
    cout << "5.Exit" << endl;

    cin >> choice;

    switch (choice) {
    case 1: task1(); break;
    case 2: task2(); break;
    case 3: task3(); break;
    case 4: task4(); break;
    case 5: return 0;
    default: cout << "Error" << endl;
    }
}