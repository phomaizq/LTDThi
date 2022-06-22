
#define MAX 100
#define inputfile "t6.txt"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int ChuaXet[MAX];
typedef struct GRAPH 
{
	int n; 
	int a[MAX][MAX]; 
};

int DocMaTranKe(char TenFile[100], GRAPH &g)
{
	FILE* f; 
	f = fopen(TenFile, "rt"); 
	if (f == NULL) 
	{
		printf("Khong mo duoc file\n");
		return 0; 
	}
		fscanf(f, "%d", &g.n);
	int i, j;
		for (i=0; i<g.n; i++)
		{
			for (j=0; j<g.n; j++)
			{	
				fscanf(f, "%d", &g.a[i][j]); 
			}
		}
	fclose(f);
	return 1; 
}
void XuatMaTranKe (GRAPH g)
{
	printf("So dinh cua do thi la %d\n", g.n);
	printf("Ma tran ke cua do thi la\n");
	for (int i = 0; i < g.n; i++)
	{
	printf ("\t");
		for (int j = 0; j < g.n; j++)
			{
				printf("%d ",g.a[i][j]);
			}
	printf("\n");
	}	
}
int XetLienThong(GRAPH g)
{
int Nhan[MAX];
int i;
for (i=0;i<g.n;i++)
	Nhan[i] =0;
	int SoThanhPhanLT =0;
	for (i=0; i<g.n; i++)
	{
		if (Nhan[i] == 0)
		{
			SoThanhPhanLT++;
			Nhan[i]=SoThanhPhanLT;
		}
	}
	printf ("So thanh phan lien thong la %d\n",SoThanhPhanLT);
return SoThanhPhanLT;
}
typedef struct EDGE
{
	int u;
	int v;
	int value;
}CANH;
CANH T[MAX];
void Prim (GRAPH g)
{
	if(XetLienThong(g) == 1)
	{		
	printf ("Do thi khong lien thong, do do khong thuc hien duoc thuat toan Prim tim cay khung nho nhat\n");
	return;
	}
	int nT=0;
	for(int i=0;i<g.n;i++)
		ChuaXet[i] = 0;
	ChuaXet[0] = 1;
	while (nT < g.n -1)
	{
		CANH CanhNhoNhat;
		int GiaTriNhoNhat = 100;
		for(int i=0 ;i<g.n;i++)
		{
			if (ChuaXet[i] == 1) 
			{
				for (int j = 0; j < g.n; j++)
				if (ChuaXet[j] == 0 && g.a[i][j] != 0 && GiaTriNhoNhat > g.a[i][j])
				{
					CanhNhoNhat.u=i;
					CanhNhoNhat.v=j;
					CanhNhoNhat.value=g.a[i][j];
					GiaTriNhoNhat=g.a[i][j];
				}
			}
		}
	T[nT]=CanhNhoNhat;
	nT++;
	ChuaXet[CanhNhoNhat.v]=1;
	}
	int TongTrongSoCuaCayKhung=0;
	printf ("Cay khung nho nhat cua do thi la \n");
	for (int i = 0; i < nT - 1; i++)
	{
	printf ("(%d,%d), ", T[i].u, T[i].v);
	TongTrongSoCuaCayKhung += T[i].value;
	}
	printf ("(%d,%d).\n", T[nT - 1].u, T[nT - 1].v);
	TongTrongSoCuaCayKhung += T[nT - 1].value;
	printf ("Tong gia tri cua cay khung la %d\n",TongTrongSoCuaCayKhung);
}
int main()
{
	GRAPH g;
 	int S,F;
	if (DocMaTranKe(inputfile, g) == 1)
	{
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
			XuatMaTranKe(g);
		printf("Bam 1 phim bat ki de bat dau thuat toan Prim ...\n\n");
		getch();
		Prim(g);
	}
}
