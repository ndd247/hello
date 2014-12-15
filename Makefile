SOURCES=$(wildcard *.cpp)
TARGETS=$(SOURCES:.cpp=)

OPTS=-O3

%: %.cpp
	g++ $(OPTS) -o $@ $<

all: $(TARGETS)
	@echo $(SOURCES)
	@echo $(TARGETS)
