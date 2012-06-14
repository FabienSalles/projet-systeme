#define historique_h

static char * DIR_HISTORIQUES = "historiques/";

void addAction(char * user, char * action);
void addActionWithDate(char * user, char * action, time_t timestamp);
