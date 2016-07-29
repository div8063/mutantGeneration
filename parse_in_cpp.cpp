#include <iostream>
#include<cstdlib>
#include<stdlib.h>
using namespace std;
#include<cstdio>
#include<map>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>

string array_of_operator[]={"+","-","*","/","%","<",">","<=",">=","&","|","&&","||","^","<<",">>"};
map<string,int> map_of_oper;
int total_mutant=0,count=1;
ifstream fin,fin1;
ofstream fout;


void muta_gen(int fp,int type,int index)
{
	char ch;
	fin.close();
	char buff[3];char name[15]={"mutant000.c"};
	fp-=1;
	for(int i=0;i<16;i++)
	{
		if(i!=(index-1))
		{
			int x;
			name[8]=count%10+48;
			x=count/10;
			name[7]=x%10+48;
			x=count/100;
			name[6]=x%10+48;
			ofstream muta;
			muta.open(name);
			fin.open("input.c");
			while(fin.tellg()<fp)
			{
				fin.get(ch);
				muta<<ch;
			}
			fin.get(ch);
			if(type)
			fin.get(ch);
			muta<<array_of_operator[i];
			while(!fin.eof())
			{
				fin.get(ch);
				muta<<ch;
			}
			muta.close();
			fin.close();
			count++;
		}
	}


return;
}



int main()
{
	map_of_oper["+"]=1,map_of_oper["-"]=2,map_of_oper["*"]=3,map_of_oper["/"]=4,map_of_oper["%"]=5;
	map_of_oper["<"]=6,map_of_oper[">"]=7,map_of_oper["<="]=8,map_of_oper[">="]=9,map_of_oper["&"]=10;
	map_of_oper["|"]=11,map_of_oper["&&"]=12,map_of_oper["||"]=13,map_of_oper["^"]=14,map_of_oper["<<"]=15,map_of_oper[">>"]=16;
	map<string,int>::iterator it,temp;
  	
  	fin.open("input.c");
  	
  	if (!fin.good()) 
  		return 1;

  	while (!fin.eof())
  	{
 		int i,j,k,l;
 		char ch;
 		fin.get(ch);
		stringstream ss;
		string s;
		ss << ch;
		ss >> s;
		
		if(ch=='#')
			while(ch!='\n')
				fin.get(ch);
		
		it=map_of_oper.find(s);	
 		if(it!=map_of_oper.end())
 		{
	 		int len;
	 		temp=it;
	 		fin.get(ch);
	 		s=s.insert(1,1,ch);
	 		
	 		if((it=map_of_oper.find(s))!=map_of_oper.end())
	 		{
	 			len=fin.tellg();
	 			muta_gen(len-1,1,it->second);
			}
			
			else if(s=="//")
			{
				while(ch!='\n')
					fin.get(ch);
				
				fin.get(ch);
				len=fin.tellg();
				fin.close();
			}
			else if(s=="/*")
			{
				char ch1,ch2;
				char s2[3]="/*";
				while(strcmp(s2,"*/"))
				{
					fin.get(s2[0]);
					fin.get(s2[1]);
				}
				fin.get(ch);
				len=fin.tellg();
				fin.close();
			}
				
			else
	 		{
	 			len=fin.tellg();
	 			fin.seekg(-1,fin.cur);
	 			muta_gen(len-1,0,temp->second);
			}
	 		
	 		fin.open("input.c");
	 		fin.seekg(len,fin.beg);
	 	}
	 	else
	 	{
	 		if(ch=='"')
	 			{
	 				fin.get(ch);
	 				while(ch!='"')
	 					fin.get(ch);
	 			}
	 	}
	}
	fin.close();
}
