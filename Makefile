.PHONY: myfind
myfind: myfind.c
	$(CC) -o $@ $^ -Wall -Werror

.PHONY: test
test: myfind
	@echo "*********** STARTING TEST SETUP ***********"
	mkdir -p test
	mkdir -p test/a
	mkdir -p test/b
	touch test/a/1
	touch test/b/1
	touch test/c
	@echo "*********** ENDING TEST SETUP ***********"
	@echo ""
	@echo "*********** STARTING TEST 1 ***********"
	./myfind test
	@echo "***********  ENDING TEST 1  ***********"
	@echo ""
	@echo "*********** STARTING TEST 2 ***********"
	./myfind test test test/c test/a/1
	@echo "***********  ENDING TEST  2 ***********"

.PHONY: clean
clean:
	rm -f myfind
	rm -rf  test
