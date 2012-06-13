typedef struct utilisateur{
	char nom[128];
	char password[128];
} Utilisateur;

Utilisateur inscription();
Utilisateur auth();
int exist(char * nom, char * password);
void errorExist();
