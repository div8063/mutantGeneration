# include <cstdlib>
# include <iostream>
# include <fstream>
# include <cmath>
# include <cstring>
# include <cstdio>
using namespace std;
int universal[1000];

int main()
{
	int arr[20][1000];

	int i=0,j=0,k=0,x=0;
	char c=0;
	FILE *fp;
	
	fp=fopen("kill_mat","r");	
	
	while(c!=EOF)
	{
		c=fgetc(fp);
		if(c=='1')
			arr[i][j++]=1;
		else if(c=='0')
			arr[i][j++]=0;	
		else if (c=='\n')
		{
			i++;k=j;j=0;
		}
	}
	
	for(x=0;x<i;x++)
	{
		int flag =0;
		for(j=0;j<k;j++)
		{
			if(arr[x][j]==1 && universal[j]==0)
				flag=1;
			if(flag==1)
				universal[j]|=arr[x][j];
		}
		if (flag==1)
			cout<<"result includes "<<x+1<<"th testcase\n";
	}
	return 0;
}
