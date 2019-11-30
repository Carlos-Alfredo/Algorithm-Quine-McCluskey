#include <stdio.h>
#include <string.h>
#include <math.h>

const char variaveis[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

int power(int base,int expoente){
  	int resposta=1;
  	for(int i=0;i<expoente;i++){
    	resposta=resposta*base;
  	}
  	return resposta;
}
//anexa o vetor 2 ao vetor 1(vetores de inteiros)
void append_int(int vetor1[],int vetor2[],int len_vetor1,int len_vetor2){
	for(int i=0;i<len_vetor2;i++){
    	vetor1[len_vetor1+i]=vetor2[i];
	}
}
//retorna o numero de caracteres de uma string
int len_string(char string[]){
  	int len=0;
  	while(string[len]!='\0'){
    	len++;
  	}
  	return len;
}
//copia a string_raiz para string
void string_copy(char string_raiz[],char string[]){
  	for(int i=0;i<=len_string(string_raiz);i++){
    	string[i]=string_raiz[i];
  	}
}
//anexa a string 2 à string 1
void append_string(char vetor1[],char vetor2[]){
  	int len_vetor1=len_string(vetor1);
  	int len_vetor2=len_string(vetor2);
  	for(int i=0;i<len_vetor2;i++){
    	vetor1[len_vetor1+i]=vetor2[i];
  	}
 	vetor1[len_vetor1+len_vetor2]='\0';
}
//inverte uma string
void inverter_string(char string[],int len_string){
  	char aux;
  	for(int i=0;i<len_string/2;i++){
    	aux=string[i];
    	string[i]=string[len_string-i-1];
    	string[len_string-i-1]=aux;
  	}
}
int buscar_string(char string_raiz[],char string_elemento[]){
	int achou;
	int len_raiz=len_string(string_raiz);
	int len_elemento=len_string(string_elemento);
	for(int i=0;i<len_raiz-len_elemento;i++){
		achou=1;
		for(int k=0;k<len_elemento;k++){
			if(string_raiz[k+i]!=string_elemento[k]){
				achou=0;
			}
		}
		if(achou==1){
			return 1;
		}
	}
	return 0;
}
//converte decimal para binario e guarda a resposta no vetor desejado
void dec2bin(int decimal,char binario[],int n){
  	for(int i=0;i<n;i++){
    	binario[i]='0'+decimal%2;
    	decimal=decimal/2;
  	}
  	inverter_string(binario,n);
  	binario[n]='\0';
}
//retorna -1 caso nao haja simplificacao, caso contrario retorna a posicao da simplificacao
int posicao_simplificar(char entrada1[],char entrada2[]){
  	int len1=len_string(entrada1);
  	int len2=len_string(entrada2);
  	if(len1!=len2){
    	return -1;
  	}
  	int numero_diferencas=0;
  	int indice=0;
  	for(int i=0;i<len1;i++){
    	if(entrada1[i]!=entrada2[i]){
     	numero_diferencas++;
      	indice=i;
    	}
  	}
  	if(numero_diferencas==1){
    	return indice;
  	}
  	else{
    	return -1;
  	}
}
//coloca a combinacao de input1 e input2 em resposta, caso haja combinacao retorna 1, caso contrario retorna 0
int combinar(char input1[],char input2[],char resposta[]){
  	int posicao=posicao_simplificar(input1,input2);
  	if(posicao==-1){
    	return 0;
  	}
  	else{
    	string_copy(input1,resposta);
    	resposta[posicao]='-';
    	return 1;
  	}
	return 0;
}
//Traduz o termo da forma numerica para a forma booleana
void traduzir(char numerico[],char booleano[]){
  	int len=len_string(numerico);
  	int indice=0;
  	for(int i=0;i<len;i++){
    	if(numerico[i]=='1' || numerico[i]=='0'){
      	booleano[indice]=variaveis[i];
      	indice++;
      		if(numerico[i]=='0'){
        		booleano[indice]='`';
        		indice++;
      		}
    	}
  	}
  	booleano[indice]='\0';
}
//cria um vetor com as entradas do algoritmo de Quine-McCluskey
void gerar_entradas(int tabela_verdade[],int tam_tabela,char entradas[],int n){
  	entradas[0]='\0';
  	char binario[100];
  	for(int i=0;i<tam_tabela;i++){
    	if(tabela_verdade[i]==1){
      	dec2bin(i,binario,n);
      	append_string(binario,"/");
      	append_string(entradas,binario);
   	 	}
  	}
}
//vai escrever a entrada que representa o indice escolhido no vetor retorno, caso as entradas tenham acabado retorna 0, senao retorna 1
int elemento_entrada(char entradas[],int indice,char retorno[]){
  	int i=0;
  	int aux=0;
  	while(aux!=indice && entradas[i]!='\0'){
    	if(entradas[i]=='/'){
      		aux++;
    	}
    	i++;
  	}
  	if(entradas[i]=='\0'){
    	return 0;
  	}
  	int k=0;
  	retorno[0]='\0';
  	while(entradas[i+k]!='/' && entradas[i+k]!='\0'){
    	retorno[k]=entradas[i+k];
    	k++;
  	}
  	retorno[k]='\0';
  	if(entradas[i+k]=='\0'){
    	return 0;
  	}
  	else{
    	return 1;
  	}
}
//recebe as entradas e escreve a simplificacao em solucao
void AlgoritmoQM(char entradas[],char entradas_futuras[],char solucao[],int n){
  	entradas_futuras[0]='\0';
  	int indice=0;
  	char input1[n+2];
  	char input2[n+2];
  	char simplificacao[n+2];
  	int aux1,aux2,aux3,k,combina;
  	aux1=elemento_entrada(entradas,indice,input1);
  	while(aux1){
    	k=0;
    	combina=0;
    	aux2=elemento_entrada(entradas,k,input2);
    	while(aux2){
    		aux3=combinar(input1,input2,simplificacao);
      		if(aux3){
        		combina=1;
        		if(buscar_string(entradas_futuras,simplificacao)==0){
          			append_string(entradas_futuras,simplificacao);
          			append_string(entradas_futuras,"/");
        		}
      		}
      		k++;
      		aux2=elemento_entrada(entradas,k,input2);
    	}
    	if(combina==0 && buscar_string(solucao,input1)==0){
      		append_string(solucao,input1);
      		append_string(solucao,"/");
    	}
    	indice++;
    	aux1=elemento_entrada(entradas,indice,input1);
  	}
  	if(len_string(entradas_futuras)){
    	AlgoritmoQM(entradas_futuras,entradas,solucao,n);
  	}
}
void traduzir_solucao(char solucao[],char solucao_traduzida[],int n){
  	int aux1,indice;
  	char termo_traduzido[2*n+2];
  	char termo_numerico[n+2];
  	solucao_traduzida[0]='\0';
  	indice=0;
  	while(elemento_entrada(solucao,indice,termo_numerico)==1){
    	traduzir(termo_numerico,termo_traduzido);
    	append_string(termo_traduzido,"+");
    	append_string(solucao_traduzida,termo_traduzido);
    	indice++;
  	}
  	solucao_traduzida[len_string(solucao_traduzida)-1]='\0';
}

void simplificar_tabela(int tabela_verdade[],char retorno[],int n){
	char entradas[(n+1)*power(2,n)];
	entradas[0]='\0';
	char entradas_futuras[(n+1)*power(2,n)];
	gerar_entradas(tabela_verdade,power(2,n),entradas,n);
	char solucao[(n+1)*power(2,n)];
	solucao[0]='\0';
	AlgoritmoQM(entradas,entradas_futuras,solucao,n);
	retorno[0]='\0';
	traduzir_solucao(solucao,retorno,n);
}

int main(void) {
  	int tabela_verdade[64]={0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1};
  	int n_variaveis_max=6;
  	char retorno[(n_variaveis_max+1)*power(2,n_variaveis_max)];
  	retorno[0]='\0';
  	simplificar_tabela(tabela_verdade,retorno,n_variaveis_max);
  	printf("%s\n",retorno);
	return 0;
}
