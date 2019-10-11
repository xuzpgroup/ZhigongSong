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
	if((fp1=fopen("E:\\samsung\\forward_osmosis\\data\\5mol\\tube\\9\\f_oxide_down.xyz","r"))!=NULL)
	{//D:\\samsung\\forward_osmosis\\data\\plate
		fp3=fopen("E:\\samsung\\forward_osmosis\\data\\5mol\\tube\\9\\f_oxide_up.xyz","r");
		fp2=fopen("E:\\samsung\\forward_osmosis\\data\\5mol\\tube\\Count9","w"); 
		j=0;
		while (j<maxstep)   // something is wrong                                                                                                                                                                                                                              
		{
			count1=0;
			count2=0;
			fscanf(fp1,"%d",&numatom);
			j++;
			//fprintf(fp2,"%8d\n\n",numatom); 			
			//fscanf(fp1,"%s",temp1);//fgets(ch,500,fp1);
			fscanf(fp1,"%s%s%s",temp1,temp2,temp3);
			//fgets(ch,500,fp1);                                                                                                                                                                                                                                                                   
			//fscanf(fp1,"%d",&numatom);fgets(ch,500,fp1);                                                                                                                                                                                                                                         
			//erase box                                                                                                                                                                                                                                                                          
			//fgets(ch,500,fp1);fgets(ch,500,fp1);fgets(ch,500,fp1);fgets(ch,500,fp1);fgets(ch,500,fp1);                                                                                                                                                                                           
			for (i=0;i<numatom;i++)                                                                                                                                                                                                                                                              
			{                                                                                                                                                                                                                                                                                    
				fscanf(fp1,"%d%f%f%f",&atomType,&xu[i],&yu[i],&zu[i]);//fgets(ch,500,fp1);
				if (zu[i]>76)
				{
					count1++;
				}
				//fprintf(fp2,"%4d%12.5f%12.5f%12.5f\n",atomType,xu[i],yu[i],zu[i]);                                                                                                                                                                                      
			}
			fprintf(fp2,"%8d%8d",j,count1);
			fscanf(fp3,"%d",&numatom);
			//fprintf(fp2,"%8d\n\n",numatom); 
			//fscanf(fp3,"%s",temp1);
			fscanf(fp3,"%s%s%s",temp1,temp2,temp3);
			//fgets(ch,500,fp3);                                                                                                                                                                                                                                        
			//fgets(ch,500,fp1);                                                                                                                                                                                                                                                                   
			//fscanf(fp1,"%d",&numatom);fgets(ch,500,fp1);                                                                                                                                                                                                                                         
			//erase box                                                                                                                                                                                                                                                                          
			//fgets(ch,500,fp1);fgets(ch,500,fp1);fgets(ch,500,fp1);fgets(ch,500,fp1);fgets(ch,500,fp1);                                                                                                                                                                                           
			for (i=0;i<numatom;i++)                                                                                                                                                                                                                                                              
			{                                                                                                                                                                                                                                                                                    
				fscanf(fp3,"%d%f%f%f",&atomType,&xu[i],&yu[i],&zu[i]);//fgets(ch,500,fp1);
				if (zu[i]>60)
				{
					count2++;
				}
			}
			fprintf(fp2,"%8d%8d\n",count2,count1+count2);
			//≈≈–Ú
			//for (i=0;i<numatom;i++)
			//{
			//	for (j=i+1;j<numatom;j++)
			//	{
			//		if(atom_ID[i]>atom_ID[j])
			//		{
			//			tempt1=atom_ID[i];temp[0]=vx[i];temp[1]=vy[i];temp[2]=vz[i];
			//			atom_ID[i]=atom_ID[j];vx[i]=vx[j];vy[i]=vy[j];vz[i]=vz[j];
			//			atom_ID[j]=tempt1;vx[j]=temp[0];vy[j]=temp[1];vz[j]=temp[2];
			//		}
			//	}
			//}
			//fprintf(fp2,"%10d",timestep);
			//for (i=0;i<numatom;i++)
			//{
			//fprintf(fp2,"%10d%10d%4d%14.5e%14.5e%14.5e\n",atom_ID[i],timestep,i+1,vx[i],vy[i],vz[i]);
			//	fprintf(fp2,"%14.5e%14.5e%14.5e",vx[i],vy[i],vz[i]);
			//}
			//fprintf(fp2,"\n");
		}
	}
	free(temp1);
	free(temp2);
	free(temp3);
	free(ch);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}