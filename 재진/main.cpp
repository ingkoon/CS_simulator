#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
int tmeal[33];
int ameal[33];
int tbolus[33];
double abolus[33];
int tmealPM[33];
char *name[20]={"adolescents1.txt","M_adolescents2.txt","M_adolescents3.txt","adolescents4.txt","M_adolescents5.txt","adolescents6.txt","adolescents7.txt","M_adolescents8.txt","M_adolescents9.txt","adolescents10.txt","adult1.txt","adult2.txt","M_adult3.txt","adult4.txt","M_adult5.txt","M_adult6.txt","M_adult7.txt","adult8.txt","M_adult9.txt","adult10.txt"};
void initValue(int num,int who,FILE * fs);
void creatScript(FILE * fs);
void makeMutantScript(FILE*fs);
void makeMutant();
void makeNormal();
long double adult[10]={19.1612,22.4840,14.5516,19.7031,13.4688,8.9951,18.1445,8.7930,19.7629,13.7726};
int normalAdult[10]={1,1,0,1,0,0,0,1,0,1};
long double adolescents[10]={25.9375, 19.7031, 25.9375, 10.3516, 10.3516, 24.3789, 25.9375, 8.7930, 11.1309, 15.0273};
int normalAdolescents[10]={1,0,0,1,0,1,1,0,0,1};
int main(int argc, char *argv[]) {
	srand(time(0));
//	makeNormal();//make scriptValue and script
//	makeMutant();//make mutant	
	return 0;
}
void initValue(int num,int who,FILE * fs){
	long double CR;
	int i,j=-1440;
	
	if(!who){CR =adolescents[num];}
	else{CR= adult[num];} 
	
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
		abolus[i*3]=(long double)ameal[i*3]/CR;
		abolus[i*3+1]=(long double)ameal[i*3+1]/CR;
		abolus[i*3+2]=(long double)ameal[i*3+2]/CR;		
	//	fprintf(fs,"%.2lf %.2lf %.2lf ",abolus[i*3],abolus[i*3+1],abolus[i*3+2]);
	}
}
void creatScript(FILE * fs){
	
	int i;
	fprintf(fs,"simulation info\n\n%%Tsimul=11\n%%QTsimul=day\n%%simToD=0\n\nclosed loop info\n\n%%Tclosed=264\n%%%QTclosed=hour\n%%Treg=15840\n\n");
	fprintf(fs,"Open loop info\n\n%%Qbasal=quest\n\n");

	fprintf(fs,"meals info\n\n");
	fprintf(fs,"%%Tmeals=[");
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
		fprintf(fs,"%.2Lf ",abolus[i]);	
	}fprintf(fs,"]\n");
	
}
void makeMutantScript(FILE*fs){
	int i;
	long double abolusTemp;	
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
		fprintf(fs,"%0.2Lf ",abolusTemp);	//abolus[i]-((double)(rand()%600)/100)-3
	}fprintf(fs,"]\n");
}
void makeMutant(){

	FILE m1,m2,m3,m4,m5,m6,m7,m8,m9,m10;
	FILE *mutant[10]={&m1,&m2,&m3,&m4,&m5,&m6,&m7,&m8,&m9,&m10};	
	int i,k=0;
	
	for(i=0;i<10;i++){ //adolescents
		if(!normalAdolescents[i]){	
	   		mutant[k]=fopen(name[i],"w");
			initValue(i,0,mutant[k]);
			makeMutantScript(mutant[k]);
			fclose(mutant[k++]);
		}
	}	
	
	for(i=0;i<10;i++){ //adult
		if(!normalAdult[i]){	
	   		mutant[k]=fopen(name[i+10],"w");
			initValue(i,1,mutant[k]);
			makeMutantScript(mutant[k]);
			fclose(mutant[k++]);
		}
	}
}
void makeNormal(){

	FILE m1,m2,m3,m4,m5,m6,m7,m8,m9,m10;
	FILE *normal[10]={&m1,&m2,&m3,&m4,&m5,&m6,&m7,&m8,&m9,&m10};	
	int i,k=0;
	
	for(i=0;i<10;i++){ //adolescents
		if(normalAdolescents[i]){	
	   		normal[k]=fopen(name[i],"w");
			initValue(i,0,normal[k]);
			creatScript(normal[k]);
			fclose(normal[k++]);
		}
	}	
	
	for(i=0;i<10;i++){ //adult
		if(normalAdult[i]){	
	   		normal[k]=fopen(name[i+10],"w");
			initValue(i,1,normal[k]);
			creatScript(normal[k]);
			fclose(normal[k++]);
		}
	}
}
