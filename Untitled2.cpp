#include <stdio.h>
#include <conio.h>

#define inputfile "t6.txt"
#define MAX 100

int ArrTrace[MAX];
int ArrLabel[MAX];

struct GRAPH
{
	int n;
	int a[MAX][MAX];
};

struct QUEUE
{
	int size;
	int array[MAX];
};

int ReadMatrix(char filepath[100], GRAPH &g)
{
	FILE* f;
	f = fopen(filepath,"rt");
	
	if (f == NULL)
	{
			printf("can not open this file");
			return 0;
		}
	
	fscanf(f, "%d", &g.n);
	
	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n;j++)
		{
			fscanf(f, "%d", &g.a[i][j]);
		}
	}
	
	fclose(f);
	return 1;
}

void OutputMatrix(GRAPH g)
{
	printf("The number of vertices in the graph is: %d\n", g.n);
	
	printf("The adjacency matrix of the graph is: \n");
	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n; j++)
		{
			printf("\t%d", g.a[i][j]);
		}
		printf("\n");
	}
}

int ValidityCheck(GRAPH g)
{
	for (int i = 0; i < g.n; i++)
	{
		if (g.a[i][i] != 0)
			return 0;
	}
	return 1;
}

void CreateQueue(QUEUE &q)
{
	q.size = 0;
}

int DayGiaTriVaoQueue(QUEUE &q, int value)
{
	if (q.size + 1 >= 100)
		return 0;
	q.array[q.size] = value;
	q.size++;
	return 1;
}

int LayGiaTriRaKhoiQueue(QUEUE &q, int &value)
{
	if (q.size <= 0)
		return 0;
	value = q.array[0];
	for (int i = 0; i < q.size; i++)
		q.array[i] = q.array[i+1];
	q.size--;
	return 1;
}

int CheckQueueRong(QUEUE q)
{
	if (q.size <= 0)
		return 1;
	return 0;
}

void BFS(int v, GRAPH g)
{
	QUEUE q;
	CreateQueue(q);
	DayGiaTriVaoQueue(q,v);
	while (!CheckQueueRong(q))
	{
		LayGiaTriRaKhoiQueue(q,v);
		ArrLabel[v] = 1;
		for (int u = 0; u < g.n; u++)
		{
			if (g.a[v][u] != 0 && ArrLabel[u] == 0)
			{
				DayGiaTriVaoQueue(q,u);
				if (ArrTrace[u] == -1)
					ArrTrace[u] = v;
			}
		}
	}
}

void DuyetTheoBFS(int S, int F, GRAPH g)
{
	int i;
	for (int u = 0; u < g.n; u++)
	{
		ArrLabel[u] = 0;
		ArrTrace[u] = -1;
	}
	
	BFS(S,g);
	
	if (ArrLabel[F] == 1 && S != F)
	{
		printf("\nDuong di tu dinh %d den dinh %d la: \n\t", S, F);
		i = F;
		printf("\t%d ", F);
		while (ArrTrace[i] != S)
		{
			printf("<-- %d ", ArrTrace[i]);
			i = ArrTrace[i];
		}	
		printf("<-- %d ", ArrTrace[i]);
	}
	else
	{
		printf("\nKhong co duong di tu dinh %d den dinh %d", S, F);
	}		
}

void DuongDi(GRAPH g)
{
	int dau, cuoi;
	
	printf("\nNhap dinh dau: ");
	scanf("%d", &dau);
	printf("Nhap dinh cuoi: ");
	scanf("%d", &cuoi);
	
	DuyetTheoBFS(dau,cuoi,g);
}

void Bai2(GRAPH g)
{
	int dau;
	printf("cac thu tu duyet theo tu dinh dau :");
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
	GRAPH g;
	
	if (ReadMatrix(inputfile, g) == 1)
	{
		printf("Retrieved graph information from file successfully \n");
		OutputMatrix(g);
		
		if (ValidityCheck(g) == 1)
		{
			printf("The graph is valid\n");
			DuongDi(g);
			Bai2(g);
		}
		else
		{
			printf("The graph is invalid\n");
		}
	}
	
	return 0;
}
