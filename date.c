#ifndef date_h
#include "date.h"
#endif

time_t getTimeStamp(){
	time_t timestamp;
	
	time(&timestamp);
	return timestamp;
}
void getDate(time_t timestamp, char * date){
	struct tm * timeinfo;

	timeinfo = localtime(&timestamp);
	strftime(date, 11, "%d/%m/%Y",timeinfo);

}

void getHour(time_t timestamp, char * heure){
	struct tm * timeinfo;

	timeinfo = localtime(&timestamp);
	strftime(heure, 11, "%H:%M:%S",timeinfo);

}
