#define message_h

typedef struct message{

	time_t timestamp;

	char id[24],
	     dest[128],
	     exp[128],
	     date[11],
	     hour[11],
	     etat[2],
	     message[1000],
	     pathMsg[256];

} Message;

#define FILE_ENVOYES "/envoyes.txt"
#define FILE_RECUS   "/recus.txt"
#define NL	     "NL"
#define LU 	     "LU"
 	
void envoyerMessage(char* user);
int nbMsgEnvoyes(char * user);
int nbMsgRecus(char * user, int choix);
void boiteReception(char * user);
void errorChoixMsg(char * user);
void messageLu(char * user, char * id);

