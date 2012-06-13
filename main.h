#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "utilisateur.h"
#include "ami.h"

void menu();
void menuconect(Utilisateur user);

static char * FILE_USERS = "users.txt";
static char * DIR_USERS = "users/";
static char * DIR_HISTORIQUES = "historiques/";

#include "utilisateur.c"
#include "ami.c"
