#ifndef historique_h
#include "h​istorique.h"
#endif

void addAction(char * user, char * action){
	time_t rowtime;
	rowtime = getTimeStamp();
	
	addActionWithDate(user, action, rowtime);
}

void addActionWithDate(char * user, char * action, time_t timestamp){
	
	char fileHistorique[256]="",
	     fileTemp[256]="",
	     date[11],
	     hour[11],
	     tempDate[11],
	     tempHour[11],
	     tempAction[256];

	FILE * fic,
	     * temp;
	
	// Génération de la date
	getDate(timestamp,date);
	getHour(timestamp,hour);

	//  --- Modification du fichier historique --- //

	// Ouverture et créations des fichiers
	strcat(fileHistorique, DIR_HISTORIQUES);
	strcat(fileHistorique, user);
	strcat(fileHistorique, ".txt");

	strcat(fileTemp, DIR_HISTORIQUES);
	strcat(fileTemp, "temp.txt");
	
	if ((fic = fopen(fileHistorique, "r")) < 0) {
		fprintf(stderr, "Erreur : %s ne peut être ouvert\n",fileHistorique);
		exit(EXIT_FAILURE);
	}

	temp = fopen(fileTemp, "w");
	
	// Ajout de l'action dans le fichier temporaire
	fprintf(temp, "%s %s %s\n",date, hour, action);

	// Ajout des enciènnes actions
	while(fscanf(fic,"%s %s %s",tempDate, tempHour, tempAction)!=EOF){
		fprintf(temp, "%s %s %s\n",tempDate, tempHour, tempAction);
	}

	// fermeture des fichiers
	fclose(fic);
	fclose(temp);

	//on remplace le fichier d'historique par le fichier temporaire
	rename(fileTemp,fileHistorique);
}

void AfficherHisto(char * user){
	
	int status,f=fork();
	if(f==0){
		char fileHistorique[256]="";
		strcat(fileHistorique, DIR_HISTORIQUES);
		strcat(fileHistorique, user);
		strcat(fileHistorique, ".txt");
		execl("/bin/more","more",fileHistorique,NULL);
	}
	else{
		wait(&status);
		printf("\n\n");
		menuconnect(user);
	}
}
