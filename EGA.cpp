# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <iomanip>
# include <cmath>
# include <ctime>
# include <cstring>
#include<cstdio>
using namespace std;
// 
//  Change any of these parameters to match your needs 
//
# define POPSIZE 5
# define MAXGENS 5
//# define NVARS 3
# define MAXPARS 5
# define PXOVER 0.5
# define PMUTATION 0.5
//
//  Each GENOTYPE is a member of the population, with
//  gene: a string of variables,
//  fitness: the fitness
//  upper: the variable upper bounds,
//  lower: the variable lower bounds,
//  rfitness: the relative fitness,
//  cfitness: the cumulative fitness.
//
struct genotype
{
  double gene[MAXPARS];
  double fitness;
  double upper[MAXPARS];
  double lower[MAXPARS];
  double rfitness;
  double cfitness;
};

struct genotype population[POPSIZE+1];
struct genotype newpopulation[POPSIZE+1]; 
struct genotype glob[2*POPSIZE+1];

void crossover ( );
void elitist ( );
void evaluate ( );
void initialize ( string file_in_name );
void keep_the_best ( );
int main ( );
void mutate ( );
void r8_swap ( double *, double * );
double randval ( double, double );
void report ( int generation );
void selector ( );
void timestamp ( );
void Xover ( int, int );
void func();
int string_to_int(string);
//****************************************************************************80

int NVARS;
int send[POPSIZE][10];
int mutascore[POPSIZE];
double array_avg[MAXGENS];
double array_best_val[MAXGENS];
double array_stddev[MAXGENS];
int table_count=0;  


int main ( )

//****************************************************************************80
//
//  Purpose:
//
//    MAIN supervises the genetic algorithm.
//
//  Discussion:
//
//    Each generation involves selecting the best 
//    members, performing crossover & mutation and then 
//    evaluating the resulting population, until the terminating 
//    condition is satisfied   
//
//    This is a simple genetic algorithm implementation where the 
//    evaluation function takes positive values only and the 
//    fitness of an individual is the same as the value of the 
//    objective function.  
//
//  Modified:
//
//    29 December 2007
//
//  Parameters:
//
//    MAXGENS is the maximum number of generations.
//
//    NVARS is the number of problem variables.
//
//    PMUTATION is the probability of mutation.
//
//    POPSIZE is the population size. 
//
//    PXOVER is the probability of crossover.                          
//
{
  int generation;
  int i;
  cout << "\n";
  cout << "  Start of genetic algorithm.\n\n";
  
  cout << "Enter the Number of Parameters\n";
  cin>>NVARS;
cout<<"\n\t\tTable No - 1 (all test cases)\n\n";
cout<<"  Test case         Killed mutants   Total Mutants  Mutation Score\n";
  initialize ( "simple_ga_input" );

  evaluate ( );

  keep_the_best () ;

  for ( generation =  0; generation < MAXGENS; generation++ )
  {
    selector ( );
    crossover ( );
    mutate ( );
    report ( generation );
    evaluate ( );
    elitist ( );
  }

//return here final population

  FILE *fp,*fp1;
	
	fp=fopen("population","w");
	fp1=fopen("best_members","w");
	
	int j;
	for(i=0;i<POPSIZE;i++)
	{
	for(j=0;j<NVARS;j++)
	{
	fprintf(fp,"%d ",(int)glob[i].gene[j]);		
	fprintf(fp1,"%d ",(int)glob[i].gene[j]);		
	}
	fprintf(fp1,"\tmutation score = %d\n",(int)glob[i].fitness);
	fprintf(fp,"\n");
	}
	fclose(fp);
	fclose(fp1);
cout<<"\n\n\t\tTable No - 2 (best members)\n\n";
cout<<"  Test case         Killed mutants   Total Mutants  Mutation Score\n";


	system("bash ms_compute1.sh");

  cout << "\nSimulation completed.\n";

  cout << "\n";
getchar();
  return 0;
}
//****************************************************************************80

void crossover ( )

//****************************************************************************80
// 
//  Purpose:
//
//    CROSSOVER selects two parents for the single point crossover.
//
//  Modified:
//
//    29 December 2007
//
//  Local parameters:
//
//    Local, int FIRST, is a count of the number of members chosen.
//
{
  int mem;
  int one;
  int first = 0;
  double x;

  for ( mem = 0; mem < POPSIZE; ++mem )
  {
    x = ( rand ( ) % 1000 ) / 1000.0;

    if ( x < PXOVER )
    {
      ++first;

      if ( first % 2 == 0 )
      {
        Xover ( one, mem );
      }
      else
      {
        one = mem;
      }

    }
  }
  return;
}
//****************************************************************************80

