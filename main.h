#define main_h

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/wait.h>

#include "date.h"
#include "utilisateur.h"
#include "ami.h"
#include "historique.h"
#include "message.h"

void menu();
void menuconnect(char * user);

static char * FILE_USERS = "users.txt";
static char * DIR_USERS = "users/";
static char * DIR_HISTORIQUES = "historiques/";

#include "date.c"
#include "utilisateur.c"
#include "ami.c"
#include "historique.c"
#include "message.c"
