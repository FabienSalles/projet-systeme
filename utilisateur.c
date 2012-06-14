#ifndef utilisateur_h
#include "utilisateur.h"
#endif

Utilisateur inscription(){
	char saisie[128],
	     dirUser[256] = "",
	     fileHistorique[256] ="",
	     fileAmi[256] = "",
	     fileMsgEnvoye[256] = "",
	     fileMsgRecu[256] = "";

	Utilisateur user;
	FILE * fic;

	// Saisie du login et mot de passe
	printf("##############################################################\n");
	printf("#                          S'inscrire                        #\n");
	printf("##############################################################\n\n");
	printf("Nom : ");
	scanf("%s", user.nom);
	while(1){
		printf("Mot de passe : ");
		scanf("%s", user.password);
		printf("Mot de passe (confirmer) : ");
		scanf("%s", saisie);
		if(strcasecmp(user.password, saisie)==0)
			break;
		else {
		 	printf("Les mots de passes sont différent!\n");
			printf("Veuillez les resaisir!\n");
		}
	}
	

	// enregistrement de l'utiliseur (users.txt)
	if ((fic = fopen(FILE_USERS, "a" )) < 0) {
		fprintf(stderr, "Erreur : %s ne peut être ouvert\n",FILE_USERS);
		exit(EXIT_FAILURE);
	}

	if(userExist(user.nom, NULL)){
		printf("\nLe nom d'utilisateur exsite déjà!\n");
		printf("Veuillez resaisir les données!\n\n");
		
		return inscription();
	}
	else {

		fprintf(fic, "%s %s\n", user.nom,user.password);
		fclose(fic);

		// créaction du dossier utilisateur
		strcat(dirUser, DIR_USERS);
		strcat(dirUser, user.nom);
		mkdir(dirUser, 0777);

		// création du fichier gérant l'historique de l'utilisateur
		strcat(fileHistorique, DIR_HISTORIQUES);
		strcat(fileHistorique, user.nom);
		strcat(fileHistorique, ".txt");
		fic = fopen(fileHistorique, "w");
		fclose(fic);

		// création du fichier gérant les amis de l'utilisateur
		strcat(fileAmi, dirUser);
		strcat(fileAmi, "/amis.txt");
		fic = fopen(fileAmi, "w");
		fclose(fic);

		// création des fichiers gérant les messages de l'utilisateur
		strcat(fileMsgEnvoye, dirUser);
		strcat(fileMsgEnvoye, "/envoyes.txt");
		fic = fopen(fileMsgEnvoye, "w");
		fclose(fic);

		strcat(fileMsgRecu, dirUser);
		strcat(fileMsgRecu, "/recus.txt");
		fic = fopen(fileMsgRecu, "w");
		fclose(fic);

		printf("\n");
		printf("vous etes maintenant connecte!\n");
		printf("\n");
		
		//ajout dans le fichier historique
		addAction(user.nom,"Création_du_compte");
		return user;
	}
}

Utilisateur auth(){

	Utilisateur user;
	printf("##############################################################\n");
	printf("#                       authentification                     #\n");
	printf("##############################################################\n\n");
	printf("Nom : ");
	scanf("%s", user.nom);
	printf("Mot de passe : ");
	scanf("%s", user.password);

	printf("\n");	
	//vérification login et mdp
	if(!userExist(user.nom, user.password)) 
		errorUserExist();
	else
		printf("vous etes maintenant connecte!\n");
	printf("\n");
	//ajout dans le fichier historique
	addAction(user.nom,"Connexion");
	return user;	
}

int userExist(char * nom, char * password){
	//retour 1 si login et mdp ok sinon 0
	int trouve=0;
	Utilisateur temp;
	FILE *fic;
	
	fic=fopen(FILE_USERS,"r");
	if (fic==NULL) {
		printf("fichier inexistant\n");
		exit(0);
	}
	
	while(fscanf(fic,"%s %s",temp.nom, temp.password)!=EOF){
		if(strcasecmp(temp.nom, nom) == 0){
			if(password){
				if(strcasecmp(temp.password, password) == 0){
					//login et mdp OK!
					trouve=1;
					break;
				}
			} else {
				// login ok
				trouve=1;
				break;
			}
		}
	}
	fclose(fic);
	
	return trouve;
}

void errorUserExist(){
	int choix=0;
	
	printf("Le mot de passe et/ou login est incorecte!\n\n");
	printf("1 : Try again\n");
	printf("2 : Retour Menu\n");
	scanf("%d", &choix);
			
	switch(choix){
		case 1:
			auth();
			break;
		case 2:
			menu();
			break;
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			errorUserExist();

	}
}

