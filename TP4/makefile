COMPILER=g++
CPPFLAGS=-w -Wall
LINKER=@g++
LINKERFLAGS=
INCPATH=
LIBPATH=

ECHO=@echo
CLEAN=clean

SRCDIR=src
OUTPUTDIR=build
EXE=analog

FILES=ApacheLogParser.h Date.h GraphGenerator.h LinkUriReferer.h LogAnalyser.h LogEntry.h
HEADERS=$(addprefix $(SRCDIR)/,$(FILES))
IMPL=$(HEADERS:.h=.cpp)

OBJ=$(addprefix $(OUTPUTDIR)/,$(FILES:.h=.o))
OBJ+=$(OUTPUTDIR)/TP4.o

.PHONY: $(CLEAN)

# Ouput executable
$(EXE): $(OBJ)
	$(ECHO) Linking $(EXE)...
	$(LINKER) $(LINKERFLAGS) $(INCPATH) -o $(OUTPUTDIR)/$(EXE) $(OBJ) $(LIBS)

# Generic rule
$(OUTPUTDIR)/%.o: $(SRCDIR)/%.cpp
	$(ECHO) Compiling $<...
	$(COMPILER) $(CPPFLAGS) $(INCPATH) -o $@ -c $<
# Explicit dependancies
$(OUTPUTDIR)/ApacheLogParser.o: $(SRCDIR)/LogEntry.h
$(OUTPUTDIR)/GraphGenerator.o: $(SRCDIR)/LogAnalyser.h
$(OUTPUTDIR)/LogAnalyser.o: $(SRCDIR)/LogEntry.h $(SRCDIR)/ApacheLogParser.h $(SRCDIR)/LogAnalyserTypes.h
$(OUTPUTDIR)/LogEntry.o: $(SRCDIR)/Date.h
$(OUTPUTDIR)/TP4.o: $(SRCDIR)/LogAnalyser.h $(SRCDIR)/GraphGenerator.h

$(CLEAN):
	$(ECHO) Cleaning project.
	rm -f $(OBJ) $(OUTPUTDIR)/$(EXE) core
