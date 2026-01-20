#include<iostream>
#include<vector>
#include<queue>


/*
题目：
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7

答案：
4 1 6 3 5 7 2
*/

using namespace std;

struct Node
{
    int val;
    Node* left;
    Node* right;
    Node(int v): val(v),left(nullptr),right(nullptr){}
};



Node* build(vector<int> post,vector<int> inorder,int lp,int rp,int li,int ri){
    if(lp > rp) return NULL;
    // 储存根节点变量值 因为后序遍历最后一个是树的根节点
    int roolValue = post[rp];
    Node* root = new Node(roolValue);

    // 找到中序遍历表中的根节点把树分为左右子树
    int k = li;
    // 经过循环之后就会把下标作为中心节点的下标
    while(inorder[k] != roolValue) k++; 

    // 先计算左边子节点的树木
    int leftSize = k - li;

    // 先遍历左子树 [左边，左边+SIZE-1]
    root->left = build(post,inorder,lp,lp+leftSize-1,li,k-1);
    // 再遍历右子树 [右边，右边-1]
    root->right = build(post,inorder,lp+leftSize,rp-1,k+1,ri);

    return root;
}   

int main() {
        int N;
        cin >> N;
        vector<int> post(N), in(N);
        for (int i = 0; i < N; i++) cin >> post[i];
        for (int i = 0; i < N; i++) cin >> in[i];


        // 先建立一棵树
        Node* root = build(post, in, 0, N - 1, 0, N - 1);

        queue<Node*> q;
        q.push(root);
        bool first = true;

        while (!q.empty()) {
                    Node* t = q.front();
                    q.pop();
                    if (!first) cout << " ";
                    first = false;
                    cout << t->val;
                    if (t->left) q.push(t->left);
                    if (t->right) q.push(t->right);
        }

        return 0;
}