void modifMDP(char* user){
	
	FILE *fic;
	FILE *ficTmp;
	char fileTmp[256]="usersTmp.txt",
		 login[256]="",
		 pwd[128]="",
		 mdp[128]="",
		 tmp[128]="";
	printf("##############################################################\n");
	printf("#                 Modification mot de passe                  #\n");
	printf("##############################################################\n\n");
	while(1){
		printf("Nouveau mot de passe : ");
		scanf("%s", mdp);
		printf("Nouveau mot de passe (confirmer) : ");
		scanf("%s", tmp);
		if(strcasecmp(mdp,tmp)==0)
			break;
		else {
		 	printf("Les mots de passes sont différent!\n");
			printf("Veuillez les resaisir!\n");
		}
	}
	
	fic=fopen(FILE_USERS,"r");
	if (fic==NULL) {
		printf("fichier inexistant\n");
		exit(0);
	}
	ficTmp=fopen(fileTmp,"a");
	if (ficTmp==NULL) {
		printf("fichier inexistant\n");
		exit(0);
	}
	
	while(fscanf(fic,"%s %s",login,pwd)!=EOF){
		if(strcasecmp(user, login) == 0){
			//modifier le mdp
			fprintf(ficTmp, "%s %s\n",login,mdp);
		}
		else
			fprintf(ficTmp, "%s %s\n",login,pwd);
	}
	fclose(ficTmp);
	fclose(fic);
	rename(fileTmp,FILE_USERS);
	printf("##############################################################\n");
	printf("Mot de passe change!");
	printf("\n\n");
	//ajout dans le fichier historique
	addAction(user,"Modification_du_mot_de_passe");
	menuconnect(user);
}

void afficheMur(char * user,char* userAffiche){
	
	FILE *fic;
	FILE *fic2;
	char ami[128],
		 fileAmi[256] = "",
		 file[256] = "",
		 pathMsg[256] = "",
		 destinataire[256] = "";
	int i=0,c;
	Message msg;
	printf("##############################################################\n");
	printf("#                        Liste des amis                      #\n");
	printf("##############################################################\n\n");
	strcat(fileAmi, DIR_USERS);
	strcat(fileAmi, userAffiche);
	strcat(fileAmi, "/amis.txt");
	fic = fopen(fileAmi, "r");
	while(fscanf(fic,"%s",ami)!=EOF){
		printf("%s\n",ami);
		i++;
	}
	printf("--------------------------------------------------------------\n");
	printf("total: %d amis\n\n",i);
	fclose(fic);
	printf("##############################################################\n");
	printf("#                    Liste des messages envoye               #\n");
	printf("##############################################################\n\n");
	i=0;
	strcat(file, DIR_USERS);
	strcat(file, userAffiche);
	strcat(file, FILE_ENVOYES);
	fic = fopen(file, "r");
	while(fscanf(fic,"%s %s %s %s", msg.id, msg.date, msg.hour, msg.exp)!=EOF){

		strcat(pathMsg, DIR_USERS);
		strcat(pathMsg, userAffiche);
		strcat(pathMsg, "/");
		strcat(pathMsg, msg.id);
		strcat(pathMsg, ".txt");
		fic2 = fopen(pathMsg, "r");
		fscanf(fic2,"%s",destinataire);
		printf("Destinataire: %s\nMessage:",destinataire);
		while((c=fgetc(fic2))!=EOF){
			printf("%c",c);
		}
		printf("--------------------------------------------------------------\n");
		i++;
	}
	printf("total: %d messages\n",i);
	
	
	
	printf("\n\n");
	menuconnect(user);
}
void deconnexion(char* user){
	//ajout dans le fichier historique
	addAction(user,"Deconnexion");
	int status;
	if(fork()==0){
		char fileHistorique[256]="";
		strcat(fileHistorique, DIR_HISTORIQUES);
		strcat(fileHistorique, user);
		strcat(fileHistorique, ".txt");
		execl("/bin/clear","clear",NULL);
	}
	else{
		wait(&status);
		printf("\n\n");
		menu();
	}
}

void afficheMurAmi(char* user){
	
	char ami[128];
	printf("##############################################################\n");
	printf("#                    Affichage du mur d'un ami               #\n");
	printf("##############################################################\n\n");
	printf("nom de l'ami: ");
	scanf("%s",ami);
	if(amiExist(user,ami)==0)
		errorAmi(user,3);
	else{
		afficheMur(user,ami);
	}
}