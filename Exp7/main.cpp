#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

#define MAX_VERTEX_NUM 20    //最大顶点个数
#define INFINITY INT_MAX  //最大值∞

typedef char VertexType;   //顶点向量类型
typedef int VRType;
typedef int InfoType;
typedef int QElemType;

//图的数组存储表示
typedef struct{
    VertexType vexs[MAX_VERTEX_NUM];    //顶点向量
    VRType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//邻接矩阵,于无权图1、0表示两个顶点是否相邻，对于有权图为权值
    int vexnum,arcnum; //图的顶点数和弧数
}MGraph;

bool visited[MAX_VERTEX_NUM];  //标记顶点是否被访问，访问为true,否则为false

//查找顶点在顶点向量中的位置
int locateVertex(MGraph umg, VertexType v)
{
    int i;
    for(i=0;i<umg.vexnum;i++)
    {
        if(v == umg.vexs[i])
            return i;
    }
    return -1;
}

void createMGraph(MGraph *mg){
    int i,j,v,w;
    char v1,v2;
    char ch[5];
    fstream infile;
//    char filename[20];
//    printf("请输入文件名称");
//    cin>>filename;
//    infile.open(filename,ios::in);
    infile.open("2.txt",ios::in);
    infile>>ch;
    (*mg).vexnum=atoi(ch);//获得顶点数
    infile>>ch;
    (*mg).arcnum=atoi(ch);//获得边数
    for(v=0;v<(*mg).vexnum;v++)
        visited[v] = false;
    for(v=0;v<(*mg).vexnum;v++){
        infile>>ch;
        (*mg).vexs[v]=ch[0];
    }

    //初始化邻接矩阵
    for(i=0;i<(*mg).vexnum;i++)
        for(j=0;j<(*mg).vexnum;j++)
            (*mg).arcs[i][j] = INFINITY;//最值，表示不可达。有n个顶点，就有n^2个储存空间

    for(v=0;v<(*mg).arcnum;v++){
        infile>>ch;
        v1=ch[0];
        infile>>ch;
        v2=ch[0];
        i=locateVertex(*mg,v1);
        j=locateVertex(*mg,v2);
        infile>>ch;
        w=atoi(ch);
        (*mg).arcs[i][j]=w;
    }

    infile.close();
}

//打印图的邻接矩阵
void print(MGraph G)
{
    int i,j;
    printf("图的邻接矩阵:\n");
    for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
            if(G.arcs[i][j]!=INFINITY)
                printf("%2d  ",G.arcs[i][j]);
            else
                printf("∞  ");
        }//∞
        printf("\n");
    }
    printf("\n");
}

int FirstAdjVex(MGraph G,int v)
{   //获取与顶点v相邻的第一个顶点下标
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.arcs[v][i]!=0 && G.arcs[v][i]!=INFINITY && !visited[i])
            return i;
    }
    return -1;
}

int NextAdjVex(MGraph G,int v,int w)
{   //得到v的下一个未被访问的相邻顶点下标
    int i;
    for(i=w;i<G.vexnum;i++)
    {
        if(G.arcs[v][i]!=0 && G.arcs[v][i]!=INFINITY && !visited[i])
            return i;
    }
    return -1;
}

void DFS(MGraph G,int v)
{
    //请在此处填写代码实现深度优先遍历v顶点所在的连通分量
    printf("%c",G.vexs[v]);
    visited[v]=true;
    for(int vi=0;vi<G.vexnum;vi++){
        if(!visited[vi])
            DFS(G,vi);
    }
}

void DFSTraverse(MGraph G)
{
    printf("深度优先遍历序列：");
    //请在此处填写代码实现深度优先遍历图G
    for(int i=0;i<G.vexnum;i++)
        visited[i] = false;
    for(int p=0;p<G.vexnum;p++){
        if(!visited[p])
            DFS(G,p);
    }
    printf("\n");
}

void BFSTraverse(MGraph G)
{
    printf("广度优先遍历序列：");
    int i,v,w;
    for(i=0;i<G.vexnum;i++)//初始化访问标记
        visited[i] = false;

    queue<int> BFSQueue;//初始化辅助队列
    for(i=0;i<G.vexnum;i++)
    {
        if(!visited[i])             //i未被访问
        {
            visited[i] = true;
            printf("%c",G.vexs[i]);
            BFSQueue.push(i);
            while(!BFSQueue.empty())
            {
                v=BFSQueue.front();//队头元素出队
                BFSQueue.pop();
                for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
                    if(!visited[w])            //w为v的尚未访问的邻接顶点
                    {
                        visited[w] = true;
                        printf("%c",G.vexs[w]);
                        BFSQueue.push(w);
                    }

            }
        }
    }
    printf("\n");
}

void dijkstra(MGraph G, int vs )//求图G中从vs顶点到达其余各顶点的最短路径
{
    int *prev=(int *)malloc(sizeof(int)*G.arcnum);
    int *dist=(int *)malloc(sizeof(int)*G.arcnum);
    int *flag=(int *)malloc(sizeof(int)*G.arcnum);
    // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。

    int i,j,k;
    int min;
    int tmp;

    // 初始化
    for (i = 0; i < G.vexnum; i++)
    {
        flag[i] = 0;              // 顶点i的最短路径还没获取到。
        prev[i] = 0;              // 顶点i的前驱顶点为0。
        dist[i] = G.arcs[vs][i];// 顶点i的最短路径为"顶点vs"到"顶点i"的权。
    }//表格式记法

    // 对"顶点vs"自身进行初始化
    flag[vs] = 1;
    dist[vs] = 0;

    /*请在此处补充代码实现dijkstra算法*/


    // 打印dijkstra最短路径的结果
    printf("dijkstra(%c): \n", G.vexs[vs]);
    for (i = 0; i < G.vexnum; i++)
        printf("  shortest(%c, %c)=%d\n", G.vexs[vs], G.vexs[i], dist[i]);
}


int main(){
    MGraph mg;
    createMGraph(&mg);
    print(mg);
    DFSTraverse(mg);
    BFSTraverse(mg);
    return 0;

}