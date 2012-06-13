#ifndef historique_h
#include "h​istorique.h"
#endif

void test(){
	time_t rowtime;
	char date[11];

	rowtime = getTimeStamp();
	
	printf("time : %ti \n",rowtime);

	getDate(rowtime,date);

	printf("date : %s\n",date);

	getHour(rowtime,date);

	printf("heure : %s",date);
}
