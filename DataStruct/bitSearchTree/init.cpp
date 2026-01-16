#include <iostream>

using namespace std;

struct Node
{
    int value;
    Node *left;
    Node *right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree
{
private:
    Node *root;
    // 插入函数
    Node *insert(Node *node, int value);
    // 删除函数
    Node *remove(Node *node, int value);
    // 查找
    bool find(Node *node, int value) const;
    // 找最小
    Node *findMin(Node *node) const;
    // 销毁树
    void destroyTree(Node *node);

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree();
    void insertNode(int value)
    {
        root = insert(root, value);
    }
    void removeNode(int value)
    {
        root = remove(root, value);
    }

    bool findNode(int value)
    {
        return find(root, value);
    }
    
    void inorderTraversal() const
    {
        inorderHelper(root);
        cout << endl;
    }

private:
    void inorderHelper(Node *node) const;
};

BinarySearchTree::~BinarySearchTree()
{
    destroyTree(root);
}

void BinarySearchTree::destroyTree(Node *node)
{
    if (node != nullptr)
    {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

Node *BinarySearchTree::insert(Node *node, int value)
{   
    // 当节点为空时插入（默认是根节点）
    if (node == nullptr)
    {
        return new Node(value);
    }

    if (value < node->value)
    {
        node->left = insert(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = insert(node->right, value);
    }
    

    return node;
}

// 找最小值，肯定在左边树木上找
Node *BinarySearchTree::findMin(Node *node) const
{
    while (node && node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}
// 删除元素指定在删除的位置上删除
Node *BinarySearchTree::remove(Node *node, int value)
{
    if (node == nullptr)
    {
        return node;
    }

    if (value < node->value)
    {
        node->left = remove(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = remove(node->right, value);
    }
    else
    {
        // 相等的时候
        
        // 第一个这个这个点没有子节点
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            return nullptr;
        }
    //    有一个子节点只需要把上一个删除就好了
        else if (node->left == nullptr)
        {
            Node *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            Node *temp = node->left;
            delete node;
            return temp;
        }
        // 有两个子节点这个就比较麻烦了
        // 删除父节点然后把右边最小的作为父节点 
        else
        {
            // 找到右边最小的
            Node *successor = findMin(node->right);
            //把节点值换成最小值
            node->value = successor->value;
            // 删掉最小值节点（右边的） 
            node->right = remove(node->right, successor->value);
        }
    }

    return node;
}
// 查找
bool BinarySearchTree::find(Node *node, int value) const
{
    if (node == nullptr)
    {
        return false;
    }

    if (value == node->value)
    {
        return true;
    }
    else if (value < node->value)
    {
        return find(node->left, value);
    }
    else
    {
        return find(node->right, value);
    }
}


// 中序遍历
void BinarySearchTree::inorderHelper(Node *node) const
{
    if (node != nullptr)
    {
        inorderHelper(node->left);
        cout << node->value << " ";
        inorderHelper(node->right);
    }
}

// 使用一下
int main()
{
    BinarySearchTree bst;
    
    bst.insertNode(50);
    bst.insertNode(30);
    bst.insertNode(70);
    bst.insertNode(20);
    bst.insertNode(40);
    bst.insertNode(60);
    bst.insertNode(80);
    
    cout << "Inorder traversal: ";
    bst.inorderTraversal();
    
    cout << "Finding 40: " << (bst.findNode(40) ? "Found" : "Not Found") << endl;
    cout << "Finding 90: " << (bst.findNode(90) ? "Found" : "Not Found") << endl;
    
    cout << "Removing 20..." << endl;
    bst.removeNode(20);
    cout << "Inorder traversal after removing 20: ";
    bst.inorderTraversal();
    
    cout << "Removing 30..." << endl;
    bst.removeNode(30);
    cout << "Inorder traversal after removing 30: ";
    bst.inorderTraversal();
    
    cout << "Removing 50..." << endl;
    bst.removeNode(50);
    cout << "Inorder traversal after removing 50: ";
    bst.inorderTraversal();
    
    return 0;
}
