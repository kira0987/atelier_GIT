prog:menu_button.o test.o
	gcc test.o menu_button.o -o test -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
test.o:test.c
	gcc -c test.c -g
menu_button.o:menu_button.c
	gcc -c menu_button.c -g