all: mallocycode regularcode sleepycode threadedcode

threadedcode: threadedcode.c
	gcc -c -Wall threadedcode.c -lpthread -o threadedcode

mallocycode: mallocycode.c
	gcc -c -Wall mallocycode.c -o mallocycode

regularcode: regularcode.c
	gcc -c -Wall regularcode.c -o regularcode

sleepycode: sleepycode.c
	gcc -c -Wall sleepycode.c -o sleepycode

clean:
	rm -rf mallocycode regularcode sleepycode threadedcode