name := BDS_run
G4TARGET := $(name)
G4EXLIB := true

G4BINDIR := .

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin

ROOTLIBS=`$(ROOTSYS)/bin/root-config --libs`
ROOTINCS=`$(ROOTSYS)/bin/root-config --cflags`

LDLIBS3 += $(ROOTLIBS)

include $(G4INSTALL)/config/binmake.gmk

# JCC removed to make look like GB's GNUmakefile
CPPFLAGS += -Df2cFortran
CPPFLAGS += -I$(CERN)/pro/include -g

CPPFLAGS += -w 
LDFLAGS += -L$(G4LIBDIR) -L$(CERN)/pro/lib 


# gab:Root include:
INCFLAGS += -I$(ROOTSYS)/include

test:
	@echo LDLIBS3=$(LDLIBS3)
	@echo CERN=$(CERN)
