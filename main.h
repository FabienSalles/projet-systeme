#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void accueil();
void menu();
void menuconect();

static char * fileUser = "users.txt";
