CC = gcc
CFLAGS = --std=c99 -Wall -Werror -Iinclude

APP_NAME = main

DEPS = $(wildcard include/*.h)
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
TESTS = $(wildcard tests/*.c)
TEST_OBJ = $(TESTS:.c=)

obj/%.o: src/%.c $(DEPS)
	mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

install:
	sudo apt update
	sudo apt upgrade -y
	sudo apt install valgrind -y
	sudo apt install doxygen -y
	python -m venv venv
	source venv/bin/activate
	pip install -r requirements.txt

all: compile-app compile-tests

compile-app: $(APP_NAME)

compile-tests: $(TEST_OBJ)

$(APP_NAME): $(OBJ)
	mkdir -p bin/app
	$(CC) -o bin/app/$(APP_NAME) $^ $(CFLAGS)

tests/%: tests/%.c $(DEPS) $(filter-out src/main.c, $(SRC))
	mkdir -p bin/tests
	$(CC) -o bin/tests/$* $^ $(CFLAGS)

launch-app:
	valgrind --leak-check=full --show-leak-kinds=all -s ./bin/app/$(APP_NAME)

launch-tests:
	for test in bin/tests/*; do $$test upload/map.txt; done

doc:
	doxygen Doxyfile
	cd doc/latex/ && make
	cd ../..
	cp doc/latex/refman.pdf doc/doc.pdf

clean-obj:
	rm -f obj/*.o

clean-exe:
	rm -f bin/app/$(APP_NAME)
	rm -f bin/tests/*

clean-cvs:
	rm -f data/csv/*

clean-plot:
	rm -f data/plot/*

clean-generated:
	rm -f generated/*

clean-upload:
	rm -f upload/*

clean-doc:
	rm -f doc/*

full-clean: clean-obj clean-exe clean-cvs clean-plot clean-generated clean-upload clean-doc

git-push:
	git add .
	read -p "Enter commit message: " message; \
	git commit -m "$$message"
	git push

.PHONY: all compile-app compile-tests launch-app launch-tests doc clean-obj clean-exe clean-cvs clean-plot clean-generated clean-upload clean-doc full-clean git-push
