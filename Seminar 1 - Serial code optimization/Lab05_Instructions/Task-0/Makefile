all: mallocycode regularcode sleepycode threadedcode

threadedcode: threadedcode.c
	gcc -g -Wall -lpthread threadedcode.c  -o threadedcode

mallocycode: mallocycode.c
	gcc -g -Wall mallocycode.c -o mallocycode

regularcode: regularcode.c
	gcc -g -Wall regularcode.c -o regularcode

sleepycode: sleepycode.c
	gcc -g -Wall sleepycode.c -o sleepycode

clean:
	rm -rf mallocycode regularcode sleepycode threadedcode