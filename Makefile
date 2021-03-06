###########################################
##        Make File projet System        ##
###########################################

CFLAGS		= -Wall
MAIN  		= main.c
EXE		= exe
HISTORIQUE_DIR	= historiques/
USERS_DIR	= users/
USERS_FILE	= users.txt

exec:
	gcc ${CFLAGS} ${MAIN} -o ${EXE}

.PHONY: reset

reset:
	rm -rf ${HISTORIQUE_DIR}* ${USERS_DIR}* ${USERS_FILE}
	touch ${USERS_FILE}
	chmod 777 -R *
