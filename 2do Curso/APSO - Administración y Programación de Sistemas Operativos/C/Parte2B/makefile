all: revision servidor_ncurses atodo ateoria profeteoria profetodo

revision: revision.c comun.c comun.h
	cc revision.c comun.c -o revision

servidor_ncurses: servidor_ncurses.c comun.h
	cc servidor_ncurses.c -o servidor_ncurses -lncursesw

atodo: atodo.c comun.h comun.c comunestudiante.c comunestudiante.h
	cc atodo.c comunestudiante.c comun.c -o atodo

ateoria: ateoria.c comun.h comun.c comunestudiante.c comunestudiante.h
	cc ateoria.c comunestudiante.c comun.c -o ateoria

profeteoria: profeteoria.c comun.h comun.c
	cc profeteoria.c comun.c -o profeteoria

profetodo: profetodo.c comun.h comun.c
	cc profetodo.c comun.c -o profetodo

clean:
	rm revision ateoria atodo profeteoria profetodo servidor_ncurses 