void elitist ( )

//****************************************************************************80
// 
//  Purpose:
//
//    ELITIST stores the best member of the previous generation.
//
//  Discussion:
//
//    The best member of the previous generation is stored as 
//    the last in the array. If the best member of the current 
//    generation is worse then the best member of the previous 
//    generation, the latter one would replace the worst member 
//    of the current population.
//
//  Modified:
//
//    29 December 2007
//
//  Local parameters:
//
//    Local, double BEST, the best fitness value.
//
//    Local, double WORST, the worst fitness value.
//
{
  int i;
  double best;
  int best_mem;
  double worst;
  int worst_mem;

  best = population[0].fitness;
  worst = population[0].fitness;

  for ( i = 0; i < POPSIZE - 1; ++i )
  {
    if ( population[i].fitness > population[i+1].fitness )
    {

      if ( best <= population[i].fitness )
      {
        best = population[i].fitness;
        best_mem = i;
      }

      if ( population[i+1].fitness <= worst )
      {
        worst = population[i+1].fitness;
        worst_mem = i + 1;
      }

    }
    else
    {

      if ( population[i].fitness <= worst )
      {
        worst = population[i].fitness;
        worst_mem = i;
      }

      if ( best <= population[i+1].fitness )
      {
        best = population[i+1].fitness;
        best_mem = i + 1;
      }

    }

  }
// 
//  If the best individual from the new population is better than 
//  the best individual from the previous population, then 
//  copy the best from the new population; else replace the 
//  worst individual from the current population with the 
//  best one from the previous generation                     
//
  if ( best >= population[POPSIZE].fitness )
  {
    for ( i = 0; i < NVARS; i++ )
    {
      population[POPSIZE].gene[i] = population[best_mem].gene[i];
    }
    population[POPSIZE].fitness = population[best_mem].fitness;
  }
  else
  {
    for ( i = 0; i < NVARS; i++ )
    {
      population[worst_mem].gene[i] = population[POPSIZE].gene[i];
    }
    population[worst_mem].fitness = population[POPSIZE].fitness;
  } 

  return;

}
//****************************************************************************80

void evaluate ( )

//****************************************************************************80
// 
//  Purpose:
//
//    EVALUATE implements the user-defined valuation function
//
//  Discussion:
//
//    Each time this is changed, the code has to be recompiled.
//    The current function is:  x[1]^2-x[1]*x[2]+x[3]
//
//  Modified:
//
//    29 December 2007
//
{
  int member;
  int i;

/*  double x[NVARS+1];

  for ( member = 0; member < POPSIZE; member++ )
  {
    for ( i = 0; i < NVARS; i++ )
    {
      x[i+1] = population[member].gene[i];
    } 
    population[member].fitness = ( x[1] * x[1] ) - ( x[1] * x[2] ) + x[3];
  }
  */

//cout<<"evaluate";
  for ( member = 0; member < POPSIZE; member++ )
  {
    for ( i = 0; i < NVARS; i++ )
    {
        send[member][i]=population[member].gene[i];
//       	cout<<send[member][i]<<endl;
    }
  }
  func();        //recieving the mutation scores computed here
  for ( member = 0; member < POPSIZE; member++ )
  {
      population[member].fitness=mutascore[member];
  }

  for(member=POPSIZE;member<2*POPSIZE;member++)
  {
      glob[member]=population[member-POPSIZE];
  }

  
  
  
  
  
  
  for(int x=0; x<2*POPSIZE; x++)
	{
		for(int y=0; y<2*POPSIZE; y++)
		{
			if(glob[y].fitness < glob[y+1].fitness)
			{
				struct genotype temp = glob[y+1];
				glob[y+1] = glob[y];
				glob[y] = temp;
			}
		}
	}

  
  for(member=0;member<POPSIZE;member++)
  {
      population[member]=glob[member];
  }
  
  
  
  
  
  
  
  

  return;
}
//****************************************************************************80

void initialize ( string file_in_name )

