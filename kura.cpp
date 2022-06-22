#include<stdio.h>
#include<conio.h>
#define max 100
#define input "t6.txt"
struct matran{
	int size;
	int g[max][max];
};
struct canh{
	int n;
	int a;
	int b;
};
canh caykhung[max];

int InPutMT(char name[100],matran & a){
	FILE*f;
	f=fopen(name,"rt");
	if(f==NULL)
	{
	printf("\nERROR\n");
	return 0;
	}
	fscanf(f,"%d",&a.size);
	for (int i=0;i<a.size;i++) 
		for (int j=0;j<a.size;j++)  
			fscanf(f,"%d",&a.g[i][j]);
	printf("\nInput success\n");
	fclose(f);
	return 1;	
}

void Sort (canh E[100],int tongsocanh)
{
	canh canhtam;
	for(int i=0;i<tongsocanh;i++)
	{
		for(int j = 0 ;j<tongsocanh;j++)
		{
			if(E[i].n<E[j].n)
			{
				canhtam=E[i];
				E[i]=E[j];
				E[j]=canhtam;
			}
		}
	}
}


void output (matran a )
{
	int n = a.size;
	for (int i =0 ; i<n; i ++)
	{
		printf("\n");
		for (int j =0 ; j<n; j ++)
		printf("%4d",a.g[i][j]);
	}
}
void kruskal(matran a)
{
	canh listedge[max];
	int tongcanh=0;
	int i,j;
	for(i = 0 ; i<a.size;i++)
	{
		for(j=i+1;j<a.size;j++)
			if(a.g[i][j]>0)
			{
				listedge[tongcanh].a=i;
				listedge[tongcanh].b=j;
				listedge[tongcanh].n=a.g[i][j];
				tongcanh++;
			}
	}
	Sort(listedge,tongcanh);
	int nT=0;
	canh T[max];
	int nhan[max];
	for(i=0;i<a.size;i++)
	{
		nhan[i]=i;
	}
	int canhdangxet =0 ;
	while(nT<a.size&& canhdangxet<tongcanh)
	{
		
		if(nhan[listedge[canhdangxet].a]!=nhan[listedge[canhdangxet].b])
		{
			T[nT]=listedge[canhdangxet];
			nT++;
			int giatri=nhan[listedge[canhdangxet].b];
			for(j=0;j<a.size;j++)
				if(nhan[j]==giatri)
					nhan[j]=nhan[listedge[canhdangxet].a];
		}
		canhdangxet++;
	}
	if(nT!=a.size-1)
		printf("do thi khong lien thong");
	else
	{
		int tong=0;
			for(int i=0;i<nT;i++)
			{
				tong+=T[i].n;
				printf("\n canh: (%d;%d)",T[i].a,T[i].b);
			}
				printf("\ntong cua cay khung la %d\n",tong);
	}
}

int main()
{
	matran a;	
	char ch;
	do

	{
		
		if(InPutMT(input,  a)==1) 
		{
			printf("Da lay thong tin do thi tu file thanh cong.\n\n");
			output(a);
			printf("\n\n KRUSKAL: ");
			kruskal(a);
		}	
	}while(ch=='Y'||ch=='y');
	return 0;
}
