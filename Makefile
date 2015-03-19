CC = g++
CFLAGS = -std=c++11
SOURCES = $(filter-out null-or-cycle.cpp, $(wildcard *.cpp))
OUTS = $(patsubst %.cpp, %.exe, $(SOURCES))
PROCESSES = $(patsubst %.cpp, %.run, $(SOURCES))
.PHONY: clean all

all: $(PROCESSES) tall
TESTS = $(patsubst %.in,%.test,$(wildcard */*.in))
CODES = $(patsubst %.cpp,%,$(wildcard */code.cpp))

define C_template
$(1): $(1).cpp
	$(CC) $(CFLAGS) -o $$@ $$^
endef
$(foreach code, $(CODES), $(eval $(call C_template,$(code))))

define TT_template
$(1): $(dir $(1))code
	$$< < $(patsubst %.test, %.in, $(1)) > $(patsubst %.test, %.out, $(1))
	cmp $(patsubst %.test, %.out, $(1)) $(patsubst %.test, %.exp, $(1))
endef
$(foreach test, $(TESTS), $(eval $(call TT_template,$(test))))

tall: $(TESTS)
	echo "tests passed: [$^]"

%.test: $(dir %.exe)/code.cpp
	echo "$@ : $^"

build: $(OUTS)

clean:
	find \( -name '*.exe' -o -name '*.out' -o -name 'code' \) -type f  -exec rm -rf {} \;
%.run: %.exe
	./$< || echo -n

%.exe: %.cpp
	$(CC) $(CFLAGS) -o $@ $<
