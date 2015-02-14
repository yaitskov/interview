CC = g++
SOURCES = $(wildcard *.cpp)
OUTS = $(patsubst %.cpp, %.exe, $(SOURCES))
PROCESSES = $(patsubst %.cpp, %.run, $(SOURCES))
.PHONY: clean all

all: $(PROCESSES)

build: $(OUTS)

clean:
	rm -rf *.exe
%.run: %.exe
	$< || echo -n

%.exe: %.cpp
	$(CC) -std=c++11 -o $@ $<
