#define ami_h

void ajouterAmi(char * user);
void supprAmi(char * user);
int amiExist(char* user,char nom[128]);
void errorAjoutAmi(char* user);
void errorAmi(char* user,int from);
