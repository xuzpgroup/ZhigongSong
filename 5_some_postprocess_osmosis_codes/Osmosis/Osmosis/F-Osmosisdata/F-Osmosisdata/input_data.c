#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
main()
{
	FILE *fp1,*fp2,*fp3;
	int i1,i2,i3,i4,i5,i6,molecule;
	int thickness=948,temp=0;
	float f1,f2,f3,f4,xlo=0.0,xhi=0.0,ylo=0.0,yhi=0.0,zlo=0.0,zhi=948.37;//thickness;
	float center_x=18.46,center_y=13.5273;
	int i,numatoms1=0,numatoms2=0,numatoms3=0,numbond1=0,numbond2=0,numbond3=0,numangle1,numangle2,numangle3,numdihedral1,numdihedral2,numdihedral3;
	int atomtype1,atomtype2,atomtype3,bondtype1,bondtype2,bondtype3,angletype1,angletype2,angletype3,dihedraltype1,dihedraltype2,dihedraltype3;

	char *ch,*temp1,*temp2,*temp3;
	ch=(char *)malloc(500);
	temp1=(char *)malloc(500);
	temp2=(char *)malloc(500);
	temp3=(char *)malloc(500);
	//fp1——>水分子文件  fp2——>石墨烯文件
	if((fp1=fopen("D:\\samsung\\forward_osmosis\\size\\solve5mol.data","r"))!=NULL&&(fp2=fopen("D:\\samsung\\forward_osmosis\\size\\F\\graphene_5structureF.data","r"))!=NULL)
	{ 
		fp3=fopen("D:\\samsung\\forward_osmosis\\size\\F\\substage_plate5F.data","w");
		fgets(ch,500,fp1);
		fgets(ch,500,fp2);
		//fscanf(fp1,"%s",ch);
		//fscanf(fp2,"%s",ch);
		fprintf(fp3,"box%8d\n",thickness);
		fscanf(fp1,"%d%s",&numatoms1,ch);
		fscanf(fp2,"%d%s",&numatoms2,ch);
		numatoms3=numatoms1+numatoms2;
		fprintf(fp3,"%8d%catoms\n",numatoms3,32);
		fscanf(fp1,"%d%s",&numbond1,ch);
		fscanf(fp2,"%d%s",&numbond2,ch);
		numbond3=numbond1+numbond2;
		fprintf(fp3,"%8d%cbonds\n",numbond3,32);
		fscanf(fp1,"%d%s",&numangle1,ch);
		fscanf(fp2,"%d%s",&numangle2,ch);
		numangle3=numangle1+numangle2;
		fprintf(fp3,"%8d%cangles\n",numangle3,32);
		numdihedral1=0;
		fscanf(fp2,"%d%s",&numdihedral2,ch);
		numdihedral3=numdihedral1+numdihedral2;
		fprintf(fp3,"%8d%cdihedrals\n",numdihedral3,32);
		//improper
		//type
		fscanf(fp1,"%d",&atomtype1);fgets(ch,500,fp1);
		fgets(ch,500,fp2);
		fscanf(fp2,"%d",&atomtype2);fgets(ch,500,fp2);
		atomtype3=atomtype1+atomtype2;
		fprintf(fp3,"%8d%catom%ctypes\n",atomtype3,32,32);
		fscanf(fp1,"%d",&bondtype1);fgets(ch,500,fp1);
		fscanf(fp2,"%d",&bondtype2);fgets(ch,500,fp2);
		bondtype3=bondtype1+bondtype2;
		fprintf(fp3,"%8d%cbond%ctypes\n",bondtype3,32,32);
		fscanf(fp1,"%d",&angletype1);fgets(ch,500,fp1);
		fscanf(fp2,"%d",&angletype2);fgets(ch,500,fp2);
		angletype3=angletype1+angletype2;
		fprintf(fp3,"%8d%cangle%ctypes\n",angletype3,32,32);
		fscanf(fp1,"%d",&dihedraltype1);fgets(ch,500,fp1);
		fscanf(fp2,"%d",&dihedraltype2);fgets(ch,500,fp2);
		dihedraltype3=dihedraltype1+dihedraltype2;
		fprintf(fp3,"%8d%cdihedral%ctypes\n",dihedraltype3,32,32);

		fprintf(fp3,"%12.4f%12.4f%cxlo%cxhi\n",xlo,xhi,32,32);
		fprintf(fp3,"%12.4f%12.4f%cylo%cyhi\n",ylo,yhi,32,32);
		fprintf(fp3,"%12.4f%12.4f%czlo%czhi\n",zlo,zhi,32,32);

		//atoms
		do 
		{
			fscanf(fp1,"%s",ch);
		} while (abs(strcmp(ch,"Atoms")));
		do 
		{
			fscanf(fp2,"%s",ch); 

		} while (strcmp(ch,"Atoms"));
		//write mass
		fputs("\n Masses\n",fp3);
		fputs("\n 1 1.007940\n",fp3);//H
		fputs(" 2 15.999400\n",fp3);//O
		fputs(" 3 12.0107\n",fp3);//C
		fputs("\n Atoms\n\n",fp3);
		i=0;
		while (i<numatoms1)
		{
			fscanf(fp1,"%d%d%d%f%f%f%f",&i1,&i2,&i3,&f1,&f2,&f3,&f4);
			//i1-atom id i2-molecule id i3-atom type f1-charge f2-x f3-y f4-z

			fprintf(fp3,"%8d%8d%8d%12.5f%12.5f%12.5f%12.5f\n",i1,i2,i3,f1,f2,f3,f4);//modify the atom_ID  水分子层厚度可自调
			i++;
			molecule=i2;
		}
		f1=0.0;
		while (fscanf(fp2,"%d%d%d%f%f%f%f",&i1,&i2,&i3,&f1,&f2,&f3,&f4)&&i<numatoms3)
		{
			fprintf(fp3,"%8d%8d%8d%12.5f%12.5f%12.5f%12.5f\n",i1+numatoms1,i2+molecule,i3+4,f1,f2-4.26,f3,f4);//modify the atom_type 此处原子类型自己调整，
			i++;
			//f1=0.0;
		}
		//bonds
		do 
		{
			fscanf(fp1,"%s",ch);
		} while (abs(strcmp(ch,"Bonds")));
		do 
		{
			fscanf(fp2,"%s",ch); 

		} while (strcmp(ch,"Bonds"));
		fputs("\nBonds\n\n",fp3);
		i=0;
		while (fscanf(fp1,"%d%d%d%d",&i1,&i2,&i3,&i4)&&i<numbond1)
		{
			fprintf(fp3,"%8d%8d%8d%8d\n",i1,i2,i3,i4);//modify the atom_ID
			i++;
		}

		while (fscanf(fp2,"%d%d%d%d",&i1,&i2,&i3,&i4)&&i<numbond3)
		{
			fprintf(fp3,"%8d%8d%8d%8d\n",i1+numbond1,i2+1,i3+numatoms1,i4+numatoms1);//bond type
			//modify the atom_ID and bone type
			i++;				
		}
		//Angles
		do 
		{
			fscanf(fp1,"%s",ch);
		} while (abs(strcmp(ch,"Angles")));
		do 
		{
			fscanf(fp2,"%s",ch); 

		} while (strcmp(ch,"Angles"));
		fputs("\nAngles\n\n",fp3);
		i=0;
		while (fscanf(fp1,"%d%d%d%d%d",&i1,&i2,&i3,&i4,&i5)&&i<numangle1)
		{
			fprintf(fp3,"%8d%8d%8d%8d%8d\n",i1,i2,i3,i4,i5);//modify the atom_ID
			i++;
		}
		while (fscanf(fp2,"%d%d%d%d%d",&i1,&i2,&i3,&i4,&i5)&&i<numangle3)
		{
			fprintf(fp3,"%8d%8d%8d%8d%8d\n",i1+numangle1,i2+1,i3+numatoms1,i4+numatoms1,i5+numatoms1);//angle type
			//modify the atom_ID and angle type
			i++;				
		}
		//dihedral
		fputs("\nDihedrals\n\n",fp3);
		i=0;
		do 
		{
			fscanf(fp2,"%s",ch);
		} while (strcmp(ch,"Dihedrals"));
		//fputs("\nDihedrals\n\n",fp3);
		//i=0;
		while (i<numdihedral3)
		{
			fscanf(fp2,"%d%d%d%d%d%d",&i1,&i2,&i3,&i4,&i5,&i6);
			fprintf(fp3,"%8d%8d%8d%8d%8d%8d\n",i1+numdihedral1,i2,i3+numatoms1,i4+numatoms1,i5+numatoms1,i6+numatoms1);
			//modify the atom_ID and dihedral type
			i++;				
		}
	}
	free(ch);
	free(temp1);
	free(temp2);
	free(temp3);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}