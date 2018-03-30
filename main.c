#include <stdio.h>
#include <stdlib.h>

double **readMatrix(int n){
	double **m = (double**)malloc(n * sizeof(double*));

	for(int i=0; i<n; i++){
		m[i] = (double*)malloc(n * sizeof(double));

		printf("Digite os elementos da linha %d, separedos por ENTER:\n", i+1);
		for(int j=0; j<n; j++){
			scanf("%lf", &m[i][j]);
		}
	}

	return m;
}

void printMatrix(double **m, int n){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			printf("%lf ", m[i][j]);
		}
		printf("\n");
	}
}

void iterate(double *old, double **new, double **m, double *b, int n){
	double sumNew = 0, sumOld = 0;

	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++) sumNew += m[i][j]*(*new[j]);
		for(int j=i; j<n; j++) sumOld += m[i][j]*(old[j]);
		*new[i] = (b[i] - sumNew - sumOld)/m[i][i];
		printf("%lf ", *new[i]);
	}
}

int main(int argc, char *argv[]){

	int n, itmax;
	double **m, *b, e, *x1, *x2;

	printf("Dimensao da matriz: ");
	scanf("%d", &n);
	m = readMatrix(n);

	printMatrix(m, n);

	b = (double*)malloc(n*sizeof(double));
	printf("Elementos do vetor b:\n");
	for(int i=0; i<n; i++){
		scanf("%lf", &b[i]);
	}

	printf("Constante real: ");
	scanf("%lf", &e);

	printf("\"itmax\": ");
	scanf("%d", &itmax);

	x1 = (double*)malloc(n*sizeof(double));
	x2 = (double*)malloc(n*sizeof(double));

	for(int i=0; i<n; i++) x1[i] = 0;

	iterate(x1, &x2, m, b, n);

	return 0;
}