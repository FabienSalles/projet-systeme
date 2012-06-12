typedef struct utilisateur{
	char nom[128];
	char password[128];
} Utilisateur;

void inscription();
void auth();
int exist(char nom[100], char mdp[100]);
