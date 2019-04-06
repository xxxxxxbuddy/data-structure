#include<iostream>
#include<iomanip>
using namespace std;
#define  OK  1
#define  MAX_VERTEX_NUM  20  //��󶥵���
#define  INFINITY  32768  //����� 

typedef int Status;  //���������ͣ���ֵ�Ǻ������״̬����
typedef char VertexType;
typedef int VRType;
typedef int InforType;

//�Ѷ��� 
typedef struct Heap
{
	VertexType tail;
	VertexType head;
	VRType cost;
}Heap,HeapNode[MAX_VERTEX_NUM];

typedef struct ArcCell
{
	VRType adj;  //�����ϵ���ͣ�����Ȩͼ����1��0��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ����
	InforType *info;  //�û������Ϣָ�� 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];  //��������
	AdjMatrix arcs;  //�ڽӾ���
	int vexnum,arcnum;  //ͼ�ĵ�ǰ�������ͻ��� 
} MGraph;

//���ض���v�ڶ��������е�λ��
int LocateVex(MGraph G,char v)
{
	int i;
	for(i=0;v!=G.vexs[i] && i<G.vexnum;++i); 
	if(i>=G.vexnum){
		return -1;
	}
	return i;
 } 

//�������飨�ڽӾ��󣩱�ʾ��������������
Status CreateUDN(MGraph &G)
{
	cout<<"���붥����vexnum��";
	cin>>G.vexnum;
	cout<<"���뻡��arcnum��";
	cin>>G.arcnum;
	cout<<"���춥������\n"; //���춥������
	for(int i1=0;i1<G.vexnum;++i1)
	{
		cout<<"����ͼ�ĵ�"<<i1+1<<"��������Ϣ��";
		cin>>&G.vexs[i1];
	 } 
	 for(int i=0;i<G.vexnum;++i)  //��ʼ���ڽӾ���
	 	for(int j=0;j<G.vexnum;++j)
		 {
		 	G.arcs[i][j].adj=INFINITY;  //{adj,info}
		 	G.arcs[i][j].info=NULL;
		  } 
		char v1,v2;
		int w;
		for(int k=0;k<G.arcnum;++k)  //�����ڽӾ��� 
		{
			cout<<"�����"<<k+1<<"���������Ķ���v1:";
			cin>>v1;
			cout<<"�����"<<k+1<<"���������Ķ���v2:";
			cin>>v2;
			cout<<"�����"<<k+1<<"���ߵ�Ȩֵw��";
			cin>>w;
			int ii=LocateVex(G,v1);  //ȷ��v1��v2��G�е�λ�� 
			int jj=LocateVex(G,v2);
			G.arcs[ii][jj].adj=w;  //����Ȩֵ
			G.arcs[jj][ii].adj=G.arcs[jj][ii].adj;  //ֵ<v1,v2>�ĶԳƻ�<v2,v1> 
		} 
		return OK; 
 } 
 
 //�������������ͼ���ڽӾ���G
 Status PrintMGraph(MGraph G)
 {
 	cout<<"������ͼ�ڽӾ���Ϊ��"<<endl;
 	cout<<"----32768���������----"<<endl;
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
  
  //��������ͼ�ڽӾ��󴴽���ʼ��
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
   
   //����H[s]�Ĺؼ�����ʹH[s..m]��Ϊһ��С����
   void HeapAdjust(HeapNode H,int s,int m)
   {
   	int j;
   	Heap h0;
   	h0=H[s-1];
   	for(j=2*s;j<=m;j*=2)
   	{
   		if(j<m && H[j-1].cost>H[j].cost) ++j;  //jΪkeyֵ�ϴ�ļ�¼�±�
		if(h0.cost<H[j-1].cost) break;
		H[s-1]=H[j-1];
		s=j; 
	   }
	H[s-1]=h0;
	} 
	
	//���տ�³˹�����㷨��������ͼG����С������T�����T�ĸ���
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
		cout<<"��С�������ϵı�Ϊ��"<<endl;
		for(int i=G.arcnum;i>0 && k<G.vexnum;--i)		//�Ե�ǰH[1..i]���ж����򣬹���n-1��
		{
			v1=LocateVex(G,H[0].tail);
			v2=LocateVex(G,H[0].head);
			if(Vset[v1]!=Vset[v2])
			{
				cout<<"("<<H[0].tail<<","<<H[0].head<<")";  //�����С�������ϵı�
				k++; 
				t=Vset[v2];  //����v2�������ͨ����
				for(int j=0;j<G.vexnum;j++)
				{
					if(Vset[j]==t)
					{
						Vset[j]=Vset[v1];
					}
				}
			}
			h0=H[i-1];  //���Ѷ��Ͷ������һ����¼����
			H[i-1]=H[0];
			H[0]=h0;
			HeapAdjust(H,1,i-1);  //��H[1..i-1]���µ���Ϊ��С�� 
		 } 
		 cout<<endl; 
	 } 
	 
	 int main()
	 {
	 	MGraph G;
	 	HeapNode H;
	 	CreateUDN(G);  //��������ͼ���ڽӾ���
		PrintMGraph(G);  //�������������ͼ
		createHeap(G,H);  //�����ڽӾ��󴴽���ʼ��
		for(int i=G.arcnum/2;i>0;--i)  //��ͼ���ձ�Ȩֵ��Ƴ�ʼ��С��
		{
			HeapAdjust(H,i,G.arcnum);
		}
		MinSpanTree_Kruscal(G,H);  //��Kruscal�㷨������С�� 
	 }
