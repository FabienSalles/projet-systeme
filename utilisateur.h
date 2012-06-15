#define utilisateur_h

typedef struct utilisateur{
	char nom[128];
	char password[128];
} Utilisateur;

static char * FILE_USERS = "users.txt";
static char * DIR_USERS = "users/";

Utilisateur inscription();
Utilisateur auth();
int userExist(char * nom, char * password);
void errorUserExist();
void modifMDP(char* user);
void deconnexion(char* user);
void afficheMurAmi(char* user);
void supprCompte(char* user);
