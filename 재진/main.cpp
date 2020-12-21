#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
int tmeal[33];
int ameal[33];
int tbolus[33];
double abolus[33];
int tmealPM[33];
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void initValue();
void creatScript(FILE * fs);
void makeMutantScript(FILE*fs,int seed);
void makeMutant();
void makeScript();

int main(int argc, char *argv[]) {
	srand(time(0));
	makeScript();//make scriptValue and script
	makeMutant();//make mutant
	
	return 0;
}
void initValue(){
	
	int i,j=-1440;
//	fprintf(fs,"tmeal: ");// j(하루 1440분)+[6시 12시 19시] + tmealPM 
	for(i=0;i<11;i++){
		j+=1440;
		tmeal[i*3]=360+j+(rand()%120);
		tmeal[i*3+1]=720+j+(rand()%120);
		tmeal[i*3+2]=1140+j+(rand()%120);
		
	//	fprintf(fs,"%d %d %d ",tmeal[i*3],tmeal[i*3+1],tmeal[i*3+2]);
	}
	
//	fprintf(fs,"\nAmeal: ");
	for(i=0;i<11;i++){		//랜덤값을 초기에 받고 변수로 저장해서 사용중 새로 받으려면 밑에 3줄 주석 해제 
		ameal[i*3]=45+rand()%20-10; 
		ameal[i*3+1]=75+rand()%20-10;
		ameal[i*3+2]=85+rand()%20-10;		
	//	fprintf(fs,"%d %d %d ",ameal[i*3],ameal[i*3+1],ameal[i*3+2]);
	}
	
//	fprintf(fs,"\ntbolus: ");//식사시간 - 45분 
	for(i=0;i<11;i++){
		tbolus[i*3]=tmeal[i*3]-45;
		tbolus[i*3+1]=tmeal[i*3+1]-45;
		tbolus[i*3+2]=tmeal[i*3+2]-45;		
	//	fprintf(fs,"%d %d %d ",tbolus[i*3],tbolus[i*3+1],tbolus[i*3+2]);
	}
	
//	fprintf(fs,"\nabolus: ");//식사량/15 한 값  
	for(i=0;i<11;i++){
		abolus[i*3]=(double)ameal[i*3]/15;
		abolus[i*3+1]=(double)ameal[i*3+1]/15;
		abolus[i*3+2]=(double)ameal[i*3+2]/15;		
	//	fprintf(fs,"%.2lf %.2lf %.2lf ",abolus[i*3],abolus[i*3+1],abolus[i*3+2]);
	}
}
void creatScript(FILE * fs){
	
	int i;
	fprintf(fs,"simulation info\n\n%%Tsimul=11\n%%QTsimul=day\n%%simToD=0\n\nclosed loop info\n\n%%Tclosed=264\n%%%QTclosed=hour\n%%Treg=15840\n\n");
	fprintf(fs,"Open loop info\n\n%%Qbasal=quest\n\n");

	fprintf(fs,"meals info\n\n");
	fprintf(fs,"%%Tmeal=[");
	for(i=0;i<33;i++){
		fprintf(fs,"%d ",tmeal[i]);	
	}fprintf(fs,"]\n%%QTmeals=min\n");
	
	fprintf(fs,"%%Ameals=[");
	for(i=0;i<33;i++){
		fprintf(fs,"%d ",ameal[i]);	
	}fprintf(fs,"]\n%%Dmeals=[15]\n%%Qmeals=total\n");
	
	fprintf(fs,"\nbolus info\n%%Tbolus=[");
	for(i=0;i<33;i++){
		fprintf(fs,"%d ",tbolus[i]);	
	}fprintf(fs,"]\n%%QTbolus=min\n");		
	
	fprintf(fs,"%%Abolus=[");
	for(i=0;i<33;i++){
		fprintf(fs,"%.2lf ",abolus[i]);	
	}fprintf(fs,"]\n");
	
}
void makeMutantScript(FILE*fs,int seed){
	int i;
	double abolusTemp;	
	fprintf(fs,"simulation info\n\n%%Tsimul=11\n%%QTsimul=day\n%%simToD=0\n\nclosed loop info\n\n%%Tclosed=264\n%%%QTclosed=hour\n%%Treg=15840\n\n");
	fprintf(fs,"Open loop info\n\n%%Qbasal=quest\n\n");

	fprintf(fs,"meals info\n\n");
	fprintf(fs,"%%Tmeal=[");
	for(i=0;i<33;i++){
		fprintf(fs,"%d ",tmeal[i]);	
	}fprintf(fs,"]\n%%QTmeals=min\n");
	
	fprintf(fs,"%%Ameals=[");
	for(i=0;i<33;i++){
		fprintf(fs,"%d ",ameal[i]);	
	}fprintf(fs,"]\n%%Dmeals=[15]\n%%Qmeals=total\n");
	
	fprintf(fs,"\nbolus info\n%%Tbolus=[");
	for(i=0;i<33;i++){
		fprintf(fs,"%d ",tbolus[i]);	
	}fprintf(fs,"]\n%%QTbolus=min\n");		
	
	fprintf(fs,"%%Abolus=[");
	for(i=0;i<33;i++){
		abolusTemp=abolus[i]-((double)(rand()%600)-300)/100;
		if(abolusTemp<0)abolusTemp=0;
		fprintf(fs,"%0.2lf ",abolusTemp);	//abolus[i]-((double)(rand()%600)/100)-3
	}fprintf(fs,"]\n");
}
void makeMutant(){
	FILE m1,m2,m3,m4,m5,m6,m7,m8,m9,m10;
	FILE *mutant[10]={&m1,&m2,&m3,&m4,&m5,&m6,&m7,&m8,&m9,&m10};
	char *mutantname[10]={"m1.txt","m2.txt","m3.txt","m4.txt","m5.txt","m6.txt","m7.txt","m8.txt","m9.txt","m10.txt"};	
	int i;
	
	for(i=0;i<10;i++){
   		mutant[i]=fopen(mutantname[i],"w");
   		initValue(mutant[i],i);
		makeMutantScript(mutant[i],i);
		fclose(mutant[i]);
	}
}
void makeScript(){

	FILE m1,m2,m3,m4,m5,m6,m7,m8,m9,m10;
	FILE *normal[10]={&m1,&m2,&m3,&m4,&m5,&m6,&m7,&m8,&m9,&m10};
	char *normalName[10]={"script1.txt","script2.txt","script3.txt","script4.txt","script5.txt","script6.txt","script7.txt","script8.txt","script9.txt","script10.txt"};	
	int i;
	
	for(i=0;i<10;i++){
   		normal[i]=fopen(normalName[i],"w");
		initValue(normal[i],i);
		creatScript(normal[i]);
		fclose(normal[i]);
	}
}
