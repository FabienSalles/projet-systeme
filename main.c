#include "main.h"
#include "utilisateur.c"


int main(int argc, char * argv[]){
	
	menu();
	//inscription();
	return  0;
	
}

void menu(){
	char choix;
	
	printf("############################\n");
	printf("####       Accueil      ####\n");
	printf("1 : S'inscrire\n");
	printf("2 : S'authentifier\n");
	printf("3 : Quitter\n");
	printf("############################\n");
	printf("Choix : ");
	scanf("%c", &choix);
	printf("\n\n");
	switch(choix){
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

