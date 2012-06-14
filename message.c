#ifndef message_h
#include "message.h"
#endif
void envoyerMessage(char* user){
	
	time_t rowtime=getTimeStamp();
	char date[11];
	char hour[11];
	char dirUser[256] = "",dirMsgDest[256] = "",dirDest[256] = "";
	char fileMsgEnvoye[256] = "",fileMsg[256] = "",fileMsgRecus[256]="";
	char fileTmp[256] = "",fileDestTmp[256]="";
	char copyTimestamp[128],copyDate[128],copyHour[128],destinataire[128];
	char message[256]="",fichier[256] = "";
	char idMessage[128];
	char histoEnvoi[256]="",histoRecu[256] = "";
	int choix=0;
	FILE * fic;
	FILE * ficTmp;
	getDate(rowtime,date);
	getHour(rowtime,hour);
	
	printf("#########################\n");
	printf("####     Message     ####\n");
	printf("#########################\n");
	printf("Destinataire : ");
	scanf("%s",destinataire);
	if(amiExist(user,destinataire)==0){
		errorAmi(user,2);
	}
	else{
		printf("#########################\n");
		printf("Message : ");
		
			while(getchar()!='\n');//flush stdin
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
		printf("envoyer le message? \n");
		printf("1 : oui\n");
		printf("2 : non(message perdu!)\n");
		printf("#########################\n");
		scanf("%d", &choix);
		if(choix==2){
			menuconnect(user);
		}
		else{
			strcat(dirUser, DIR_USERS);
			strcat(dirUser, user);
			strcat(fileMsgEnvoye, dirUser);
			strcat(fileMsgEnvoye, "/envoyes.txt");
			strcat(fileTmp, dirUser);
			
			
			//creation du fichier temporaire
			strcat(fileTmp, "/envoyesTmp.txt");
			ficTmp = fopen(fileTmp, "w");
			fclose(ficTmp);
			
			//ouverture fichier temp
			ficTmp = fopen(fileTmp, "a");
			if (ficTmp==NULL) {
				printf("fichier temp inexistant\n");
				exit(0);
			}
			
			//ecriture du message
			fprintf(ficTmp, "%ti %s %s\n", rowtime,date,hour);
			
			//ouverture envoyes.txt
			fic = fopen(fileMsgEnvoye, "r");
			if (fic==NULL) {
				printf("fichier envoyes.txt inexistant\n");
				exit(0);
			}
			
			while(fscanf(fic,"%s %s %s",copyTimestamp,copyDate,copyHour)!=EOF){
				fprintf(ficTmp, "%s %s %s\n", copyTimestamp,copyDate,copyHour);
			}
			fclose(ficTmp);
			fclose(fic);
			rename(fileTmp,fileMsgEnvoye);
			
			strcat(dirDest,DIR_USERS);
			strcat(dirDest,destinataire);
			strcat(fileMsgRecus,dirDest);
			strcat(fileMsgRecus, "/recus.txt");
			//creation du fichier temporaire
			strcat(fileDestTmp,dirDest);
			strcat(fileDestTmp, "/recusTmp.txt");
			ficTmp = fopen(fileDestTmp, "w");
			fclose(ficTmp);
			//ouverture fichier temp
			ficTmp = fopen(fileDestTmp, "a");
			if (ficTmp==NULL) {
				printf("fichier temp inexistant\n");
				exit(0);
			}
			
			//ecriture du message
			fprintf(ficTmp, "%ti %s %s\n", rowtime,date,hour);
			
			//ouverture envoyes.txt
			fic = fopen(fileMsgRecus, "r");
			if (fic==NULL) {
				printf("fichier envoyes.txt inexistant\n");
				exit(0);
			}
			
			while(fscanf(fic,"%s %s %s",copyTimestamp,copyDate,copyHour)!=EOF){
				fprintf(ficTmp, "%s %s %s\n", copyTimestamp,copyDate,copyHour);
			}
			fclose(ficTmp);
			fclose(fic);
			rename(fileDestTmp,fileMsgRecus);
			
			
			
			//création du fichier message (idMessage.txt)
			fic = fopen(fileMsgEnvoye, "r");
			if (fic==NULL) {
				printf("fichier envoyes.txt inexistant\n");
				exit(0);
			}
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
			printf("#########################\n");
			printf("Message envoye! \n");
			
			//ajout historique envoi d'un message
			strcat(histoEnvoi,"Envoi d'un message à ");
			strcat(histoEnvoi,destinataire);
			addActionWithDate(user,histoEnvoi,rowtime);
			
			//ajout historique recu d'un message
			strcat(histoRecu,"Reception d'un message de ");
			strcat(histoRecu,user);
			addActionWithDate(destinataire,histoRecu,rowtime);
			
			printf("\n\n");
			menuconnect(user);
		}
	}
}
