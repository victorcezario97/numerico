#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
		sumNew=0; sumOld=0;
		for(int j=0; j<i; j++) sumNew += m[i][j]*((*new)[j]);
		for(int j=i; j<n; j++) sumOld += m[i][j]*(old[j]);
		printf("sumNew: %lf\tsumOld: %lf\n", sumNew, sumOld);
		(*new)[i] = (b[i] - sumNew - sumOld)/m[i][i];
		//printf("-->%lf\n", (*new)[i]);
	}
}

double *subtractVector(double *v1, double *v2, int n){
	double *sub = (double*)malloc(n*sizeof(double));

	for(int i=0; i<n; i++) sub[i] = v1[i] - v2[i];

	return sub;
}

double norm(double *v, int n){
	double max = v[0];

	for(int i=1; i<n; i++) if(fabs(v[i]) > max) max = fabs(v[i]);

	return max;
}

int main(int argc, char *argv[]){

	int n, itmax;
	double **m, *b, e, *x1, *x2, max, *sub;

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

	for(int i=0; i<itmax; i+=2){
		iterate(x1, &x2, m, b, n);
		sub = subtractVector(x1, x2, n);
		max = norm(sub, n);
		if(max <= e){
			printf("Broke 1: %lf\n", max);
			break;
		}
		iterate(x2, &x1, m, b, n);
		for(int j=0; j<n; j++) printf("%lf ", x1[j]);
		max = norm(subtractVector(x1, x2, n), n);
		if(max <= e){
			printf("Broke 2\n");
			break;
		}
	}

	//for(int i=0; i<n; i++) printf("%lf\n", x1[i]);

	return 0;
}