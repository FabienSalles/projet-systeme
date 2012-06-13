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
	printf("############################\n");
	printf("####       Accueil      ####\n");
	printf("############################\n");
	printf("1 : S'inscrire\n");
	printf("2 : S'authentifier\n");
	printf("3 : Quitter\n");
	printf("############################\n");
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
		case 3:
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

	printf("############################\n");
	printf("####        Menu        ####\n");
	printf("############################\n");
	printf("1 : Afficher mur\n");
	printf("2 : Envoyer un message\n");
	printf("3 : Boite de reception\n");
	printf("4 : Ajouter un ami\n");
	printf("5 : Supprimer un ami\n");
	printf("6 : Historique\n");
	printf("7 : Modifier compte\n");
	printf("8 : Supprimer compte\n");
	printf("9 : Deconnexion\n");
	printf("0 : Quitter\n");
	printf("############################\n");
	printf("Choix : ");
	scanf("%d", &choix);
	printf("\n\n");
	switch(choix){

		case 1:
			menuconnect(user);
			break;
		case 2:
			envoyerMessage(user);
			break;
		case 3:
			menuconnect(user);
			break;
		case 4:
			ajouterAmi(user);
			break;
		case 5:
			supprAmi(user);
			break;
		case 6:
			test();
			break;
		case 7:
			menuconnect(user);
			break;
		case 8:
			menuconnect(user);
			break;
		case 9:
			menu();
			break;
		case 0:
			exit(EXIT_SUCCESS);
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			menuconnect(user);
	}
}
