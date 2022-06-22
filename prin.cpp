
#include<stdio.h>
#include<conio.h>
#define inputfile "t6.txt"
#define MAX 50
#define MAX_VALUE 100

typedef struct GRAPH
{
	int n;
	int a[MAX][MAX];
}DOTHI;

typedef struct EDGE
{
	int u,v,value;
}CANH;

CANH T[MAX]; 
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

void DiTimCacDinhLienThong(DOTHI g, int Nhan[], int i)
{
	for(int j=0;j<g.n;j++)
		if(g.a[i][j] !=0 && Nhan[j] != Nhan[i])
		{
			Nhan[j] = Nhan[i];
			DiTimCacDinhLienThong(g, Nhan, j);
		}
}

int XetLienThong(DOTHI g)
{
	int Nhan[MAX];
	for(int i=0;i<g.n;i++)
		Nhan[i] = 0;
	
	int SoThanhPhanLT = 0;
	for(int i=0;i<g.n;i++)
		if(Nhan[i] ==0)
		{
			SoThanhPhanLT++;
			Nhan[i] = SoThanhPhanLT;
			DiTimCacDinhLienThong(g, Nhan, i);
		}
	return (SoThanhPhanLT == 1);
}

void Prim(DOTHI g)
{
	if(XetLienThong(g) ==0)
	{
		printf("\nDo thi khong lien thong nen khong co Prim");
		return;
	}
	int nT=0;

	for(int i=0;i<g.n;i++) 
		ChuaXet[i] = 0;
	ChuaXet[0] = 1; 
	while(nT<g.n-1)
	{	CANH CanhNhoNhat;
		int GiaTriNhoNhat=MAX_VALUE;
		for(int i=0;i<g.n;i++)
		{	if(ChuaXet[i] ==1)
				for(int j=0;j<g.n;j++)
					if(ChuaXet[j] ==0 && g.a[i][j] !=0 && GiaTriNhoNhat > g.a[i][j])
					{	CanhNhoNhat.u =i;
						CanhNhoNhat.v =j;
						CanhNhoNhat.value =g.a[i][j];
						GiaTriNhoNhat =g.a[i][j];
					}
		}
		T[nT++] = CanhNhoNhat;
		ChuaXet[CanhNhoNhat.v] =1; 
	}
	int TongTrongSoCuaCayKhung =0;
	printf("Cay khung nho nhat cua do thi la:\n");
	for(int i=0;i<nT-1;i++)
	{	printf("[%d,%d(%d)], ", T[i].u,T[i].v,T[i].value);
		TongTrongSoCuaCayKhung += T[i].value;
	}
	printf("[%d,%d(%d)].", T[nT-1].u,T[nT-1].v,T[nT-1].value);
	TongTrongSoCuaCayKhung += T[nT-1].value;
	printf("\nTong trong so cua cay khung la: %d\n",TongTrongSoCuaCayKhung);
}

int main()
{                                 
	DOTHI g;
	char ch;
	do
	{
		
		if(DocMaTranKe(inputfile, g)==1) 
		{
			printf("Da lay thong tin do thi tu file thanh cong.\n\n");
			XuatMaTranKe(g);
		
			printf("\n\n PRIM: ");
			Prim(g);
		}
		printf("\n\n-----------------------\n");
		printf("Ban tiep tuc nua khong[Y/N]: ");
		ch=getche();
	}while(ch=='Y'||ch=='y');
	return 0;
}

