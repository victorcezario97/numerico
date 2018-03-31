#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Funcao que le uma matriz de dimensao n da entrada padrao
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

//Funcao que imprime uma matriz de dimensao n
void printMatrix(double **m, int n){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			printf("%lf ", m[i][j]);
		}
		printf("\n");
	}
}

//Funcao que realiza uma iteracao do metodo
void iterate(double *old, double **new, double **m, double *b, int n){
	double sumNew = 0, sumOld = 0;

	for(int i=0; i<n; i++){
		sumNew=0; sumOld=0;
		//Calculando a soma dos valores do vetor X(k+1)
		for(int j=0; j<i; j++) sumNew += m[i][j]*((*new)[j]);
		//Calculando a soma dos valores do vetor X(k)
		for(int j=i+1; j<n; j++) sumOld += m[i][j]*(old[j]);
		(*new)[i] = (b[i] - sumNew - sumOld)/m[i][i];
	}
}

//Funcao que subtrai dois vetores de dimensao n elemento por elemento
double *subtractVector(double *v1, double *v2, int n){
	double *sub = (double*)malloc(n*sizeof(double));

	for(int i=0; i<n; i++) sub[i] = v1[i] - v2[i];

	return sub;
}

//Funcao que retorna a norma infinita de um vetor de dimensao n
double norm(double *v, int n){
	double max = v[0];

	for(int i=1; i<n; i++) if(fabs(v[i]) > max) max = fabs(v[i]);

	return max;
}

double **generateMatrix(int n){
	double **m = (double**)malloc(n*sizeof(double*));
	for(int i=0; i<n; i++) m[i] = (double*)malloc(n*sizeof(double));

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i==j) m[i][j] = 4;
			else if(j == i+1) m[i][j] = -1;
			else if(i == j+1) m[i][j] = -1;
			else if(j == i+3) m[i][j] = -1;
			else if(i == j+3) m[i][j] = -1;
			else m[i][j] = 0;
		}
	}

	return m;
}

int main(int argc, char *argv[]){

	int n, itmax, it, op;
	double **m, *b, e, *x1, *x2, max, *sub;

	printf("Digite 0 para utilizar a matriz definida pelas equacoes de I ou qualquer outro numero para digitar a matriz manualmente:\n");
	scanf("%d", &op);

	//Lendo os valores necessarios
	printf("Dimensao da matriz: ");
	scanf("%d", &n);
	
	if(op == 0) m = generateMatrix(n);
	else m = readMatrix(n);

	printMatrix(m, n);

	b = (double*)malloc(n*sizeof(double));
	printf("Elementos do vetor b:\n");
	for(int i=0; i<n; i++){
		scanf("%lf", &b[i]);
	}

	printf("Constante real: ");
	scanf("%lf", &e);

	printf("Numero maximo de iteracoes: ");
	scanf("%d", &itmax);
	it = itmax;

	//Alocando os vetores que serao usados nas iteracoes
	x1 = (double*)malloc(n*sizeof(double));
	x2 = (double*)malloc(n*sizeof(double));

	//Preenchendo o vetor inicial
	for(int i=0; i<n; i++) x1[i] = 0;

	for(int i=1; i*2<=itmax; i+=2){
		//Uma iteracao calcula o novo vetor X(k+1) e armazena ele em x2 usando o vetor anterior x1(X(k))
		iterate(x1, &x2, m, b, n);

		//Verificando se a norma infinita da diferenca de X(k) e X(k+1) é menor do que a constante real 'e'
		sub = subtractVector(x1, x2, n);
		max = norm(sub, n);
		free(sub);
		if(max <= e){
			it = i*2-1;
			break;
		}

		//Verificando se o numero maximo de iteracoes foi alcancado
		if(i*2 > itmax) break;

		//Uma iteracao calcula o novo vetor X(k+1) e armazena ele em x1 usando o vetor anterior x2(X(k))
		iterate(x2, &x1, m, b, n);

		//Verificando se a norma infinita da diferenca de X(k) e X(k+1) é menor do que a constante real 'e'
		sub = subtractVector(x1, x2, n);
		max = norm(sub, n);
		free(sub);
		if(max <= e){
			it = i*2;
			break;
		}
	}

	//Imprimindo resultados
	printf("\nNumero de iteracoes: %d\n", it);
	for(int i=0; i<n; i++) printf("%lf\n", x1[i]);

	//Liberando alocacoes
	for(int i=0; i<n; i++) free(m[i]);
	free(m);

	free(b);
	free(x1);
	free(x2);

	return 0;
}