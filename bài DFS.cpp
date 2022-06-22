#include<stdio.h>
#include <conio.h>
#include<stdlib.h>
#define MAX 20
#define inputfile "t6.txt"
struct Graph{
	int n;				
	int a[MAX][MAX]; 
};

int luuvet[MAX];
int chuaxet[MAX];
int docfile(char dd[100], Graph &g){
	FILE *f = fopen(dd,"rt");
	if (f == NULL)
	{
		printf("Mo file khong thanh cong!\n");
		return 0;
	}

	fscanf(f,"%d",&g.n);

	for(int i=0 ; i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
		{
			fscanf(f,"%d",&g.a[i][j]);
		}
	}

	fclose(f);
	return 1;
}

void xuatmatranke(Graph g){
	printf("Do thi co %d dinh\n",g.n);
	printf("Ma tran ke: \n");
	for(int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
		{
			printf("%3d",g.a[i][j]);
		}
		printf("\n");
	}
}
void DFS(int v, Graph g){
	chuaxet[v] =1;
	
	for(int u =0;u<g.n;u++){
		if(g.a[v][u] !=0 && chuaxet[u] == 0){
			luuvet[u]=v;
			DFS(u,g);
		}
	}
}

void Duyettheochieusau(int S,int F, Graph g)
{
	for(int i=0 ; i<g.n ; i++)
	{
		luuvet[i]=-1;
		chuaxet[i]=0;
	}
	DFS(S,g);
	if(chuaxet[F] == 1)
	{
		printf("\nDuong di DFS tu dinh %d den dinh %d la: \n",S,F);
		int i = F;
		while(i!=S)
		{
			printf(" %d <---",i);
			i=luuvet[i];
		}
		printf(" %d ",S);	
	}
	else{
		printf("Khong do duong di DFS tu dinh %d den dinh %d \n",S,F);
	}
}
int main()
{
	Graph g;
	int S,F;
	if(docfile(inputfile,g)==1)
	{
		printf(" da lay duoc thong rin tu do thi\n");
		xuatmatranke(g);
		printf("nhap dinh bat dau :\n");
		scanf("%d",&S);
		printf("nhap dinh cuoi :\n");
		scanf("%d",&F);
		getch();
		Duyettheochieusau(S,F,g);
		
	}

}
