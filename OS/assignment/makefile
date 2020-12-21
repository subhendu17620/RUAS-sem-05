all:
	@gcc -pthread matrix_sum.c

run-parallel:
	@./a.out --parallel -O4

run-sequential:
	@./a.out --sequential -O4

debug:
	@gcc -pthread -g matrix_sum.c

clean:
	@rm -r a.out

.PHONY: clean


