all: servidor_ncurses revision ateoria atodo 

servidor_ncurses: servidor_ncurses.c comun.h comun.c
	cc servidor_ncurses.c -o servidor_ncurses -lncursesw

revision: revision.c comun.h comun.c
	cc revision.c comun.c -o revision

ateoria: ateoria.c comun.h  comun.c comunestudiante.h comunestudiante.c
	cc ateoria.c comun.c comunestudiante.c -o ateoria

atodo: atodo.c comun.h comun.c comunestudiante.h comunestudiante.c
	cc atodo.c comunestudiante.c comun.c -o atodo 
