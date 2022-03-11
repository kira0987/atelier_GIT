prog:image.o test.o text.o Settings.o
	gcc test.o image.o text.o Settings.o -o test -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
test.o:test.c
	gcc -c test.c -g
image.o:image.c
	gcc -c image.c -g
text.o:text.c
	gcc -c text.c -g
Settings.o:Settings.c
	gcc -c Settings.c -g