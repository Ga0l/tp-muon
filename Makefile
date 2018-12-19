ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)

CXX = g++ 
CXXFLAGS = -g -Wall $(ROOTCFLAGS)
CINT	  = rootcint

LIBS = -lm $(ROOTLIBS) -lTreePlayer -lMinuit  $(SYSLIBS)

INCFLAGS      = -I.  
CXXFLAGS     += $(INCFLAGS)

FILESRC = $(wildcard *.cpp)
FILEOBJ = $(patsubst %.cpp,%.o,$(FILESRC) )
FILEINC = $(wildcard *.h)

EXESRC =  $(wildcard *.cxx)
EXEOBJ =  $(patsubst %.cxx,%_x,$(EXESRC) )

default: all

all: obj  exe
obj: $(FILEOBJ)
exe: $(EXEOBJ)

%.o: %.cpp %.h
	@echo "Building object : " $@
	$(CXX) -fPIC $(CXXFLAGS) -o $@ -c $<

%_x: %.cxx
	@echo "Building executable : " $@
	$(CXX) $(CXXFLAGS) -o $@ $? *.o $(LIBS) 
clean:
	@echo "Deleting compiled files"
	@rm -f *.o
	@rm -f *_x
