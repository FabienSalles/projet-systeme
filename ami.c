#ifndef ami_h
#include "ami.h"
#endif

void ajouterAmi(char * user){
	FILE * fic;

	char nom[128],
	     fileAmi[256] = "",
		 histoAjout[256]="";
	printf("##############################################################\n");
	printf("#                        Ajouter un ami                      #\n");
	printf("##############################################################\n\n");
	printf("Nom : ");
	scanf("%s",nom);
	clear();
	printf("\n");

	if(userExist(nom, NULL)){
		
		if(amiExist(user, nom)){
			errorAjoutAmi(user);
		}
		else {
			// ajout de l'ami dans le fichier ami de l'utilisateur	
			strcat(fileAmi, DIR_USERS);
			strcat(fileAmi, user);
			strcat(fileAmi, "/amis.txt");
			fic = fopen(fileAmi, "a");
			fprintf(fic, "%s\n", nom);
			fclose(fic);
			printf("\n-------------------------------------------------------------\n");
			printf("%s est maintenant votre ami(e) \n",nom);
			
			//Ajout dans historique
			strcat(histoAjout,"Ajout_de_l'ami(e)_");
			strcat(histoAjout,nom);
			addAction(user,histoAjout);
			
			printf("\n\n");
			menuconnect(user);
		}
	}
	else {
		printf("\nLe nom de votre ami n'existe pas!\n");
		printf("Veuillez resaisir le nom d'utilisateur!\n\n");
		ajouterAmi(user);
	}
	

}

void supprAmi(char* user){
	
	char nom[128],
	     choix,
	     histoSuppr[256]="";

	printf("##############################################################\n");
	printf("#                       Supprimer un ami                     #\n");
	printf("##############################################################\n\n");

	printf("Nom : ");
	scanf("%s", nom);
	clear();
	printf("\n");
	if(amiExist(user,nom)==0){
		errorAmi(user,1);
	}
	else{
		printf("Voulez vous vraiment supprime %s de vos amis? \n",nom);
		printf("1 : oui\n");
		printf("2 : non\n");
		scanf("%c", &choix);
		clear();

		if(choix=='2'){
			menuconnect(user);
		}
		else{
			fonctionSupprAmi(user,nom);
			
			printf("\n-------------------------------------------------------------\n");
			printf("L'ami %s vient d'etre supprime\n",nom);
			
			
			//Suppr dans historique
			strcat(histoSuppr,"Sppression_de_l'ami(e)_");
			strcat(histoSuppr,nom);
			addAction(user,histoSuppr);
			printf("\n\n");
			menuconnect(user);
		}
	}
}

void fonctionSupprAmi(char* user,char* nom){
			
			char fileAmi[256] = "";
			char fileAmiTmp[256] = "";
			char ami[128]= "";
			FILE * fic;
			FILE * ficTmp;
			
			strcat(fileAmi, DIR_USERS);
			strcat(fileAmi, user);
			strcat(fileAmiTmp, fileAmi);
			strcat(fileAmi, "/amis.txt");
			strcat(fileAmiTmp, "/amisTmp.txt");
			
			//creation du fichier temporaire
			ficTmp = fopen(fileAmiTmp, "w");
			fclose(ficTmp);
			
			ficTmp = fopen(fileAmiTmp, "a");
			if (ficTmp==NULL) {
				printf("fichier inexistant2\n");
				exit(0);
			}
			fic=fopen(fileAmi,"r");
			if (fic==NULL) {
				printf("fichier inexistant3\n");
				exit(0);
			}
			
			while(fscanf(fic,"%s",ami)!=EOF){
				if(strcasecmp(nom, ami) == 0){
				//ne rien faire
				}
				else
					fprintf(ficTmp, "%s\n", ami);
			}
			fclose(ficTmp);
			fclose(fic);
			rename(fileAmiTmp,fileAmi);
	
}

int amiExist(char* user,char nom[128]){
	char fileAmi[256] = "";
	char ami[128];

	int trouve = 0;
	FILE * fic;
	
	strcat(fileAmi, DIR_USERS);
	strcat(fileAmi, user);
	strcat(fileAmi, "/amis.txt");
	
	fic=fopen(fileAmi,"r");
	
	while(fscanf(fic,"%s",ami)!=EOF){
		if(strcasecmp(nom, ami) == 0)
			trouve = 1;
	}

	fclose(fic);
	return trouve;
}

void errorAjoutAmi(char* user){

	char choix;
	
	printf("\nL'ami existe déjà!\n\n");
	printf("1 : Try again\n");
	printf("2 : Retour Menu\n\n");

	printf("Choix : ");
	scanf("%c", &choix);
	clear();

	switch(choix){
		case '1':
			ajouterAmi(user);
			break;
		case '2':
			menuconnect(user);
			break;
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			errorAjoutAmi(user);
	}
}
/**
 *si from=1=suppr ami
 *si from=2=envoimessage
 *si from=3=affiche mur ami
 */
void errorAmi(char* user,int from){
	char choix;
	
	printf("L'ami(e) saisie n'existe pas!\n\n");
	printf("1 : Try again\n");
	printf("2 : Retour Menu\n\n");

	printf("Choix : ");
	scanf("%c", &choix);
	clear();

	switch(choix){
		case '1':
			switch(from){
				case 1:
					supprAmi(user);
					break;
				case 2:
					envoyerMessage(user);
					break;
				case 3:
					afficheMurAmi(user);
					break;
			}
			break;
		case '2':
			menuconnect(user);
			break;
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			errorAmi(user,from);
	}
}

