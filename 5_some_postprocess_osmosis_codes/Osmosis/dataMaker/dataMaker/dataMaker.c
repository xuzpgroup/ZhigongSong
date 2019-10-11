#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#define Max_atom  400000

main()
{
	FILE *fp1,*fp2;
	int i=0,j=0,k=0,mol=1,l=0,m=0;
	int natoms=0,nbonds=0,nangls=0,ndihs=0;
	int atomH=0,atomO=0,atomC=0,flagCH=0;
	int bondCC,bondCO,bondOH,angCCO,angCCC,angCOH,dihCCCC,dihCCCO,dihCCOH;
	int ncrds[Max_atom]={0},crd[Max_atom][4]={0};
	int bond[Max_atom][2]={0},angl[Max_atom][3]={0},dih[Max_atom][4]={0};
	float fq=0.0,x[Max_atom][3]={0.0},box[3];
	int flagC[Max_atom]={0};
	float qC=0.0,qCO=0.3568,qO=-0.3568,qH=0,q[Max_atom]={0};
	char *atomname[Max_atom];
	float dr,atommass,dx[3]={0.0},flag=0.0;
	float r0=0,r0CC=1.45,rtol=0.1,r0CO=1.5,r0CH=0,r0OH=1.0;

	if((fp1=fopen("D:\\samsung\\forward_osmosis\\size\\F\\graphene_5structureF.xyz","r"))!=NULL)//只可以有C,H
	{ 
		fp2=fopen("D:\\samsung\\forward_osmosis\\size\\F\\graphene_6structureF.data","w");
		fscanf(fp1,"%d",&natoms);
		for (k=0;k<3;k++)
		{
			fscanf(fp1,"%f",&box[k]);
		}
		//fscanf(fp1,"%s",temp);
		for (i=0;i<natoms;i++)
		{
			atomname[i]=(char *)malloc(2);
			fscanf(fp1,"%s%f%f%f",atomname[i],&x[i][0],&x[i][1],&x[i][2]);
		}
		//find bonds
		for (i=0;i<natoms;i++)
		{
			for (j=i+1;j<natoms;j++)
			{
				for (k=0;k<3;k++)
				{
					dx[k]=x[j][k]-x[i][k];
					flag=dx[k]/box[k];
					if (flag>0.5||flag==0.5)
					{
						dx[k]=dx[k]-box[k];
					}
				}
				dr=sqrt(dx[0]*dx[0]+dx[1]*dx[1]+dx[2]*dx[2]);
				r0=0;
				if ((strcmp(atomname[i],"C")==0)&&(strcmp(atomname[j],"C")==0))
				{
					r0=r0CC;
				} 
				else if ((strcmp(atomname[i],"C")==0)&&(strcmp(atomname[j],"F")==0))
				{
					r0=r0CO;
				} 
				else if ((strcmp(atomname[i],"F")==0)&&(strcmp(atomname[j],"C")==0))
				{
					r0=r0CO;
				} 
				else if ((strcmp(atomname[i],"H")==0)&&(strcmp(atomname[j],"O")==0))
				{
					r0=r0OH;
				}
				else if (strcmp(atomname[i],"O")==0&&strcmp(atomname[j],"H")==0)
				{
					r0=r0OH;
				}
				if (dr>0.00001&&dr<r0+rtol)
				{
					bond[nbonds][0]=i;
					bond[nbonds][1]=j;
					crd[i][ncrds[i]]=j;
					crd[j][ncrds[j]]=i;
					nbonds=nbonds+1;
					ncrds[i]=ncrds[i]+1;
					ncrds[j]=ncrds[j]+1;
					if ((strcmp(atomname[i],"C")==0)&&(strcmp(atomname[j],"C")==0))
					{
						q[i]=qC;
						q[j]=qC;
					}
					else if ((strcmp(atomname[i],"C")==0)&&(strcmp(atomname[j],"F")==0))
					{
						q[i]=qCO;
						q[j]=qO;
					}
					else if ((strcmp(atomname[i],"F")==0)&&(strcmp(atomname[j],"C")==0))
					{
						q[i]=qO;
						q[j]=qCO;
					}
					else if ((strcmp(atomname[i],"H")==0)&&(strcmp(atomname[j],"O")==0))
					{
						q[i]=qH;
						q[j]=qO;
					}
					else if (strcmp(atomname[i],"O")==0&&strcmp(atomname[j],"H")==0)
					{
						q[i]=qO;
						q[j]=qH;
					}
				}
			}
		}
		//find angles
		for (i=0;i<nbonds;i++)
		{
			for (j=i+1;j<nbonds;j++)
			{
				if (bond[i][0]==bond[j][0])
				{
					angl[nangls][0]=bond[i][1];
					angl[nangls][1]=bond[i][0];
					angl[nangls][2]=bond[j][1];
					nangls=nangls+1;
				}
				if (bond[i][0]==bond[j][1])
				{
					angl[nangls][0]=bond[i][1];
					angl[nangls][1]=bond[i][0];
					angl[nangls][2]=bond[j][0];
					nangls=nangls+1;
				}
				if (bond[i][1]==bond[j][0])
				{
					angl[nangls][0]=bond[i][0];
					angl[nangls][1]=bond[i][1];
					angl[nangls][2]=bond[j][1];
					nangls=nangls+1;
				}
				if (bond[i][1]==bond[j][1])
				{
					angl[nangls][0]=bond[i][0];
					angl[nangls][1]=bond[i][1];
					angl[nangls][2]=bond[j][0];
					nangls=nangls+1;
				}
			}
		}
		//find dihedral
		for (i=0;i<natoms;i++)
		{
			for (j=i;j<natoms;j++)
			{
				for (k=0;k<ncrds[i];k++)
				{
					if (crd[i][k]==j)
					{
						for (l=0;l<ncrds[i];l++)
						{
							for (m=0;m<ncrds[j];m++)
							{
								if (crd[i][l]!=j&&crd[j][m]!=i)
								{
									dih[ndihs][0]=crd[i][l];
									dih[ndihs][1]=i;
									dih[ndihs][2]=j;
									dih[ndihs][3]=crd[j][m];
									ndihs=ndihs+1;
								}
							}
						}
					}
				}
			}
		}
		// write data file
		fprintf(fp2,"\n");
		fprintf(fp2,"%8d%catoms\n",natoms,32);
		fprintf(fp2,"%8d%cbonds\n",nbonds,32);
		fprintf(fp2,"%8d%cangles\n",nangls,32);
		fprintf(fp2,"%8d%cdihedrals\n",ndihs,32);
		fprintf(fp2,"\n");
		fprintf(fp2,"%8d%catom%ctypes\n",2,32,32);
		fprintf(fp2,"%8d%cbond%ctypes\n",2,32,32);
		fprintf(fp2,"%8d%cangle%ctypes\n",2,32,32);
		fprintf(fp2,"%8d%cdihedral%ctypes\n",2,32,32);
		fprintf(fp2,"\n");
		//box
		fprintf(fp2,"%8.4f%8.4f%cxlo%cxhi\n",0.0,box[0],32,32);
		fprintf(fp2,"%8.4f%8.4f%cylo%cyhi\n",0.0,box[1],32,32);
		fprintf(fp2,"%8.4f%8.4f%czlo%czhi\n",-20.0,20.0,32,32);
		// Mass
		fprintf(fp2,"\n%cMasses\n\n",32);
		fprintf(fp2,"\n%8d%c12.01070\n",1,32);
		fprintf(fp2,"%8d%c%c1.00794\n",2,32,32);
		// atom
		fprintf(fp2,"\n%cAtoms\n\n",32);
		for (i=0;i<natoms;i++)
		{
			if (strcmp(atomname[i],"C")==0)
			{
				fprintf(fp2,"%8d%4d%4d%12.4f",i+1,mol,1,q[i]);
				for (k=0;k<3;k++)
				{
					fprintf(fp2,"%12.4f",x[i][k]);
				}
				fprintf(fp2,"\n");
				atomC++;
			}
			else if (strcmp(atomname[i],"F")==0)
			{
				fprintf(fp2,"%8d%4d%4d%12.4f",i+1,mol,2,q[i]);
				for (k=0;k<3;k++)
				{
					fprintf(fp2,"%12.4f",x[i][k]);
				}
				fprintf(fp2,"\n");
				atomO++;
			}
			else if (strcmp(atomname[i],"H")==0)
			{
				fprintf(fp2,"%8d%4d%4d%12.4f",i+1,mol,3,q[i]);
				for (k=0;k<3;k++)
				{
					fprintf(fp2,"%12.4f",x[i][k]);
				}
				fprintf(fp2,"\n");
				atomH++;
			}
		}
		// bond
		fprintf(fp2,"\n%cBonds\n\n",32);
		for (i=0;i<nbonds;i++)
		{
			bondCC=0;
			bondCO=0;
			bondOH=0;
			if (bond[i][0]<atomC&&bond[i][1]<atomC)
			{
				bondCC=1;
			} 
			else if ((bond[i][0]>atomC-1||bond[i][1]>atomC-1)&&(bond[i][0]<atomC+atomO&&bond[i][1]<atomC+atomO))
			{
				bondCO=1;
			} 
			else if ((bond[i][0]>natoms-atomH-1||bond[i][1]>natoms-atomH-1)&&(bond[i][0]<natoms-atomH-1||bond[i][1]<natoms-atomH-1))
			{
				bondOH=1;
			}
			if (bondCC==1)
			{
				fprintf(fp2,"%8d%4d%8d%8d\n",i+1,1,bond[i][0]+1,bond[i][1]+1);
			}
			else if (bondCO==1)
			{
				fprintf(fp2,"%8d%4d%8d%8d\n",i+1,2,bond[i][0]+1,bond[i][1]+1);
			}
			else //if (bondOH==1)
			{
				fprintf(fp2,"%8d%4d%8d%8d\n",i+1,3,bond[i][0]+1,bond[i][1]+1);
			}
		}
		// angle
		fprintf(fp2,"\n%cAngles\n\n",32);
		for (i=0;i<nangls;i++)
		{
			angCCC=0;
			angCCO=0;
			angCOH=0;
			if (angl[i][0]<atomC&&angl[i][1]<atomC&&angl[i][2]<atomC)
			{
				angCCC=1;
			} 
			else if ((angl[i][0]>atomC-1||angl[i][1]>atomC-1||angl[i][2]>atomC-1)&&(angl[i][0]<atomC+atomO&&angl[i][1]<atomC+atomO&&angl[i][2]<atomC+atomO))
			{
				angCCO=1;
			} 
			else if (angl[i][0]>natoms-atomH-1||angl[i][1]>natoms-atomH-1||angl[i][2]>natoms-atomH-1)
			{
				angCOH=1;
			}
			if (angCCC==1)
			{
				fprintf(fp2,"%8d%4d%8d%8d%8d\n",i+1,1,angl[i][0]+1,angl[i][1]+1,angl[i][2]+1);
			}
			else if (angCCO==1)
			{
				fprintf(fp2,"%8d%4d%8d%8d%8d\n",i+1,2,angl[i][0]+1,angl[i][1]+1,angl[i][2]+1);
			}
			else if (angCOH==1)
			{
				fprintf(fp2,"%8d%4d%8d%8d%8d\n",i+1,3,angl[i][0]+1,angl[i][1]+1,angl[i][2]+1);
			}
		}
		// dihedral
		fprintf(fp2,"\n%cDihedrals\n\n",32);
		for (i=0;i<ndihs;i++)
		{
			dihCCCC=0;
			dihCCCO=0;
			dihCCOH=0;
			if (dih[i][0]<atomC&&dih[i][1]<atomC&&dih[i][2]<atomC&&dih[i][3]<atomC)
			{
				dihCCCC=1;
			} 
			else if ((dih[i][0]>atomC-1||dih[i][1]>atomC-1||dih[i][2]>atomC-1||dih[i][3]>atomC-1)&&(dih[i][0]<atomC+atomO&&dih[i][1]<atomC+atomO&&dih[i][2]<atomC+atomO&&dih[i][3]<atomC+atomO))
			{
				dihCCCO=1;
			}
			else if (dih[i][0]>natoms-atomH-1||dih[i][1]>natoms-atomH-1||dih[i][2]>natoms-atomH-1||dih[i][3]>natoms-atomH-1)
			{
				dihCCOH=1;
			} 
			if (dihCCCC==1)
			{
				fprintf(fp2,"%8d%4d%8d%8d%8d%8d\n",i+1,1,dih[i][0]+1,dih[i][1]+1,dih[i][2]+1,dih[i][3]+1);
			}
			else if (dihCCCO==1)
			{
				fprintf(fp2,"%8d%4d%8d%8d%8d%8d\n",i+1,2,dih[i][0]+1,dih[i][1]+1,dih[i][2]+1,dih[i][3]+1);
			}
			else if (dihCCOH==1)
			{
				fprintf(fp2,"%8d%4d%8d%8d%8d%8d\n",i+1,3,dih[i][0]+1,dih[i][1]+1,dih[i][2]+1,dih[i][3]+1);
			}
		}
		fclose(fp1);
		fclose(fp2);
		printf("Topologies found:\n");
		printf("%8d%catoms\n",natoms,32);
		printf("%8d%cbonds\n",nbonds,32);
		printf("%8d%cangles\n",nangls,32);
		printf("%8d%cproper dihedrals\n",ndihs,32);
	}

}