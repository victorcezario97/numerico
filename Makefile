all:
	gcc -o main main.c -Wall -lm
run:
	./main
clean:
	rm main
