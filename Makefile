#Home Directory
HOME = /home/jsk


#Pythia Directories
PYTHIA8=$(HOME)/pythia8245
PYTHIALIB=$(PYTHIA8)/lib
PYTHIAINC=$(PYTHIA8)/include
PYTHIAINCPYTHIA8=$(PYTHIA8)/include/Pythia8

#HepMC Directories
HEPMC=$(HOME)/hepmc
HEPMCLIB=$(HEPMC)/lib
HEPMCINC=$(HEPMC)/include

#JSON DIRECTORIES
CURRDIR := $(shell pwd)
JSON=$(CURRDIR)/thirdParty/json-develop
JSONINC=$(JSON)/single_include

INCLUDE=-I$(PYTHIAINC) -I./ -I$(PYTHIAINCPYTHIA8) -I./ -I$(HEPMCINC) -I$(JSONINC)
LDLIBS=-Wl,--no-as-needed -ldl

CC=g++
CFLAGS=-std=c++17 -Wno-deprecated-declarations -O2
#LDFLAGS= -lpythia8 -L$(PYTHIALIB) -lz -L$(LDLIBS) -Wl,-rpath,
#LDFLAGS= -lpythia8 -L$(PYTHIALIB) -L$(LDLIBS) -Wl,-rpath,
#LDFLAGS=  -L$(PYTHIALIB) -L$(HEPMCLIB) -Wl,-R$(HEPMCLIB) -L$(LDLIBS)  -lpythia8 -ldl -lz  -lHepMC  #-rpath,
LDFLAGS=  -L$(PYTHIALIB) -L$(HEPMCLIB) -Wl,-R$(HEPMCLIB) -L$(LDLIBS)  -lpythia8 -lz -Wl,-rpath $(PYTHIALIB)   -lHepMC  #-rpath,

SRCDIR=src
HEADDIR=include
LIBDIR=build
BINDIR=bin
TESTDIR=tests

BIN=$(BINDIR)/main
UNITBIN=$(BINDIR)/cyldetlayer_tdd
REGTESTBIN=$(BINDIR)/detector_registry_tdd
SRC=$(shell find . -name '*.cc')
TMP=$(subst $(SRCDIR),$(LIBDIR), $(SRC))
OBJ=$(patsubst %.cc,%.o,$(TMP))

.PHONY: all main clean DetEditor test-cyldetlayer test-detector-geometry test-detector-registry
UTILTESTBIN=$(BINDIR)/detector_geometry_utils_tdd


all: main DetEditor

main: $(BIN)

$(BIN): $(OBJ)
	@[ ! -d $(BINDIR) ] & mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

$(LIBDIR)/%.o: $(SRCDIR)/%.cc
	@[ ! -d $(dir $@) ] & mkdir -p $(dir $@)
	$(CC) -o $@ -c $^ $(INCLUDE) $(CFLAGS)

DetEditor: $(BINDIR)/DetEditor

$(BINDIR)/DetEditor: $(SRCDIR)/DetEditor.cxx
	$(CC) -o $@ -std=c++17 $< -lstdc++fs

test-cyldetlayer: $(UNITBIN)
	$(UNITBIN)

test-detector-geometry: $(UTILTESTBIN)
	$(UTILTESTBIN)

test-detector-registry: $(REGTESTBIN)
	$(REGTESTBIN)

$(UNITBIN): $(TESTDIR)/cyldetlayer_tdd.cpp $(SRCDIR)/CCylSeg.cc $(SRCDIR)/CCylDetLayer.cc
	@[ ! -d $(BINDIR) ] & mkdir -p $(BINDIR)
	$(CC) -std=c++17 -I/opt/homebrew/include -iquote . -o $@ $^

$(UTILTESTBIN): $(TESTDIR)/detector_geometry_utils_tdd.cpp $(SRCDIR)/DetectorGeometryUtils.cc $(SRCDIR)/CCylSeg.cc $(SRCDIR)/CCylDetLayer.cc $(SRCDIR)/CDetector.cc
	@[ ! -d $(BINDIR) ] & mkdir -p $(BINDIR)
	$(CC) -std=c++17 -I/opt/homebrew/include -iquote . -o $@ $^

$(REGTESTBIN): $(TESTDIR)/detector_registry_tdd.cpp
	@[ ! -d $(BINDIR) ] & mkdir -p $(BINDIR)
	$(CC) -std=c++17 -I/opt/homebrew/include -iquote . -o $@ $^

clean:
	rm -rf build bin/main bin/DetEditor $(UNITBIN) $(UTILTESTBIN) $(REGTESTBIN)
