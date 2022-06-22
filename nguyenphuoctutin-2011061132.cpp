#include <stdio.h>
#include <conio.h>
#define VOCUC 1000
#define MAX 30
#define inputfile "t6.txt"


int luuVet[MAX];
int chuaXet[MAX];
int doDaiDuongDi[MAX];

struct GRAPH {
	int n;
	int a[MAX][MAX];
};

int DocMaTranKe(char TenFile[100], GRAPH &g) {
	FILE* f;
	f = fopen(TenFile,"rt");
	if (f == NULL) {
		printf("ERROR !!!\n");
		return 0;
	}
	fscanf(f,"%d",&g.n);
	for (int i = 0; i < g.n; i++) {
		for (int j = 0; j < g.n; j++) {
			fscanf(f,"%d",&g.a[i][j]);
		}
	}
	fclose(f);
	return 1;	
}

void XuatMaTranKe(GRAPH g) {
	printf("So dinh cua do thi: %d\n",g.n);
	printf("Ma tran ke cua do thi la:\n");
	for (int i = 0; i < g.n; i++) {
		for (int j = 0; j < g.n; j++) {
			printf("%5d",g.a[i][j]);
		}
		printf("\n");
	}
}

int timDuongNganNhat(GRAPH g) {
	int li = -1;
	float p = VOCUC;
	for (int i = 0; i < g.n; i++) {
		if (chuaXet[i] == 0 && doDaiDuongDi[i] < p) {
			p = doDaiDuongDi[i];
			li = i;
		}
	}
	return li;
}

void capNhatDuongDi(int u, GRAPH g) {
	chuaXet[u] = 1;
	for (int v = 0; v < g.n; v++) {
		if (chuaXet[v] == 0 && g.a[u][v] > 0 && g.a[u][v] < VOCUC) {
			if (doDaiDuongDi[v] > doDaiDuongDi[u] + g.a[u][v]) {
				doDaiDuongDi[v] = doDaiDuongDi[u] + g.a[u][v];
				luuVet[v] = u;
			}
		}
	}
}

int sau_nut[MAX][MAX];
int L[MAX][MAX];

void floyd(GRAPH g) {
	int i,j;
	for (i = 0; i < g.n; i++) {
		for (j = 0; j < g.n; j++) {
			if (g.a[i][j] > 0) {
				sau_nut[i][j] = j;
				L[i][j] = g.a[i][j];
			}
			else {
				sau_nut[i][j] = -1;
				L[i][j] = VOCUC;
			}
		}
	}
	
	for (int k = 0; k < g.n; k++) {
		for (i = 0; i < g.n; i++) {
			for (j = 0; j <g.n; j++) {
				if (L[i][j] > L[i][k] + L[k][j]) {
					L[i][j] = L[i][k] + L[k][j];
					sau_nut[i][j] = sau_nut[i][k];
				}				
			}
		}
	}
	int s,f;
	printf("\nNhap dinh bat dau: "); scanf("%d",&s);
	printf("\nNhap dinh ket thuc: "); scanf("%d",&f);
	if (sau_nut[s][f] == -1) {
		printf("Khong co duong di tu dinh %d den dinh %d !!!!\n",s,f);
	}
	else {
		printf("Duong di ngan nhat tu dinh %d den dinh %d la: \n\t",s,f);
		printf("\t%d",s);
		int u = s;
		while (sau_nut[u][f] != f) {
			u = sau_nut[u][f];
			printf("--> %d",u);
		}
		printf("--> %d",f);
		printf("\n\tVoi do dai la %d \n",L[s][f]);
	}
}
int main()
{	
	GRAPH g;
	int s,f;
	{
		if (DocMaTranKe(inputfile,g) == 1) 
		printf("\nDa doc file thanh cong\n");	
		XuatMaTranKe(g);	
		printf("-------------------------------------");		
	}
	floyd(g);
	return 0;
}

