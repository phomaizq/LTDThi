#include<stdio.h>
#include<conio.h>
#define infinity 1000
#define MAX 100
#define inputfile "t6.txt"
typedef struct GRAPH{
	int n;
	int a[MAX][MAX];
}DOTHI; 

int LuuVet[MAX];
int ChuaXet[MAX];
int DoDaiDuongDiToi[MAX];
int NhapDoThi (char TenFile[100], DOTHI &g)
{	
	FILE*f;
	f=fopen(TenFile,"rt");
	if(f==NULL) 
	{
		printf("khong mo duoc file\n");
		return 0;
	}
	fscanf(f,"%d",&g.n);
	int i,j;
	for(i=0;i<g.n;i++)
	{
		for(j=0;j<g.n;j++)
		fscanf(f,"%d",&g.a[i][j]);
	}
	fclose(f);
	return 1;
} 
 
 void XuatMaTranKe(DOTHI g)
 {
 	printf("So dinh cua do thi la %d\n",g.n);
 	printf("Ma tran ke cua do thi la\n");
 	for(int i =0;i<g.n;i++)
 	{
 		printf("\t");
 		for (int j=0; j<g.n;j++)
 		printf ("%3d",g.a[i][j]);
 		printf("\n");	
	 }
 	 
 }
 
 
int FindingMinDistance (DOTHI g)
{
	int li = -1; 
	float p = infinity;
	for(int i = 0 ; i< g.n ; i++)
	{
	if(ChuaXet[i] == 0 && DoDaiDuongDiToi[i] < p)
		{
		p = DoDaiDuongDiToi[i];
		li = i;
		}
	}
	return li; 
}
void UpdateWay(int u, DOTHI g)
{
	ChuaXet[u] = 1;
	for(int v = 0; v < g.n ; v++)
	{
		if(ChuaXet[v]==0 && g.a[u][v] >0 && g.a[u][v] < infinity) 
		if(DoDaiDuongDiToi[v] > DoDaiDuongDiToi[u] + g.a[u][v]) 
		{
			DoDaiDuongDiToi[v] = DoDaiDuongDiToi[u] + g.a[u][v];
			LuuVet[v] = u;
		}
	}
}
void Dijkstra (int F,int S, DOTHI g)
{
	int i;
	for (i = 0; i< g.n ; i++)
	{
		ChuaXet[i] = 0;
		DoDaiDuongDiToi[i] = infinity;
		LuuVet[i] = -1;		
	}
	DoDaiDuongDiToi[S] = 0; 
	while(ChuaXet[F] == 0) 
	{
		int u = FindingMinDistance(g); 
		if(u == -1) break; 
		UpdateWay(u,g); 
	}
	if (ChuaXet[F] == 1) 
	{
		printf("Duong di ngan nhat tu dinh %d den dinh %d la: \n\t",S,F);
		i = F;
		printf("%d ", F);
		while (LuuVet[i] != S)
		{
			printf ("->%d", LuuVet[i]);
			i = LuuVet[i];
			}
			printf ("->%d\n", LuuVet[i]);
			printf("\tVoi do dai la %d\n",DoDaiDuongDiToi[F]);
		}
	else 
	{
		printf("Khong co duong di tu dinh %d den dinh %d \n",S,F);
	}	
}

int main ()
{	
	DOTHI g;	
	int s,f;	
	NhapDoThi(inputfile,g);
	XuatMaTranKe(g);
	printf("moi nhap diem bat dau va diem den :\n");
	printf ("nhap diem dau :");
	scanf("%d",&s);
	printf ("nhap diem cuoi :");
	scanf("%d",&f);
	
	Dijkstra(s,f,g);
	return 0;
}

