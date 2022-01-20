FLAGS := -std=c++11 -O3 -Wall -lm

.PHONY: compile run clean

compile: project

project: project.cpp
	g++ project.cpp -o project $(FLAGS)

run: compile
	./project

clean:
	rm project