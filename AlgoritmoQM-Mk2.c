#include <stdio.h>

#define number_of_variables 5

int power(int base,int expoente){
  	int resposta=1;
  	for(int i=0;i<expoente;i++){
    	resposta=resposta*base;
  	}
  	return resposta;
}

//int truth_table[16]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int truth_table[32]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int minterms[32]; //Minterms derivated from the truth table

int inputs[32]; //Starting Prime Implicants at each round of simplification in QM Algorithm

int solution[32]; //Final group of Prime Implicants

char simplified_equation[200]; //String form of solution

const char variable[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};



//Returns the index where input1 and input2 can be combined. If there is valid index, returns -1.
//input1,input2 are truth table inputs in base 3. Number_of_variables is the number of entry variables in the circuit.
int position_simplify(int input1,int input2)
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
int combine(int input1,int input2)
{
	int posicao=position_simplify(input1,input2);
	int aux=0;
	int combinacao=-1;
	if(posicao!=-1)
	{
		aux=power(3,posicao);
		combinacao=(2-(input1/aux)%3)*aux+input1;
	}
	return combinacao;
}

//Checks is input1 contains input2. Returns 1 if true, returns 0 if false.
int contains(int input1, int input2)
{
  int contains=1;
	for(int i=0;i<number_of_variables;i++)
	{
		if((input1%3 != input2%3) && (input1%3!=2))
		{
			contains=0;
		}
		input1=input1/3;
		input2=input2/3;
	}
	return contains;
}


//Translates a input number to it's boolean form.
//Returns the number of characters
void number_to_boolean(int input,char boolean[])
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
//Creates from the truth table the minterms for the QM Algorithm
//Returns the number of inputs
int generate_inputs(int size_table)
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
      minterms[index]=aux;
      index++;
		}
	}
	return index;
}
//From the minterms and prime implicants generates the minimal solution

int minimal_solution(int number_of_minterms,int prime_implicants[],int number_of_prime_implicants)
{
  int aux;
  int solution_index=0;
  int index_last_prime=0;
  int index_min_prime=0;
  int min_primes=-1;
  while(number_of_minterms>0)
  {
    min_primes=-1;
    for(int i=0;i<number_of_minterms;i++)
    {
      aux=0;
      for(int k=0;k<number_of_prime_implicants;k++)
      {
        if(contains(prime_implicants[k],minterms[i]))
        {
          aux++;
          index_last_prime=k;
        }
      }
      if(aux<min_primes || min_primes==-1)
      {
        min_primes=aux;
        index_min_prime=index_last_prime;
      }
    }
    solution[solution_index]=prime_implicants[index_min_prime];
    solution_index++;
    for(int i=number_of_minterms-1;i>=0;i--)
    {
      if(contains(prime_implicants[index_min_prime],minterms[i]))
      {
        minterms[i]=minterms[number_of_minterms-1];
        number_of_minterms--;
      }
    }
    prime_implicants[index_min_prime]=prime_implicants[number_of_prime_implicants-1];
    number_of_prime_implicants--;
  }
  return solution_index;
}
//Calculates the minimum solution from the input values and writes them in the soluction vector.
//Returns the number of elements in the solution.
int QMAlgorithm(int number_of_inputs)
{
  int next_inputs[power(2,number_of_variables-1)*number_of_variables];
  int prime_implicants[power(2,number_of_variables-1)*number_of_variables];
  int prime_index=0;
  int aux=0;
  int repetition=0;
  int number_of_combinations=0;
  int next_inputs_index=0;
  int number_of_minterms=number_of_inputs;
  int n=number_of_inputs;
  for(int i=0;i<number_of_minterms;i++)
  {
    inputs[i]=minterms[i];
  }
  while(n>1)
  {
    for(int i=0;i<n;i++)
    {
      number_of_combinations=0;
      for(int j=0;j<n;j++)
      {
        aux=combine(inputs[i],inputs[j]);
        if(aux!=-1)
        {
          repetition=0;
          for(int k=0;k<next_inputs_index;k++)
          {
            if(next_inputs[k]==aux)
            {
              repetition=1;
            }
          }
          if(repetition==0)
          {
            next_inputs[next_inputs_index]=aux;
            next_inputs_index++;
          }
          number_of_combinations++;
        }
      }
      if(number_of_combinations==0)
      {
        prime_implicants[prime_index]=inputs[i];
        prime_index++;
      }
    }
    for(int i=0;i<next_inputs_index;i++)
    {
      inputs[i]=next_inputs[i];
    }
    n=next_inputs_index;
    next_inputs_index=0;
  }
  if(n==1)
  {
    prime_implicants[prime_index]=inputs[0];
    prime_index++;
  }
  return minimal_solution(number_of_minterms,prime_implicants,prime_index);
}

void translate_solution(int number_of_terms)
{
  if(number_of_terms==0)
  {
    simplified_equation[0]='0';
    simplified_equation[1]='\0';
  }
  else if(solution[0]==power(3,number_of_variables)-1)
  {
    simplified_equation[0]='1';
    simplified_equation[1]='\0';
  }
  else
  {
    char boolean_term[2*number_of_variables+1];
    int translated_index=0;
    int term_index=0;
    simplified_equation[0]='\0';
    for(int i=0;i<number_of_terms;i++)
    {
      number_to_boolean(solution[i],boolean_term);
      term_index=0;
      while(boolean_term[term_index]!='\0')
      {
        simplified_equation[translated_index]=boolean_term[term_index];
        translated_index++;
        term_index++;
      }
      simplified_equation[translated_index]='+';
      translated_index++;
    }
    simplified_equation[translated_index-1]='\0';
  }
}

void circuit_solver(void)
{
  int number_of_inputs=0;
  int number_of_terms=0;
  simplified_equation[0]='\0';
  number_of_inputs=generate_inputs(power(2,number_of_variables));
  number_of_terms=QMAlgorithm(number_of_inputs);
  translate_solution(number_of_terms);
}
int main(void) {
  simplified_equation[0]='\0';
  circuit_solver();
  printf("%s\n",simplified_equation);
	return 0;
}
