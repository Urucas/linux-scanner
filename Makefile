all: build
build:
	gcc -o linux-scanner main.cpp
clean:
	rm linux-scanner
