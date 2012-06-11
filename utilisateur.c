#include "utilisateur.h"

void inscription(){
	char saisie[128];
	Utilisateur user;
	int fd;

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
		else
		 	printf("Les mots de passes sont différent!\n");
			printf("Veuillez les resaisir!\n");
	}
	

	// enregistrement dans le fichier
	if ((fd = open(fileUser, O_WRONLY)) < 0) {
		fprintf(stderr, "Erreur : %s ne peut être ouvert\n",fileUser);
		exit(EXIT_FAILURE);
	}
	printf("nom : %s",user.nom);
	printf("prenom : %s",user.password);
	printf("\n");
}

void auth(){

	char nom[100],login[100];
	char pwd[100],mdp[100];
	
	printf("############################\n");
	printf("####  authentification  ####\n");
	printf("Nom : ");
	scanf("%s", nom);
	printf("Mot de passe : ");
	scanf("%s", mdp);
	
	FILE *fic;
	fic=fopen("./users.txt","w");
	
	if (fic==NULL) {
	printf("fichier inexistant\n");
	return 0;
	}
	
	while(fscanf(fic,"%s",login)!=EOF){
		if(strcasecmp(login, nom) == 0){
			fscanf(fic,"%s",pwd);
			if(strcasecmp(pwd, mdp) == 0){
				//login et mdp OK!
				printf("vous etes maintenant connecte!");
			}
			else// !mdp
				printf("Le mot de passe ou/et login est incorecte!");
		}
		else// !login
			printf("Le mot de passe ou/et login est incorecte!");
	}

}
