//
// Created by 69199 on 2019/4/6.
//

#include <iostream>
#include <malloc.h>
#include <stdlib.h>

typedef struct TreeNode *BinTree;
typedef TreeNode Position;
struct TreeNode{
    Bintree Left;
    Bintree Right;
    int DATA;
    int flag;

//    BinTree(int Value)
//    {
//        DATA = Value;
//        Left = nullptr;
//        Right = nullptr;
//    }
};

/**
 * 查找（递归）
 *
 * @param {int} x
 * @param {BinTree} BST
 * @return {BinTree}
 */
 Position Find(int x, BinTree BST)
{
     if(!BST) return NULL;

     if(BST->DATA < x){
         return Find(x, BST->Right);
     }else if (BST->DATA > x){
         return Find(x, BST->Left);
     }else{
         return *BST;
     }
}
/*********  此种方法效率取决于树的高度，不稳定   ************/

/**
 * 循环迭代查找
 *
 * @param {int}
 * @param {TreeNode}
 *
 * @return {TreeNode}
 */
 Position IterFind(int x, BinTree BST)
{
     while(BST)
     {
         if(BST->DATA < x){
             BST = BST->Right;
         }else if(BST->DATA > x){
             BST = BST->Left;
         }else
             return *BST;
     }
     return NULL;
}

/**
 * 比较二叉搜索树是否完全相同（插入序列不同）
 *
 * @param {int} 树的节点数
 * @param {int} 需要比较的额外组数
 *
 * @return
 */


/**
 * NewNode
 *
 * @param {int}
 * @return {BinTree}
 */
 BinTree NewNode(int V)
{
     BinTree T = (BinTree)malloc(sizeof(struct TreeNode));
     T->DATA = V;
     T->Left = T->Right = NULL;
     T->flag = 0;
    return  T;
}

/**
 * Insert
 *
 * @param {BinTree}
 * @param {int{
 * @return{BinTree}
 */
 BinTree Insert(BinTree T,int V)
{
     if(!T) T = NewNode(V);
     else{
         if(T->DATA < V){
             T->Right = Insert(T->Right, V);
         }else if(T->DATA > V){
             T->Left = Insert(T->Left, V);
         }
     }
    return T;
}

/**
 * 建树
 *
 * @param ｛N｝ nodes number
 * @return
 */
 BinTree MakeTree(N)
{
     BinTree T;
     int i,V;

     cin>>V;
     T = NewNode(V);
     for(i=1;i<N;i++){
         cin>>V;
         T = Insert(T,V);
     }
     return T;
}

/**
 * Judge
 *
 * @param {BinTree}
 * @param {int}
 * @return {bool}
 */
 bool Judge(BinTree T, int N)
{
     int i,V;
     for(i=0;i<N;i++){
         cin>>V;
         T->flag = 1;
         while(T->flag == 1){
             if(T->DATA > V){
                 T->flag = 1;
                 T = T->Left;
             }else if(T->DATA < V){
                 T->flag = 1;
                 T = T->Right;
             }else{
                 return true;
             }
         }
         return false;
     }
}


int main()
{
    int N, L, i;
    TreeNode T;

    cin>>N;

    while(N)
    {
        cin>>L;
        T = MakeTree(N);
        for(i = 0;i < L;i++){
            if(Judge(T,N))
                cout<<"Yes\n";
            else
                cout<<"No\n";
            ResetTree(T);
        }
        FreeTree(T);
        cin>>N;
    }

    return 0;
}
