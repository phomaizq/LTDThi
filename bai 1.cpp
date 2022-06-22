#include<stdio.h>
#include<conio.h>

#define MAX 100
#define inputLink"t4.txt"
struct STACK
{
	int array[100];
	int size;
};

typedef struct GRAPH {
	int n;
	int a[MAX][MAX];
};

int ReadMatrix(char filepath[100], GRAPH &g)
{
	FILE* f;
	f = fopen(filepath, "rt");
	if (f == NULL)
	{
		printf("can not onpen this file");
		return 0;
	}
	fscanf(f, "%d", &g.n);
	for ( int i = 0;  i < g.n; i++)
	{
		for (int j = 0; j<g.n ;j++)
		{
			fscanf(f,"%d", &g.a[i][j]);
		}
	}
	fclose(f);
	return 1;
}
void OutputMatrix(GRAPH g)
{
	printf("\nthe adjacency matrix of the graph is: \n");
	for(int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
		{
			printf("%d\t",g.a[i][j]);
		}
		printf("\n");
	}
}
int ValidityCheck(GRAPH g)
{
	for (int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
		{
			 if(g.a[i][i]!=0)
			 {
			 	return 0;
			 }
		}
	}
	return 1;
}
void khoitaoStack (STACK &stack)
{
	stack.size = 0;
}
void DayGiaTriVaoStack (STACK &stack, int value)
{
	if(stack.size + 1 >= 100){
		return; 
	}
	stack.array[stack.size] = value;
	stack.size++;
}
void TimDuongDi (GRAPH &g, STACK &stack, int i){
	for (int j = 0; j < g.n; j++)
	{
		if (g.a[i][j] != 0)
		{
			g.a[i][j] = g.a[j][i] =0; 
			TimDuongDi(g,stack,j);
		}
	}
	DayGiaTriVaoStack(stack,i);
}

int KiemTraChuTrinhEuler (GRAPH g)
{
	int i,j;
	int x = 0;
	int flag = 0;
	for (i = 0; i < g.n; i++) { 
		for (j = 0; j < g.n; j++) {
			if (g.a[i][j] != 0){
				x = i;
				flag = 1;
				break;
			}
		}
		if(flag==1)
		break;
	}
	GRAPH temp = g;
	STACK stack;
	khoitaoStack(stack);
	TimDuongDi(temp, stack, x);
	for (i = 0; i < temp.n; i++){ 
		for (j = 0; j < temp.n; j++){ 
			if (temp.a[i][j] != 0) 
			return 0;
		} 
	}
	if (stack.array[stack.size - 1] != stack.array[0])
		return 0; 
	printf("\nChu trinh Euler: ");	
	for(i = stack.size - 1; i >= 0 ; i--) 
	printf("%d ",stack.array[i] + 1); 
	return 1;
}

int KiemTraDuongDiEuler (GRAPH g) {
	int i,j; 
	int x = 0;
	int flag = 0; 
	int bac = 0; 
	for (i = 0; i < g.n; i++){ 
		bac = 0; 
		for (j = 0; j < g.n; j++){ 
			if (g.a[i][j] != 0){
				bac++;
			} 
		}
		if (bac%2 != 0){
			x = i;
			flag = 1;
			break;
		}
	}
	if(flag == 0)
		return 0;	
	GRAPH temp = g;
	STACK stack;
	khoitaoStack (stack);	
	TimDuongDi(temp, stack,x);
	for (i = 0; i < temp.n; i++){ 
		for (j = 0; j < temp.n; j++){
			if(temp.a[i][j]!=0)
			return 0;
		}
	}
	if (stack.array[stack.size - 1] == stack.array[0])
		return 0;	 
	printf("\nDuong di Euler : ");	
	for(i = stack.size - 1; i >= 0 ; i--)
	printf("%d ",stack.array[i] + 1); 
	return 1;
}

int main()
{
	GRAPH g;
	if(ReadMatrix(inputLink,g)==1)
	{
		printf("Retrieved graph information form file successfully \n");
		OutputMatrix(g);
		if(ValidityCheck(g)==1)
		{
			printf("\nThe graph is valid \n");
			if (!KiemTraChuTrinhEuler(g))
			{
				printf("Khong co chu trinh Euler trong do thi cua ban\n");
				printf("\nBam 1 phim bat ki de bat dau xet tim duong di euler ...\n");
			}
			if (!KiemTraDuongDiEuler(g))
			{
				printf("\nKhong co duong di Euler trong do thi cua ban \n");
			}
		}
		else
		{
			printf("\nThe graph is invalid\n");
		}
		getch();
		return 1;
	}
}
