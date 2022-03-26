all: compila
compila:
	clear
	g++ -o trabalhocg *.cpp -lGL -lGLU -lglut
clean:
	rm -rf *.o

	