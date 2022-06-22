#include<stdio.h>
#include<conio.h>
#define inputfile "t6.txt"
#define MAX 20	
#define MAXQUEUE 100

typedef struct GRAPH
{ 	int n;
	int a[MAX][MAX];
}DOTHI;

struct QUEUE
{	int array[MAXQUEUE];
	int size;
};

int LuuVet[MAX];
int ChuaXet[MAX];


int DocMaTranKe(const char* TenFile,DOTHI &g)
{	FILE* f;
	f = fopen(TenFile,"rt");
	if(f==NULL)
	{
		printf("Khong mo duoc file\n");
		return 0;
	}
	fscanf(f,"%d",&g.n);
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
			fscanf(f,"%d",&g.a[i][j]);
	fclose(f);
	return 1;
}

void XuatMaTranKe(DOTHI g)
{	printf("So dinh cua do thi = %d\n",g.n);
	printf("Ma tran ke cua do thi la:\n");
	for(int i=0;i<g.n;i++)
	{	for(int j=0;j<g.n;j++)
			printf("%4d",g.a[i][j]);
		printf("\n");
	}
}

int KiemTraMaTranKeHopLe(DOTHI g)
{
	for(int i=0;i<g.n;i++)
		if(g.a[i][i] != 0)
			return 0;
	return 1;
}

void KhoiTaoQueue(QUEUE &Q) 
{	Q.size = 0;
}

int KiemTraQueueRong(QUEUE &Q)
{
	return (Q.size <= 0);
}

int DayGiaTriVaoQueue(QUEUE &Q, int value) 
{	if(Q.size+1 >= MAXQUEUE) return 0; 
	Q.array[Q.size] = value;
	Q.size++;
	return 1;
}

int LayGiaTriRaKhoiQueue(QUEUE &Q, int& value) 
{	if(Q.size <= 0) return 0; 
	value = Q.array[0]; 
	for(int i=0; i<Q.size-1; i++)
		Q.array[i] = Q.array[i+1];
	Q.size--;
	return 1;
}

void KetQua_DeQui(int S, int F)
{
	if(F != S) KetQua_DeQui(S, LuuVet[F]);
	printf("%d -> ", F);
}

void BFS(int v, DOTHI g)
{
	QUEUE Q;
	KhoiTaoQueue(Q);
	DayGiaTriVaoQueue(Q,v);
	while( ! KiemTraQueueRong(Q))
	{
		LayGiaTriRaKhoiQueue(Q,v);
		ChuaXet[v] = 1; 
		for(int u=0; u<g.n; u++)
		{
			if(g.a[v][u] !=0 && ChuaXet[u] ==0 && LuuVet[u] == -1) 
			{	
				DayGiaTriVaoQueue(Q,u); 
				LuuVet[u] = v;  
			}
		}
	}
}
//==============================================================
void DuyetTheoBFS(int S, int F, DOTHI g)
{
	for(int i=0; i<g.n; i++)
	{
		LuuVet[i] = -1;
		ChuaXet[i] = 0;
	}
	BFS(S, g);
	if(ChuaXet[F] == 1) 
	{	
		printf("\n BFS: Duong di tu dinh %d -> %d la:\n\t", S, F);
		KetQua_DeQui(S, F);
		printf("\b\b\b\b.   \n");
	}
	else printf("\n Khong co duong di tu dinh %d -> %d.\n", S, F);
}
void Bai2(GRAPH g)
{
	int dau;
	printf("\ncac thu tu duyet theo tu dinh dau ");
	printf("\n\nNhap dinh dau: ");
	scanf("%d", &dau);
	
	for (int i = 0; i < g.n; i++)
	{
		DuyetTheoBFS(dau, i, g);
		printf("\n");		
	}
}
int main()
{
	DOTHI g;
	char ch;
	int S,F;
	do
	{
		if(DocMaTranKe(inputfile, g)==1) 
		{
			printf("\n Da lay thong tin do thi tu file thanh cong.\n\n");
			XuatMaTranKe(g);
		
			printf("\n Nhap Dinh bat dau: "); scanf("%d", &S);
			printf("\n Nhap Dinh ket thuc: "); scanf("%d", &F);
			
			DuyetTheoBFS(S,F,g);
			Bai2(g);
		}
		printf("\n\n-----------------------\n");
		printf("Ban tiep tuc nua khong[Y/N]: ");
		ch=getche();
	}while(ch=='Y'||ch=='y');
	return 0;
}