//****************************************************************************80
// 
//  Purpose:
//
//    INITIALIZE initializes the genes within the variables bounds. 
//
//  Discussion:
//
//    It also initializes (to zero) all fitness values for each
//    member of the population. It reads upper and lower bounds 
//    of each variable from the input file `gadata.txt'. It 
//    randomly generates values between these bounds for each 
//    gene of each genotype in the population. The format of 
//    the input file `gadata.txt' is 
//
//      var1_lower_bound var1_upper bound
//      var2_lower_bound var2_upper bound ...
//
//  Modified:
//
//    29 December 2007
//
{
  ifstream file_in;
  int i;
  int j;
  double lbound;
  double ubound;

  file_in.open ( file_in_name.c_str ( ) );

  if ( !file_in )
  {
    cout << "\n";
    cout << "Initialize - Fatal error!\n";
    cout << "  Cannot open the input file!\n";
    exit ( 1 );
  }
// 
//  Initialize variables within the bounds 
//
  for ( i = 0; i < NVARS; i++ )
  {
    file_in >> lbound >> ubound;

    for ( j = 0; j < POPSIZE; j++ )
    {
      population[j].fitness = 0;
      population[j].rfitness = 0;
      population[j].cfitness = 0;
      population[j].lower[i] = lbound;
      population[j].upper[i]= ubound;
      population[j].gene[i] = randval ( population[j].lower[i],population[j].upper[i] );
    }
  }

  file_in.close ( );

  return;
}
//****************************************************************************80

void keep_the_best ( )

//****************************************************************************80
// 
//  Purpose:
//
//    KEEP_THE_BEST keeps track of the best member of the population. 
//
//  Discussion:
//
//    Note that the last entry in the array Population holds a 
//    copy of the best individual.
//
//  Modified:
//
//    29 December 2007
//
//  Local parameters:
//
//    Local, int CUR_BEST, the index of the best individual.
//
{
  int cur_best;
  int mem;
  int i;

  cur_best = 0;

  for ( mem = 0; mem < POPSIZE; mem++ )
  {
    if ( population[mem].fitness > population[POPSIZE].fitness )
    {
      cur_best = mem;
      population[POPSIZE].fitness = population[mem].fitness;
    }
  }
// 
//  Once the best member in the population is found, copy the genes.
//
  for ( i = 0; i < NVARS; i++ )
  {
    population[POPSIZE].gene[i] = population[cur_best].gene[i];
  }

  return;
}
//****************************************************************************80

void mutate ( )

//****************************************************************************80
// 
//  Purpose:
//
//    MUTATE performs a random uniform mutation. 
//
//  Discussion:
//
//    A variable selected for mutation is replaced by a random value 
//    between the lower and upper bounds of this variable.
//
//  Modified:
//
//    29 December 2007
//
{
  double hbound;
  int i;
  int j;
  double lbound;
  double x;

  for ( i = 0; i < POPSIZE; i++ )
  {
    for ( j = 0; j < NVARS; j++ )
    {
      x = rand ( ) % 1000 / 1000.0;
// 
//  Find the bounds on the variable to be mutated 
//
      if ( x < PMUTATION )
      {
        lbound = population[i].lower[j];
        hbound = population[i].upper[j];  
        population[i].gene[j] = randval ( lbound, hbound );
      }
    }
  }

  return;
}
//****************************************************************************80

void r8_swap ( double *x, double *y )

//****************************************************************************80
// 
//  Purpose:
//
//    R8_SWAP swaps two R8's. 
//
//  Modified:
//
//    29 December 2007
//
{
  double temp;

  temp = *x;
  *x = *y;
  *y = temp;

  return;
}
//****************************************************************************80

double randval ( double low, double high )

//****************************************************************************80
// 
//  Purpose:
//
//    RANDVAL generates a random value within bounds.
//
//  Modified:
//
//    29 December 2007
//
{
  double val;

  val = ( ( double ) ( rand() % 1000 ) / 1000.0 ) 
    * ( high - low ) + low;

  return ( val );
}
//****************************************************************************80

void report ( int generation )

//****************************************************************************80
// 
//  Purpose:
//
//    REPORT reports progress of the simulation. 
//
//  Modified:
//
//    29 December 2007
//
//  Local parameters:
//
//    Local, double avg, the average population fitness.
//
//    Local, best_val, the best population fitness.
//
//    Local, double square_sum, square of sum for std calc.
//
//    Local, double stddev, standard deviation of population fitness.
//
//    Local, double sum, the total population fitness.
//
//    Local, double sum_square, sum of squares for std calc.
//
{
  double avg;
  double best_val;
  double stddev;
  int i;
  double square_sum;
  double sum;
  double sum_square;

  sum = 0.0;
  sum_square = 0.0;

  for ( i = 0; i < POPSIZE; i++ )
  {
    sum = sum + population[i].fitness;
    sum_square = sum_square + population[i].fitness * population[i].fitness;
  }

  array_avg[table_count] = sum / ( double ) POPSIZE;
  
  square_sum = array_avg[table_count]*array_avg[table_count] * POPSIZE;
  
  array_stddev[table_count] = sqrt ( ( sum_square - square_sum ) / ( POPSIZE - 1 ) );
  
  array_best_val[table_count] = population[POPSIZE].fitness;

table_count++;
  return;
}
//****************************************************************************80

