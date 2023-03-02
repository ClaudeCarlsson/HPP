all: threads_doing_work 

threads_doing_work: threads_doing_work.c
	gcc -fopenmp threads_doing_work.c -o threads_doing_work

clean:
	rm -rf threads_doing_work