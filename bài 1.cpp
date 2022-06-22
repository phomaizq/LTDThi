#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define MAX 100
#define inputfile "Test_1.txt"

typedef struct GRAPH 
{
	int n;
	int a[MAX][MAX];
}DOTHI;

//ham DocMaTranKe
int DocMaTranKe(char TenFile[100], DOTHI &g)
{
	FILE* f;
	f=fopen(TenFile,"rt");
	if(f==NULL)
	{
		printf("\nKhong mo duoc file.\n");
		return 0;
	}
	fscanf(f,"%d",&g.n);
	int i,j;
	for(i=0;i<g.n;i++)
	{
		for(j=0;j<g.n;j++)
		{
			fscanf(f,"%d",&g.a[i][j]);
		}
	}
	fclose(f);
	return 1;
}

//ham XuatMaTranKe
void XuatMaTranKe(DOTHI g)
{
	printf("\n So dinh cua do thi la : %d",g.n);
	printf("\n ------------------------------------------");
	printf("\n Ma Tran ke cua do thi : \n");
	for(int i=0;i<g.n;i++)
	{
		printf("\t");
		for(int j=0;j<g.n;j++)
		{
			printf("%3d",g.a[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	DOTHI g;
	if(DocMaTranKe(inputfile,g)==1)
	{
		printf("\n -------------------------------------------");
		printf("\n Da doc duoc file.");
		printf("\n -------------------------------------------");
		XuatMaTranKe(g);
	}
	
	return 0;
}
