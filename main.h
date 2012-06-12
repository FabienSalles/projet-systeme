#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void accueil();
void menu();
void menuconect();

static char * FILE_USERS = "users.txt";
static char * DIR_USERS = "users/";
