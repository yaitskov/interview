CC = g++
CFLAGS = -std=c++11
SOURCES = $(filter-out null-or-cycle.cpp, $(wildcard *.cpp))
OUTS = $(patsubst %.cpp, build/%.exe, $(SOURCES))
PROCESSES = $(patsubst %.cpp, %.run, $(SOURCES))
.PHONY: clean all

all: $(PROCESSES) tall
TESTS = $(patsubst %.in,%.test,$(wildcard */*.in))
CODES = $(patsubst %.cpp,%,$(wildcard */code.cpp))

define C_template
build/$(1): $(1).cpp
	mkdir -p $(dir build/$(1))
	$(CC) $(CFLAGS) -o $$@ $$^
endef
$(foreach code, $(CODES), $(eval $(call C_template,$(code))))

define TT_template
$(1): build/$(dir $(1))code
	mkdir -p build/$(dir $(1))
	$$< < $(patsubst %.test,%.in,$(1)) > build/$(patsubst %.test,%.out,$(1))
	cmp build/$(patsubst %.test,%.out,$(1)) $(patsubst %.test,%.exp,$(1))
endef
$(foreach test, $(TESTS), $(eval $(call TT_template,$(test))))

tall: $(TESTS)
	echo "tests passed: [$^]"

%.test: $(dir %.exe)/code.cpp
	echo "$@ : $^"

build: $(OUTS)

clean:
	rm -rf build
%.run: build/%.exe
	./$< || echo -n
build/%.exe: %.cpp
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $<
