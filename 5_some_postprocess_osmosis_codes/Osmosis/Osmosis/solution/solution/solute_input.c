// write salt water input
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#define Max  20000
main()
{
	FILE *fp1,*fp2;
	int i1,i2,i3,i4;
	float f1,f2,f3,f4,xlo=0.0,xhi=30.0,ylo=0.0,yhi=30.0,zlo=0.0,zhi=60;//thickness;
	int i;
	int atomtype1=4,bondtype1=1,angletype1=1;
	int water_num,NaCl_num;
	int bond[Max][2],angle[Max][3];
	float qH=0.4238,qO=-0.8476,qNa=1,qCl=-1;
	float water[3][3]={{1,1,1},{1.8637,1,0.4960},{0.1363,1,0.4960}},ion[2][3]={{5.6,5.6,5.6},{9.6,9.6,9.6}};
	char *ch,*temp1,*temp2,*temp3;
	ch=(char *)malloc(500);
	temp1=(char *)malloc(500);
	temp2=(char *)malloc(500);
	temp3=(char *)malloc(500);
	//fp1——>水分子文件  fp2——>石墨烯文件
	printf("input water molecule number\n");
	scanf("%d",&water_num);
	printf("input NaCl pair number \n");
	scanf("%d",&NaCl_num);
	if((fp1=fopen("all.data","w"))!=NULL&&(fp2=fopen("abc","r"))!=NULL)
	{
		do 
		{
			fscanf(fp2,"%s",ch); 

		} while (strcmp(ch,"Atoms"));

		fputs("\n",fp1);
		fprintf(fp1,"%8d%catoms\n",3*water_num+2*NaCl_num,32);
		fprintf(fp1,"%8d%cbonds\n",2*water_num,32);
		fprintf(fp1,"%8d%cangles\n",water_num,32);
		fprintf(fp1,"%8d%catom%ctypes\n",atomtype1,32,32);
		fprintf(fp1,"%8d%cbond%ctypes\n",bondtype1,32,32);
		fprintf(fp1,"%8d%cangle%ctypes\n",angletype1,32,32);
		fputs("\n",fp1);

		fprintf(fp1,"%12.4f%12.4f%cxlo%cxhi\n",xlo,xhi,32,32);
		fprintf(fp1,"%12.4f%12.4f%cylo%cyhi\n",ylo,yhi,32,32);
		fprintf(fp1,"%12.4f%12.4f%czlo%czhi\n",zlo,zhi,32,32);

		fputs("\n Masses\n",fp1);
		fputs("\n 1  1.007940\n",fp1);//H
		fputs(" 2 15.999400\n",fp1);//O
		fputs(" 3 22.989771\n",fp1);//Na
		fputs(" 4 35.452999\n",fp1);//Cl
		fprintf(fp1,"\nAtoms\n\n");
		for (i=0;i<water_num;i++)
		{
			fscanf(fp2,"%d%d%d%f%f%f%f%s%s%s",&i1,&i2,&i3,&f1,&f2,&f3,&f4,temp1,temp2,temp3);
fprintf(fp1,"%8d%8d%8d%12.4f%12.4f%12.4f%12.4f\n",3*i+1+2790,i+1+2,4,qO,f2-15,f3,f4+0.3);
			//fprintf(fp1,"%8d%8d%8d%12.4f%12.4f%12.4f%12.4f\n",3*i+1,i+1,2,qO,f2,f3,f4);
			fscanf(fp2,"%d%d%d%f%f%f%f%s%s%s",&i1,&i2,&i3,&f1,&f2,&f3,&f4,temp1,temp2,temp3);
fprintf(fp1,"%8d%8d%8d%12.4f%12.4f%12.4f%12.4f\n",3*i+2+2790,i+1+2,5,qH,f2-15,f3,f4+0.3);
			//fprintf(fp1,"%8d%8d%8d%12.4f%12.4f%12.4f%12.4f\n",3*i+2,i+1,1,qH,f2,f3,f4);
			fscanf(fp2,"%d%d%d%f%f%f%f%s%s%s",&i1,&i2,&i3,&f1,&f2,&f3,&f4,temp1,temp2,temp3);
fprintf(fp1,"%8d%8d%8d%12.4f%12.4f%12.4f%12.4f\n",3*i+3+2790,i+1+2,5,qH,f2-15,f3,f4+0.3);
			//fprintf(fp1,"%8d%8d%8d%12.4f%12.4f%12.4f%12.4f\n",3*i+3,i+1,1,qH,f2,f3,f4);
		}
		if (NaCl_num!=0)
		{
			do 
			{
				fscanf(fp2,"%s",ch); 

			} while (strcmp(ch,"SOD"));
			fgets(ch,500,fp2);
		}
		for (i=0;i<NaCl_num;i++)
		{
			fscanf(fp2,"%d%d%d%f%f%f%f%s%s%s",&i1,&i2,&i3,&f1,&f2,&f3,&f4,temp1,temp2,temp3);
			fprintf(fp1,"%8d%8d%8d%12.4f%12.4f%12.4f%12.4f\n",3*water_num+2*i+1,2*i+1+water_num,3,qNa,f2,f3,f4);
			fscanf(fp2,"%d%d%d%f%f%f%f%s%s%s",&i1,&i2,&i3,&f1,&f2,&f3,&f4,temp1,temp2,temp3);
			fprintf(fp1,"%8d%8d%8d%12.4f%12.4f%12.4f%12.4f\n",3*water_num+2*i+2,2*i+2+water_num,4,qCl,f2,f3,f4);
		}
		fprintf(fp1,"\nBonds\n\n");
		for (i=0;i<water_num;i++)
		{
			fprintf(fp1,"%8d%8d%8d%8d\n",2*i+1,1,3*i+1+2790,3*i+2+2790);
			fprintf(fp1,"%8d%8d%8d%8d\n",2*i+2,1,3*i+1+2790,3*i+3+2790);
			//fprintf(fp1,"%8d%8d%8d%8d\n",2*i+1,1,3*i+1,3*i+2);
			//fprintf(fp1,"%8d%8d%8d%8d\n",2*i+2,1,3*i+1,3*i+3);
		}
		fprintf(fp1,"\nAngles\n\n");
		for (i=0;i<water_num;i++)
		{
fprintf(fp1,"%8d%8d%8d%8d%8d\n",i+1,1,3*i+2+2790,3*i+1+2790,3*i+3+2790);
			//fprintf(fp1,"%8d%8d%8d%8d%8d\n",i+1,1,3*i+2,3*i+1,3*i+3);
		}
		
	}
}