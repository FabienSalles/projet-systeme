void ajouterAmi(char * user){
	FILE * fic;

	char nom[128],
	     fileAmi[256] = "";

	printf("############################\n");
	printf("####   Ajouter un ami   ####\n");
	printf("Nom : ");
	scanf("%s",nom);

	if(userExist(nom, NULL)){
		
		// ajout de l'ami dans le fichier ami de l'utilisateur	
		strcat(fileAmi, DIR_USERS);
		strcat(fileAmi, user);
		strcat(fileAmi, "/amis.txt");
		fic = fopen(fileAmi, "a");

		fprintf(fic, "%s\n", nom);
		fclose(fic);
	}
	else {
		printf("\nLe nom de votre ami n'existe pas!\n");
		printf("Veuillez resaisir le nom d'utilisateur!\n\n");
	}
}

void supprAmi(char * user){

}

