all: build
build:
	gcc -L/usr/lib/x86_64-linux-gnu/ -I/usr/include -Wno-write-strings -o linux-scanner main.cpp -lsane
	chmod 755 linux-scanner
clean:
	rm linux-scanner || true
