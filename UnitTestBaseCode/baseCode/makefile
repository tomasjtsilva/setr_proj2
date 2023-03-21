#Esta  a makefile para o projeto FIFO de SETR
#Gerar o executavel(aplicaço)
app1: main.o cmdproc.o
	gcc -o main main.o cmdproc.o

#Gerar cmdproc.o
FIFO.o: cmdproc.c cmdproc.h
	gcc -c cmdproc.c
	
#Gerar o main.o
main.o: main.c
	gcc -c main.c
	
clean:
	rm *.o
