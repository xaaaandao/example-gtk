all:
	gcc `pkg-config --cflags gtk+-3.0` teste.c -o teste.exe `pkg-config --libs gtk+-3.0`
