#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#define  Max_numatom   50000
main()
{
	// this program is to read data from dump custom file 
	FILE *fp1,*fp2,*fp3;                                                                                                                                                                                                                                                                          
	int i,j,max,timestep=0,numatom=0,maxstep=15000,atomType,tempt1=0; //maxstep ?????
	float xu[Max_numatom],yu[Max_numatom],zu[Max_numatom],temp[3]={0.0};
	char *ch,*temp1,*temp2,*temp3;
	int count1=0,count2=0;
	ch=(char *)malloc(500);
	temp1=(char *)malloc(500);
	temp2=(char *)malloc(500);
	temp3=(char *)malloc(500);
	if((fp1=fopen("E:\\samsung\\forward_osmosis\\data\\5mol\\tube\\9\\f_equil_ions.xyz","r"))!=NULL)
	{//D:\\samsung\\forward_osmosis\\data\\tube\\8\\f_equil_ions3.xyz
		fp2=fopen("E:\\samsung\\forward_osmosis\\data\\5mol\\tube\\Ions_Count9","w"); 
		j=0;
		while (j<maxstep)   // something is wrong                                                                                                                                                                                                                              
		{
			count1=0;
			count2=0;
			fscanf(fp1,"%d",&numatom);
			j++;
			//fscanf(fp1,"%s",temp1);
			fscanf(fp1,"%s%s%s",temp1,temp2,temp3);
			for (i=0;i<numatom;i++)
			{
				fscanf(fp1,"%d%f%f%f",&atomType,&xu[i],&yu[i],&zu[i]);//fgets(ch,500,fp1);
				if (zu[i]>76)
				{
					count1++;
				}
			}
			fprintf(fp2,"%8d%8d\n",j,count1);
		}
	}
	free(temp1);
	free(ch);
	fclose(fp1);
	fclose(fp2);
}