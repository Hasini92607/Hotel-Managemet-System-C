a.out : main.o mylib.so functions.h 
	gcc main.o -L. mylib.so 
main.o : main.c
	gcc -c main.c
mylib.so : mylib.o
	gcc -shared -o mylib.so mylib.o
mylib.o : mylib.c
	gcc -fPIC -c mylib.c
clean :
	rm *.o a.out *.txt