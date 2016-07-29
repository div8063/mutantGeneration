#include <stdio.h>
#include<stdlib.h>

void error(char *msg){

  printf("Error - %s.\n", msg);
  exit(2);

}


void output(int out){

  printf("%d\n", out);
  

}


int main(int argc, char **argv){

  int a, b, c;


  if (argc<4)
    error("Not enough arguments");
  else if (argc>4)
    error("Too many arguments");

  a=atoi(argv[1]);
  b=atoi(argv[2]); 
  c=atoi(argv[3]);  

  if (c==0){
    if (a>b)
      c=a-b;
    else if(a<b)
       c=b+a;
    else
        c=1000;
    
    output(c);
    return;
  }


  if (c==1){
    if (a>b)
      c=a/b;
    else if(a<b)
       c=b*a;
    else
        c=2000;

    output(c);
    return;
  }


  c=(a+1)*(b+1);

  output(c);
  return;
}

