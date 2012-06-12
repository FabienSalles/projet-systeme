#include "utilisateur.h"

void inscription(){
	char saisie[128];
	char dirUser[256] = "";
	strcat(dirUser, DIR_USERS);
	Utilisateur user;
	FILE * fic;

	// Saisie du login et mot de passe
	printf("############################\n");
	printf("####     S'inscrire     ####\n");
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
	

	// enregistrement dans le fichier
	if ((fic = fopen(FILE_USERS, "a" )) < 0) {
		fprintf(stderr, "Erreur : %s ne peut être ouvert\n",FILE_USERS);
		exit(EXIT_FAILURE);
	}
	//fprintf(fic, "%s %s\n", user.nom,user.password);
	strcat(dirUser, user.nom);
	mkdir(dirUser, 0777);
	printf("%s\n", dirUser);
	printf("\n");
}

int loginExiste(char nom[100]){
	//retour 1 si le login existe sinon 0
	int trouve=0;
	char login[100];
	char pwd[100];
	FILE *fic;
	
	fic=fopen(fileUser,"r");
	if (fic==NULL) {
		printf("fichier inexistant\n");
		exit(0);
	}
	
	while(fscanf(fic,"%s",login)!=EOF){
		fscanf(fic,"%s",pwd);
		if(strcasecmp(login, nom) == 0){
			//login OK!
			trouve=1;
			break;
		}
	}
	fclose(fic);
	
	return trouve;
}

int verifLogin(char nom[100], char mdp[100]){
	//retour 1 si login et mdp ok sinon 0
	int trouve=0;
	char login[100];
	char pwd[100];
	FILE *fic;
	
	fic=fopen(fileUser,"r");
	if (fic==NULL) {
		printf("fichier inexistant\n");
		exit(0);
	}
	
	while(fscanf(fic,"%s",login)!=EOF){
		fscanf(fic,"%s",pwd);
		if(strcasecmp(login, nom) == 0){
			if(strcasecmp(pwd, mdp) == 0){
				//login et mdp OK!
				trouve=1;
				break;
			}
		}
	}
	fclose(fic);
	
	return trouve;
}

void auth(){

	char nom[100];
	char mdp[100];
	int choix=0;
	
	printf("############################\n");
	printf("####  authentification  ####\n");
	printf("Nom : ");
	scanf("%s", nom);
	printf("Mot de passe : ");
	scanf("%s", mdp);
	
	if(verifLogin(nom ,mdp)==0){//vérification login et mdp
		printf("Le mot de passe et/ou login est incorecte!\n\n");
		
		while(choix == 0){
			printf("1 : Try again\n");
			printf("2 : Retour Menu\n");
			scanf("%d", &choix);
			
			switch(choix){
				case 1:
					auth();
					break;
				case 2:
					fflush(stdin);
					menu();
					break;
				default:
					printf("\nUne erreur est survenue!\n");
					printf("Veuillez refaire un choix\n");
					printf("%d",choix);
					choix=0;
			}
		}
	}
	else
		printf("vous etes maintenant connecte!\n");
		
}

