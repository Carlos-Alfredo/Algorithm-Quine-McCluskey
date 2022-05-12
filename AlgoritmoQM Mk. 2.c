#include <stdio.h>

const char variable[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

int power(int base,int expoente){
  	int resposta=1;
  	for(int i=0;i<expoente;i++){
    	resposta=resposta*base;
  	}
  	return resposta;
}
//Returns the index where input1 and input2 can be combined. If there is valid index, returns -1.
//input1,input2 are truth table inputs in base 3. tamanho is the number of "digits" in the inputs.
int position_simplify(int input1,int input2,int size)
{
	int numero_diferencas=0;
	int posicao=0;
	for(int i=0;i<size;i++)
	{
		if(input1%3 != input2%3)
		{
			numero_diferencas++;
			posicao=i;
		}
		input1=input1/3;
		input2=input2/3;
	}
	if(numero_diferencas==1)
	{
		return indice;
	}
	else
	{
		return -1;
	}
}
//Returns the combination between input1 and input2. If there is no valid combination returns -1.
int combine(int input1,int input2,int size)
{
	int posicao=position_simplify(input1,input2,size);
	int aux=0;
	int combinacao=-1;
	if(posicao!=-1)
	{
		aux=power(3,posicao);
		combinacao=(2-(input1/aux)%3)*aux+input1;
	}
	return combinacao;
}

//Traduz o termo da forma numerica para a forma booleana
void number_to_boolean(int input,char boolean[],int size)
{
  	int index=0;
  	int aux=power(3,size-1);
  	for(int i=0;i<size;i++)
  	{
  		if((input/aux)%3!=2)
  		{
  			boolean[index]=variable[i];
  			index++;
  			if((input/aux)%3==0)
  			{
  				boolean[index]='`';
  				index++;
  			}
  		}
  		aux=aux/3;
  	}
  	boolean[index]='\0';
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
void generate_inputs(int truth_table[],int size_table,int inputs[],int number_of_variables)
{
	int pot2=1;
	int pot3=1;
	int aux=0;
	for(int i=0;i<size_table;i++)
	{
		if(truth_table[i]==1)
		{
			pot2=1;
			pot3=1;
			aux=0;
			for(int j=0;j<number_of_variables;j++)
			{
				aux=aux+(((i/pot2)%2)*pot3);
				pot2=pot2*2;
				pot3=pot3*3;
			}

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