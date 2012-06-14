#ifndef message_h
#include "message.h"
#endif

void envoyerMessage(char* user){
	
	char date[11],
	     hour[11],
	     etat[4],
	     dirUser[256] = "",
	     dirMsgDest[256] = "",
	     dirDest[256] = "",
	     fileMsgEnvoye[256] = "",
	     fileMsg[256] = "",
	     fileMsgRecus[256]="",
	     fileExpTmp[256] = "",
	     fileDestTmp[256]="",
	     timestamp[128],
	     destinataire[128],
	     message[256]="",
	     fichier[256] = "",
	     dest[128],
	     exp[128],
	     idMessage[128],
	     histoEnvoi[256] = "",
	     histoRecu[256] = "";

	int choix=0;

	FILE * fic,
	     * ficExp,
	     * ficExpTmp,
	     * ficDest,
	     * ficDestTmp;
	
	printf("#########################\n");
	printf("####     Message     ####\n");
	printf("#########################\n");
	printf("Destinataire : ");
	scanf("%s",destinataire);

	if(amiExist(user,destinataire)==0)
		errorAmi(user,2);
	else{
		printf("#########################\n");
		printf("Message : ");
		clear();
		fgets(message,256,stdin);
		
		printf("#########################\n");
		printf("voulez vous y joindre un fichier?\n");
		printf("1 oui\n");
		printf("2 non\n");
		printf("#########################\n");
		scanf("%d",&choix);
		if(choix==1){
			printf("chemin du fichier: ");
			scanf("%s",fichier);
		}
		printf("#########################\n");
		printf("envoyer le message ? \n");
		printf("1 : oui\n");
		printf("2 : non(message perdu!)\n");
		printf("#########################\n");
		scanf("%d", &choix);
		if(choix==2)
			menuconnect(user);
		else{
			// ---- Ajout du nouveau messages dans les fichiers envoyes.txt et recus.txt de l'expéditeur et du destinataire
			time_t rowtime=getTimeStamp();

			getDate(rowtime,date);
			getHour(rowtime,hour);

			//chemin du dossier de l'expéditeur
			strcat(dirUser, DIR_USERS);
			strcat(dirUser, user);

			// chemon du fichier qui stocks tous les messages envoyé
			strcat(fileMsgEnvoye, dirUser);
			strcat(fileMsgEnvoye, "/envoyes.txt");
			
			//creation et ouverture du fichier temporaire
			strcat(fileExpTmp, dirUser);
			strcat(fileExpTmp, "/envoyesTmp.txt");
			
			ficExpTmp = fopen(fileExpTmp, "a");
			if (ficExpTmp==NULL) {
				printf("fichier temp inexistant\n");
				exit(EXIT_FAILURE);
			}
			
			//ecriture du message
			fprintf(ficExpTmp, "%ti %s %s %s\n", rowtime ,date ,hour ,destinataire );
			
			//chemin vers le destinataire
			strcat(dirDest,DIR_USERS);
			strcat(dirDest,destinataire);
			strcat(fileMsgRecus,dirDest);
			strcat(fileMsgRecus, "/recus.txt");

			//creation du fichier temporaire pour mettre à jour le fichier recus.txt
			strcat(fileDestTmp,dirDest);
			strcat(fileDestTmp, "/recusTmp.txt");

			//ouverture fichier temp
			ficDestTmp = fopen(fileDestTmp, "a");
			
			//ecriture du message
			fprintf(ficDestTmp, "%ti %s %s %s %s\n", rowtime ,date ,hour , user, NL);

			
			//ouverture de envoyes.txt et transfert de son contenu dans le fichier temporaire
			ficExp = fopen(fileMsgEnvoye, "r");
			
			while(fscanf( ficExp,"%s %s %s %s",timestamp ,date ,hour, dest)!=EOF){
				fprintf(ficExpTmp, "%s %s %s %s\n", timestamp ,date ,hour, dest);
			}
			fclose(ficExpTmp);
			fclose(ficExp);
			rename(fileExpTmp,fileMsgEnvoye);
			
			//ouverture recus.txt
			ficDest = fopen(fileMsgRecus, "r");
			
			while(fscanf(ficDest,"%s %s %s %s %s",timestamp,date,hour, exp, etat)!=EOF){
				fprintf(ficDestTmp, "%s %s %s %s %s\n", timestamp, date, hour, exp, etat);
			}
			fclose(ficDestTmp);
			fclose(ficDest);
			rename(fileDestTmp,fileMsgRecus);
			
			
			
			//création du fichier message (idMessage.txt)
			fic = fopen(fileMsgEnvoye, "r");

			fscanf(fic,"%s",idMessage);
			fclose(fic);
			strcat(fileMsg, dirUser);
			strcat(fileMsg, "/");
			strcat(fileMsg, idMessage);
			strcat(fileMsg, ".txt");
			fic = fopen(fileMsg, "w");
			fprintf(fic,"%s\n",destinataire);
			fprintf(fic,"%s\n",message);
			fprintf(fic,"%s\n",fichier);
			fclose(fic);
			
			//creation du fichier massage destinataire
			strcat(dirMsgDest,dirDest);
			strcat(dirMsgDest,"/");
			strcat(dirMsgDest,idMessage);
			strcat(dirMsgDest,".txt");
			fic = fopen(dirMsgDest, "w");
			fprintf(fic,"%s\n",user);
			fprintf(fic,"%s\n",message);
			fprintf(fic,"%s\n",fichier);
			fclose(fic);
			
			//ajout historique envoi d'un message
			strcat(histoEnvoi,"Envoi d'un message à ");
			strcat(histoEnvoi,destinataire);
			addActionWithDate(user,histoEnvoi,rowtime);
			
			//ajout historique recu d'un message
			strcat(histoRecu,"Reception d'un message de ");
			strcat(histoRecu,user);
			addActionWithDate(destinataire,histoRecu,rowtime);

			printf("\n\n");
			printf("#########################\n");
			printf("Message envoye! \n");
			menuconnect(user);
		}
	}
}

