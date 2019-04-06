//
// Created by 69199 on 2019/4/6.
//

#include <iostream>
#include <malloc.h>
#include <stdlib.h>

typedef struct TreeNode *BinTree;
typedef TreeNode Position;
struct TreeNode{
    BinTree Left;
    BinTree Right;
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
 * 1.1 查找（递归）
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
 * 1.2 循环迭代查找
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
 * 2.1 NewNode
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
 * 2.2 Insert
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
 * 2.3 建树
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
 * 2.4 check
 *
 * @param {BinTree}
 * @param {int}
 */
 int check(BinTree T, int V)
{
     if(T->flag){
         if(T->DATA > V)
             return check(T->Left, V);
         else if(T->DATA < V)
             return check(T->Right, V);
         else
             return 0;
     }else{
         if(T->DATA == V)
             return 1;
         else
             return 0;
     }
}

/**
 * 2.5 Judge
 *
 * @param {BinTree}
 * @param {int}
 * @return {int}
 */
 int Judge(BinTree T, int N)
{
     int i,V,flag=0;
     cin>>V;
     if(V != T->DATA) flag = 1;
     else   T->flag = 1;
     for(i=1;i<N; i++) {
         cin >> V;
         if (!flag && !check(T, V)) flag = 1;
     }
    if(flag) return 0;
    return 1;
}

/**
 * 2.6 Reset
 *
 * @param {BinTree}
 * @return
 */
 void ResetTree(BinTree T)
{
     if(T->Left) ResetTree(T->Left);
     if(T->Right) ResetTree(T->Right);
     T->flag = 0;
}

/**
 * 2.7 free
 *
 * @param {BinTree}
 * @return
 */
 void FreeTree(BinTree T)
{
     if(T->Left) FreeTree(T->Left);
     if(T->Right) FreeTree(T->Right);
     free(T);
}

int main()
{
    int N, L, i;
    BinTree T;

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
