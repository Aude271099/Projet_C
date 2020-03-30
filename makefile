prog: main.o affichage.o fichiers.o fir.o iir.o integration.o lecture.o mesure.o
	gcc -o projet_c.exe main.o affichage.o fichiers.o fir.o iir.o integration.o lecture.o mesure.o

main.o : main.c
	gcc -c -Wall main.c

affichage.o : affichage.c affichage.h
	gcc -c -Wall -g affichage.c

fichiers.o : fichiers.c fichiers.h
	gcc -c -Wall -g fichiers.c

fir.o : fir.c fir.h
	gcc -c -Wall -g fir.c

iir.o : iir.c iir.h
	gcc -c -Wall -g iir.c

integration.o : integration.c integration.h
	gcc -c -Wall -g integration.c

lecture.o : lecture.c lecture.h
	gcc -c -Wall -g lecture.c

mesure.o : mesure.c mesure.h
	gcc -c -Wall -g mesure.c

clean :
	rm prog *.o *.gch *exe