int nbMsgEnvoyes(char * user){
	return 0;
}

/**
 * Fonction qui retourne le nombre de message reçus
 * choix : 0 => aucun choix
 * 	 : 1 => nombre de messages non lu
 * 	 : 2 => nombre de messages lu
 */
int nbMsgRecus(char * user, int choix){
	
	char file[256] = "";
	FILE * f;
	Message msg;
	int nb = 0;

	strcat(file, DIR_USERS);
	strcat(file, user);
	strcat(file, FILE_RECUS);

	f = fopen(file, "r");

	while(fscanf(f,"%s %s %s %s %s",msg.id,msg.date,msg.hour, msg.exp, msg.etat)!=EOF){
		switch(choix){
			case 1:
				if(strcasecmp(msg.etat, NL)==0)
					nb++;
				break;
			case 2:
				if(strcasecmp(msg.etat, LU)==0)
					nb++;
				break;
			default:
				nb++;					
		}
	}

	fclose(f);

	return nb;
	
}

void boiteReception(char * user){

	char file[256] 	  = "",
	     pathMsg[256] = "";
	FILE * f;
	int i = 0,
	    choix,
	    status,
	    nb = nbMsgRecus(user, 0);
	
	Message msg[nb];

	strcat(file, DIR_USERS);
	strcat(file, user);
	strcat(file, FILE_RECUS);

	f = fopen(file, "r");

	printf("##############################################################\n");
	printf("#                      Boite de réception                    #\n");
	printf("##############################################################\n\n");

	while(fscanf(f,"%s %s %s %s %s", msg[i].id, msg[i].date, msg[i].hour, msg[i].exp, msg[i].etat)!=EOF){
		printf("%d => %s %s : Message reçu de %s ",(i+1), msg[i].date, msg[i].hour, msg[i].exp);
		if(strcasecmp(msg[i].etat, NL)==0)
			printf("(À LIRE)");
		printf("\n-------------------------------------------------------------\n");
		i++;
	}
	printf("\n Choisissez le message à lire : ");
	scanf("%d", &choix);
	clear();
	if(choix<1 || choix >nb)
		errorChoixMsg(user);
	else {
		if(fork()==0){

			strcat(pathMsg, DIR_USERS);
			strcat(pathMsg, user);
			strcat(pathMsg, "/");
			strcat(pathMsg, msg[choix].id);
			strcat(pathMsg, ".txt");
			execl("/bin/more","more",pathMsg,NULL);
		}
		else{
			wait(&status);
			printf("\n\n");
			menuconnect(user);
		}
	}
	fclose(f);
}

void errorChoixMsg(char * user){
	int choix;

	printf("Le numéro que vous avez insérer n'existe pas!\n\n");
	printf("1 : Try again\n");
	printf("2 : Retour Menu\n");
	scanf("%d", &choix);
	clear();

	switch(choix){
		case 1:
			boiteReception(user);
			break;
		case 2:
			menuconnect(user);
			break;
		default:
			printf("\nUne erreur est survenue!\n");
			printf("Veuillez refaire un choix\n");
			errorChoixMsg(user);

	}
}
