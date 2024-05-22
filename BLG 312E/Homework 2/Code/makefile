threaded:
	gcc -Wall -Werror threaded.c thread_head.c -I ./ -o threaded -pthread

processed:
	gcc -Wall -Werror processed.c process_head.c -I ./ -o processed -pthread

threaded_benchmark:
	gcc -std=c11 -Wall -Werror threaded_benchmark.c thread_head.c -I ./ -o threaded_benchmark -pthread

processed_benchmark:
	gcc -std=c11 -Wall -Werror processed_benchmark.c process_head.c -I ./ -o processed_benchmark -pthread