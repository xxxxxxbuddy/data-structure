#include<iostream>
#include<iomanip>
using namespace std;
#define  OK  1
#define  MAX_VERTEX_NUM  20  //最大顶点数
#define  INFINITY  32768  //无穷大 

typedef int Status;  //函数的类型，其值是函数结果状态代码
typedef char VertexType;
typedef int VRType;
typedef int InforType;

//堆定义 
typedef struct Heap
{
	VertexType tail;
	VertexType head;
	VRType cost;
}Heap,HeapNode[MAX_VERTEX_NUM];

typedef struct ArcCell
{
	VRType adj;  //顶点关系类型，对无权图，用1或0表示相邻否；对带权图，则为权值类型
	InforType *info;  //该弧相关信息指针 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];  //顶点数量
	AdjMatrix arcs;  //邻接矩阵
	int vexnum,arcnum;  //图的当前顶点数和弧数 
} MGraph;

//返回顶点v在顶点向量中的位置
int LocateVex(MGraph G,char v)
{
	int i;
	for(i=0;v!=G.vexs[i] && i<G.vexnum;++i); 
	if(i>=G.vexnum){
		return -1;
	}
	return i;
 } 

//采用数组（邻接矩阵）表示法，构造无向网
Status CreateUDN(MGraph &G)
{
	cout<<"输入顶点数vexnum：";
	cin>>G.vexnum;
	cout<<"输入弧数arcnum：";
	cin>>G.arcnum;
	cout<<"构造顶点向量\n"; //构造顶点向量
	for(int i1=0;i1<G.vexnum;++i1)
	{
		cout<<"输入图的第"<<i1+1<<"个顶点信息：";
		cin>>&G.vexs[i1];
	 } 
	 for(int i=0;i<G.vexnum;++i)  //初始化邻接矩阵
	 	for(int j=0;j<G.vexnum;++j)
		 {
		 	G.arcs[i][j].adj=INFINITY;  //{adj,info}
		 	G.arcs[i][j].info=NULL;
		  } 
		char v1,v2;
		int w;
		for(int k=0;k<G.arcnum;++k)  //构造邻接矩阵 
		{
			cout<<"输入第"<<k+1<<"条边依附的顶点v1:";
			cin>>v1;
			cout<<"输入第"<<k+1<<"条边依附的顶点v2:";
			cin>>v2;
			cout<<"输入第"<<k+1<<"条边的权值w：";
			cin>>w;
			int ii=LocateVex(G,v1);  //确定v1，v2在G中的位置 
			int jj=LocateVex(G,v2);
			G.arcs[ii][jj].adj=w;  //弧的权值
			G.arcs[jj][ii].adj=G.arcs[jj][ii].adj;  //值<v1,v2>的对称弧<v2,v1> 
		} 
		return OK; 
 } 
 
 //输出建立的无向图的邻接矩阵G
 Status PrintMGraph(MGraph G)
 {
 	cout<<"建立的图邻接矩阵为："<<endl;
 	cout<<"----32768代表无穷大----"<<endl;
 	cout<<setw(5)<<""; 
 	for(int i=0;i<G.vexnum;++i)
 	{
		 cout<<setw(10)<<G.vexs[i];
	}
	cout<<endl;
	for(int i=0;i<G.vexnum;++i)
	{
		cout<<setw(5)<<G.vexs[i]<<"|";
		for(int j=0;j<G.vexnum;++j)
		{
			cout<<setw(10)<<G.arcs[i][j].adj;
		}
		cout<<"|"<<endl; 
	  }  
 	return OK;
  } 
  
  //按照无向图邻接矩阵创建初始堆
  void createHeap(MGraph G,HeapNode H)
  {
  	int i,j,k=0;
  	for(i=0;i<G.vexnum;i++)
  	{
		for(j=1;j<G.vexnum;j++)
  		{
  			if(G.arcs[i][j].adj!=INFINITY)
  			{
  				H[k].tail=G.vexs[i];
  				H[k].head=G.vexs[j];
  				H[k].cost=G.arcs[i][j].adj;
  				k++;
			  }
		  }
   } 
}
   
   //调整H[s]的关键字适使H[s..m]成为一个小顶堆
   void HeapAdjust(HeapNode H,int s,int m)
   {
   	int j;
   	Heap h0;
   	h0=H[s-1];
   	for(j=2*s;j<=m;j*=2)
   	{
   		if(j<m && H[j-1].cost>H[j].cost) ++j;  //j为key值较大的记录下标
		if(h0.cost<H[j-1].cost) break;
		H[s-1]=H[j-1];
		s=j; 
	   }
	H[s-1]=h0;
	} 
	
	//按照克鲁斯卡尔算法构造无向图G的最小生成树T，输出T的各边
	void MinSpanTree_Kruscal(MGraph G,HeapNode H)
	{
		Heap h0;
		int Vset[MAX_VERTEX_NUM],v1,v2,t;
		int k=0;
		int j=0;
		for(j=0;j<G.vexnum;j++)
		{
			Vset[j]=j;
		}
		cout<<"最小生成树上的边为："<<endl;
		for(int i=G.arcnum;i>0 && k<G.vexnum;--i)		//对当前H[1..i]进行堆排序，共做n-1趟
		{
			v1=LocateVex(G,H[0].tail);
			v2=LocateVex(G,H[0].head);
			if(Vset[v1]!=Vset[v2])
			{
				cout<<"("<<H[0].tail<<","<<H[0].head<<")";  //输出最小生成树上的边
				k++; 
				t=Vset[v2];  //保存v2顶点的连通分量
				for(int j=0;j<G.vexnum;j++)
				{
					if(Vset[j]==t)
					{
						Vset[j]=Vset[v1];
					}
				}
			}
			h0=H[i-1];  //将堆顶和堆中最后一个记录交换
			H[i-1]=H[0];
			H[0]=h0;
			HeapAdjust(H,1,i-1);  //将H[1..i-1]重新调整为最小堆 
		 } 
		 cout<<endl; 
	 } 
	 
	 int main()
	 {
	 	MGraph G;
	 	HeapNode H;
	 	CreateUDN(G);  //建立无向图的邻接矩阵
		PrintMGraph(G);  //输出建立的无向图
		createHeap(G,H);  //根据邻接矩阵创建初始堆
		for(int i=G.arcnum/2;i>0;--i)  //将图按照边权值简称初始最小堆
		{
			HeapAdjust(H,i,G.arcnum);
		}
		MinSpanTree_Kruscal(G,H);  //用Kruscal算法建立最小树 
	 }
