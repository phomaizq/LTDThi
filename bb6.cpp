#include<stdio.h>
#include<conio.h>
#define infinity 1000
#define MAX 100
#define inputfile "t6.txt"
typedef struct GRAPH{
	int n;
	int a[MAX][MAX];
}DOTHI; 

int Sau_Nut[MAX][MAX];
int L[MAX][MAX];
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
 
 

void Floyd(DOTHI g)
{
	int i ,j;
	for( i = 0; i< g.n ; i++)
	{
		for(j = 0 ; j <g.n ; j++)
		{
			if(g.a[i][j]!=0)
			{
				Sau_Nut[i][j] = j;
				L[i][j]=g.a[i][j];
			}
			else 
			{
				Sau_Nut[i][j] = -1;
				L[i][j]=infinity;
			}
		}
	}
	
	for(int k =0 ; k <g.n;k++)
	{
		for( i = 0; i< g.n ; i++)
		{
			for(j = 0 ; j <g.n ; j++)
			{
				if(L[i][j]> L[i][k]+L[k][j])
				{
					L[i][j]=L[i][k]+L[k][j];
					Sau_Nut[i][j] = Sau_Nut[i][k];			
				}
				
			}
		}
	}

	int s,f;
	printf("moi nhap diem bat dau :");
	scanf("%d",&s);
	printf("moi nhap diem cuoi : ");
	scanf("%d",&f);

	if(Sau_Nut[s][f]==-1) printf("Khong co duong di tu dinh %d den dinh %d la :\n",f,s);
	else 
	{
		printf("Duong di ngan nhat tu dinh %d den dinh %d la: \n\t",s,f);
		printf("\t%d",s);
		int u = s;
		while(Sau_Nut[u][f]!=f)
		{
			u=Sau_Nut[u][f];
			printf (" --> %d",u);
		}
		printf (" --> %d",f);
		printf ("\n\tVoi tong trong so la %d",L[s][f]);
	}
}
int main ()
{
	DOTHI g;	
	NhapDoThi(inputfile,g);
	XuatMaTranKe(g);
	

	
	Floyd(g);
	return 0;

}

