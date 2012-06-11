#include "main.h"
#include "utilisateur.c"


int main(){
	
	menu();
	
	return  0;
	
}

void menu(){
	char choix[2];
	
	printf("############################\n");
	printf("####       Accueil      ####\n");
	printf("1 : S'inscrire\n");
	printf("2 : S'authentifier\n");
	printf("3 : Quitter\n");
	printf("############################\n");
	printf("Choix : ");
	if (fgets(choix, 2, stdin) == NULL)
		exit(EXIT_FAILURE);

	switch(choix[0]){
		case '1':
			inscription();
			break;
		case '2':
			auth();
			break;
		case '3':
			exit(EXIT_SUCCESS);
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			menu();
	}
}

