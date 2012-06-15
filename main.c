#ifndef main_h
#include "main.h"
#endif

int main(int argc, char * argv[]){
	
	menu();
	return  0;
	
}

void menu(){
	int choix;
	Utilisateur user;
	printf("##############################################################\n");
	printf("#                            Accueil                         #\n");
	printf("##############################################################\n\n");
	printf("1 : S'inscrire\n");
	printf("2 : S'authentifier\n");
	printf("0 : Quitter\n");
	printf("\n-------------------------------------------------------------\n");
	printf("Choix : ");
	scanf("%d", &choix);
	
	printf("\n\n");
	switch(choix){
		case 1:
			user = inscription();
			break;
		case 2:
			user = auth();
			break;
		case 0:
			exit(EXIT_SUCCESS);
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			menu();
	}
	menuconnect(user.nom);
}

void menuconnect(char * user){
	
	int choix;
	printf("##############################################################\n");
	printf("#                             Menu                           #\n");
	printf("##############################################################\n\n");
	printf("1 : Affichage des mur\n");
	printf("2 : Messagerie\n");
	printf("3 : Gestion des amis\n");
	printf("4 : Gestion du compte\n");
	printf("9 : Deconnexion\n");
	printf("0 : Quitter\n");
	printf("\n-------------------------------------------------------------\n");
	printf("Choix : ");
	scanf("%d", &choix);
	printf("\n\n");
	switch(choix){

		case 1:
			menuMur(user);
			break;
		case 2:
			menuMessagerie(user);
			break;
		case 3:
			menuAmi(user);
			break;
		case 4:
			menuCompte(user);
			break;
		case 9:
			deconnexion(user);
			break;
		case 0:
			exit(EXIT_SUCCESS);
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			menuconnect(user);
	}
}

void menuMur(char * user){
	
	int choix;

	printf("##############################################################\n");
	printf("#                       Affichage des mur                    #\n");
	printf("##############################################################\n\n");
	printf("1 : Afficher mon mur\n");
	printf("2 : Afficher le mur d'un ami\n");
	printf("9 : Retour Menu\n");
	printf("\n-------------------------------------------------------------\n");
	printf("Choix : ");
	scanf("%d", &choix);
	printf("\n\n");
	switch(choix){

		case 1:
			afficheMur(user,user);
			break;
		case 2:
			afficheMurAmi(user);
			break;
		case 9:
			menuconnect(user);
			break;	
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			menuMur(user);
	}
}
void menuMessagerie(char * user){
	
	int choix;

	printf("##############################################################\n");
	printf("#                          Messagerie                        #\n");
	printf("##############################################################\n\n");
	printf("1 : Boite de reception(%d)\n",nbMsgRecus(user, 1));
	printf("2 : Envoyer un message\n");
	printf("9 : Retour Menu\n");
	printf("\n-------------------------------------------------------------\n");
	printf("Choix : ");
	scanf("%d", &choix);
	printf("\n\n");
	switch(choix){

		case 1:
			boiteReception(user);
			break;
		case 2:
			envoyerMessage(user);
			break;
		case 9:
			menuconnect(user);
			break;	
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			menuMessagerie(user);
	}
}
void menuAmi(char * user){
	
	int choix;

	printf("##############################################################\n");
	printf("#                       Gestion des amis                     #\n");
	printf("##############################################################\n\n");
	printf("1 : Ajouter un ami\n");
	printf("2 : Supprimer un ami\n");
	printf("9 : Retour Menu\n");
	printf("\n-------------------------------------------------------------\n");
	printf("Choix : ");
	scanf("%d", &choix);
	printf("\n\n");
	switch(choix){

		case 1:
			ajouterAmi(user);
			break;
		case 2:
			supprAmi(user);
			break;
		case 9:
			menuconnect(user);
			break;	
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			menuAmi(user);
	}
}
void menuCompte(char * user){
	
	int choix;

	printf("##############################################################\n");
	printf("#                       Gestion du compte                    #\n");
	printf("##############################################################\n\n");
	printf("1 : Modifier Mot de passe du compte\n");
	printf("2 : Supprimer compte\n");
	printf("9 : Retour Menu\n");
	printf("\n-------------------------------------------------------------\n");
	printf("Choix : ");
	scanf("%d", &choix);
	printf("\n\n");
	switch(choix){

		case 1:
			modifMDP(user);
			break;
		case 2:
			supprCompte(user);
			break;
		case 9:
			menuconnect(user);
			break;	
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			menuCompte(user);
	}
}
