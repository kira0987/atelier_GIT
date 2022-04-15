prog:image.o test.o text.o Settings.o background.o personnage.o enigme_image.o
	gcc test.o image.o text.o Settings.o background.o personnage.o enigme_image.o -o test -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
test.o:test.c
	gcc -c test.c -g
image.o:image.c
	gcc -c image.c -g
text.o:text.c
	gcc -c text.c -g
Settings.o:Settings.c
	gcc -c Settings.c -g
background.o:background.c
	gcc -c background.c -g
personnage.o:personnage.c
	gcc -c personnage.c -g
enigme_image.o:enigme_image.c
	gcc -c enigme_image.c -g 