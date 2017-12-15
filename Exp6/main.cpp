
#include<stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;

typedef struct Node
{
    char data;
    struct Node *LChild;
    struct Node *RChild;
}BiTNode, *BiTree;
typedef BiTree StackElementType;
typedef BiTree QueueElementType;

//构造二叉链表
void CreateBiTree(BiTree *bt)
{
    char ch=getchar();
    if(ch=='.') *bt=NULL;
    else if(ch=='\n') return;
    else{
        *bt=(BiTree)malloc(sizeof(Node));
        (*bt)->data=ch;
        CreateBiTree(&((*bt)->LChild));
        CreateBiTree(&((*bt)->RChild));
    }

}

void Visit(BiTree root)
{
    if(root!=NULL)
        printf("%c",root->data);
}

/*先序遍历二叉树, root为指向二叉树根结点的指针*/
void  PreOrder(BiTree root)
{
    if(root!=NULL){
        Visit(root);
        PreOrder(root->LChild);
        PreOrder(root->RChild);
    }
}

/* 后序遍历二叉树，root为指向二叉树(或某一子树)根结点的指针*/
void  PostOrder(BiTree root)
{
    if(root!=NULL){
        PreOrder(root->LChild);
        PreOrder(root->RChild);
        Visit(root);
    }
}
void  InOrder(BiTree root) /* 中序遍历二叉树的非递归算法 */
{
    stack<StackElementType> StackType;
    StackElementType p;
    p=root;
    while(p!=NULL||!StackType.empty()){
        if(p!= NULL){
            StackType.push(p);
            p=p->LChild;
        } else{
            p=StackType.top();
            StackType.pop();
            Visit(p);
            p=p->RChild;
        }
    }
}

void PrintTree(BiTree bt,int nLayer)  /* 按竖向树状打印的二叉树 */
{
    if(bt==NULL) return;
    PrintTree(bt->RChild,nLayer+1);
    for(int i=0;i<nLayer;i++) {
        printf("  ");
    }
    printf("%c\n",bt->data);
    PrintTree(bt->LChild,nLayer+1);
}

void  LayerOrder(BiTree bt) /* 层序遍历二叉树 */
{
    queue<QueueElementType> QueueType;
    if(bt==NULL) return;
    QueueType.push(bt);
    QueueElementType p;
    while(QueueType.empty()==0){
        p=QueueType.front();
        Visit(p);
        QueueType.pop();
        if(p->LChild!=NULL) QueueType.push(p->LChild);
        if(p->RChild!=NULL) QueueType.push(p->RChild);
    }
}

int main()
{
    BiTree T;
    printf("按扩展先序遍历序列建立二叉树，请输入序列:\n");
    CreateBiTree(&T);
    printf("先序遍历输出序列为:\n");
    PreOrder(T);
    printf("\n中序遍历输出序列为:\n");
    InOrder(T);
    printf("\n后序遍历输出序列为:\n");
    PostOrder(T);
    printf("\n层序遍历输出序列为:\n");
    LayerOrder(T);
    printf("\n竖向打印二叉树:\n");
    PrintTree(T,1);
    return 0;
}
