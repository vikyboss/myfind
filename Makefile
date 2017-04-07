myfind: myfind.c
	c99 -o $@ $^ -Wall

test: myfind
	mkdir -p test
	mkdir -p test/a
	mkdir -p test/b
	touch test/a/1
	touch test/b/1
	touch test/c
	@echo "*********** STARTING TEST ***********"
	./myfind test
	@echo "***********  ENDING TEST  ***********"
	@echo "*********** STARTING TEST ***********"
	./myfind test test test/c test/a/1
	@echo "***********  ENDING TEST  ***********"

clean:
	rm -f myfind
	rm -rf  test