void selector ( )

//****************************************************************************80
// 
//  Purpose:
//
//    SELECTOR is the selection function.
//
//  Discussion:
//
//    Standard proportional selection for
//    maximization problems incorporating elitist model - makes
//    sure that the best member survives
//
//  Modified:
//
//    29 December 2007
//
{
  int i;
  int j;
  int mem;
  double p;
  double sum = 0;
//
//  Find total fitness of the population 
//
  for ( mem = 0; mem < POPSIZE; mem++ )
  {
    sum = sum + population[mem].fitness;
  }
//
//  Calculate the relative fitness.
//
  for ( mem = 0; mem < POPSIZE; mem++ )
  {
    population[mem].rfitness = population[mem].fitness / sum;
  }
  population[0].cfitness = population[0].rfitness;
// 
//  Calculate the cumulative fitness.
//
  for ( mem = 1; mem < POPSIZE; mem++ )
  {
    population[mem].cfitness = population[mem-1].cfitness + population[mem].rfitness;
  }
// 
//  Select survivors using cumulative fitness. 
//
  for ( i = 0; i < POPSIZE; i++ )
  { 
    p = rand() % 1000 / 1000.0;
    if (p < population[0].cfitness)
    {
      newpopulation[i] = population[0];      
    }
    else
    {
      for ( j = 0; j < POPSIZE; j++ )
      { 
        if ( p >= population[j].cfitness && p < population[j+1].cfitness )
        {
          newpopulation[i] = population[j+1];
        }
      }
    }
  }
// 
//  Once a new population is created, copy it back 
//




  for ( i = 0; i < POPSIZE; i++ )
  {
    glob[i]=population[i];
  }







  for ( i = 0; i < POPSIZE; i++ )
  {
    population[i] = newpopulation[i]; 
  }

  return;     
}
//****************************************************************************80

void timestamp ( )

//****************************************************************************80
//
//  Purpose:
//
//    TIMESTAMP prints the current YMDHMS date as a time stamp.
//
//  Example:
//
//    May 31 2001 09:45:54 AM
//
//  Modified:
//
//    04 October 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    None
//
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  size_t len;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  len = strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  cout << time_buffer << "\n";

  return;
# undef TIME_SIZE
}
//****************************************************************************80

void Xover ( int one, int two )

//****************************************************************************80
// 
//  Purpose:
//
//    XOVER performs crossover of the two selected parents. 
//
//  Modified:
//
//    29 December 2007
//
//  Local parameters:
//
//    Local, int point, the crossover point.
//
{
  int i;
  int point;
// 
//  Select the crossover point.
//
  if ( 1 < NVARS )
  {

    if ( NVARS == 2 )
    {
      point = 1;
    }
    else
    {
      point = ( rand ( ) % ( NVARS - 1 ) ) + 1;
    }

    for ( i = 0; i < point; i++ )
    {
      r8_swap ( &population[one].gene[i], &population[two].gene[i] );
    }

  }
  return;
}



void printarray()
{
int e,f;
	for(e=0;e<POPSIZE;e++)
	{
		for(f=0;f<NVARS;f++)
		printf("%d ",send[e][f]);
		printf("\n");
	}
	return;
}



void func()
{

//	printarray();
	int i=0,j=0;
	char delim='\n';
	ifstream fin;
	ofstream fout;
	fout.open("testcase_input");
	string output;
	for(i=0;i<POPSIZE;i++)
	{
	
		for(j=0;j<NVARS;j++)
		{
			//cout<<send[i][j];
			fout<<send[i][j]<<" ";
		}
		fout<<"\n";
	//	cout<<"\n";
	}
	i=0;
	fout.close();
	system("bash ms_compute.sh");
	//system("ls -l");
	
	
	
	
	

	
	
	
	fin.open("Mutation_Score");
	if(!fin.good())
	{
	cout<<"file opening error\n";
	exit(0);
	}
	
	while(!fin.eof())
	{
	
		getline(fin,output,delim);
		mutascore[i++]=string_to_int(output);
	}
	fin.close();
}

int string_to_int(string output)
{
	int l=2;
	int a=0;
	int i=0;

	while(l--)
	{
		a=a*10+output[i++]-48;
	}
	return a;
}





