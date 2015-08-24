all: build
build:
	gcc -g -Wno-write-strings -o linux-scanner -L. main.cpp
	chmod 755 linux-scanner
clean:
	rm linux-scanner || true
