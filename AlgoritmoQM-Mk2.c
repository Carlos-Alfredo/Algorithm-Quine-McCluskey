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
//input1,input2 are truth table inputs in base 3. Number_of_variables is the number of entry variables in the circuit.
int position_simplify(int input1,int input2,int number_of_variables)
{
	int numero_diferencas=0;
	int posicao=0;
	for(int i=0;i<number_of_variables;i++)
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
		return posicao;
	}
	else
	{
		return -1;
	}
}
//Returns the combination between input1 and input2. If there is no valid combination returns -1.
int combine(int input1,int input2,int number_of_variables)
{
	int posicao=position_simplify(input1,input2,number_of_variables);
	int aux=0;
	int combinacao=-1;
	if(posicao!=-1)
	{
		aux=power(3,posicao);
		combinacao=(2-(input1/aux)%3)*aux+input1;
	}
	return combinacao;
}

//Translates a input number to it's boolean form.
//Returns the number of characters
void number_to_boolean(int input,char boolean[],int number_of_variables)
{
  	int index=0;
  	int aux=power(3,number_of_variables-1);
  	for(int i=0;i<number_of_variables;i++)
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
//Creates from the truth table the input vector for the QM Algorithm
//Returns the number of inputs
int generate_inputs(int truth_table[],int size_table,int inputs[],int number_of_variables)
{
	int pot2=1;
	int pot3=1;
	int aux=0;
  int index=0;
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
      inputs[index]=aux;
      index++;
		}
	}
}
//Calculates the minimum solution from the input values and writes them in the soluction vector.
//Returns the number of elements in the solution.
int QMAlgorithm(int inputs[],int number_of_inputs,int solution[],int number_of_variables)
{
  int next_inputs[power(2,number_of_variables-1)*number_of_variables];
  int solution_index=0;
  int aux=0;
  int number_of_combinations=0;
  int next_inputs_index=0;
  while(number_of_inputs>1)
  {
    for(int i=0;i<number_of_inputs-1;i++)
    {
      number_of_combinations=0;
      for(int j=0;j<number_of_inputs-1;j++)
      {
        aux=combine(inputs[i],inputs[j],number_of_variables);
        if(aux!=-1)
        {
          if(j>i)
          {
            next_inputs[next_inputs_index]=aux;
            next_inputs_index++;
          }
          number_of_combinations++;
        }
      }
      if(number_of_combinations==0)
      {
        solution[solution_index]=inputs[i];
        solution_index++;
      }
    }
    for(int i=0;i<next_inputs_index;i++)
    {
      inputs[i]=next_inputs[i];
    }
    number_of_inputs=next_inputs_index;
    next_inputs_index=0;
  }
  if(number_of_inputs==1)
  {
    solution[solution_index]=inputs[0];
    solution_index++;
  }
  return solution_index;
}

void translate_solution(int solution[],int number_of_terms,char translated_solution[],int number_of_variables)
{
  if(number_of_terms==0)
  {
    translated_solution[0]='0';
    translated_solution[1]='\0';
  }
  else if(solution[0]==power(3,number_of_variables)-1)
  {
    translated_solution[0]='1';
    translated_solution[1]='\0';
  }
  else
  {
    char boolean_term[2*number_of_variables+1];
    int translated_index=0;
    int term_index=0;
    translated_solution[0]='\0';
    for(int i=0;i<number_of_terms;i++)
    {
      number_to_boolean(solution[i],boolean_term,number_of_variables);
      term_index=0;
      while(boolean_term[term_index]!='\0')
      {
        translated_solution[translated_index]=boolean_term[term_index];
        translated_index++;
        term_index++;
      }
      translated_solution[translated_index]='+';
      translated_index++;
    }
    translated_solution[translated_index-1]='\0';
  }
}

void circuit_solver(int truth_table[],char equation[],int number_of_variables)
{
  int size_table=power(2,number_of_variables);
  int inputs[size_table];
  int number_of_inputs=0;
  int number_of_terms=0;
  int solution[size_table];
  equation[0]='\0';
  number_of_inputs=generate_inputs(truth_table,size_table,inputs,number_of_variables);
  number_of_terms=QMAlgorithm(inputs,number_of_inputs,solution,number_of_variables);
  translate_solution(solution,number_of_terms,equation,number_of_variables);

}
int main(void) {
  	int tabela_verdade[64]={0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1};
  	int n_variaveis_max=6;
  	char retorno[(n_variaveis_max+1)*power(2,n_variaveis_max)];
  	retorno[0]='\0';
  	circuit_solver(tabela_verdade,retorno,n_variaveis_max);
  	printf("%s\n",retorno);
	return 0;
}
