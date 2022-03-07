SHELL = bash
PROJNM = conpalette

SRCDIR = src
INCDIR = $(SRCDIR)/include
LIBDIR = $(SRCDIR)/lib
DBGDIR = debug
DBGDYNDIR = $(DBGDIR)/dynamic
DBGSTCDIR = $(DBGDIR)/static
RELDIR = release
RELDYNDIR = $(RELDIR)/dynamic
RELSTCDIR = $(RELDIR)/static
TSTDIR = test
TSTDYNDIR = $(TSTDIR)/dynamic
TSTSTCDIR = $(TSTDIR)/static

MAINNM = main
MAINEX = cpp
MAINFL = $(MAINNM).$(MAINEX)

SRCFLS = $(wildcard $(SRCDIR)/*.cpp)
OBJSRC = $(wildcard $(INCDIR)/*.cpp)
OBJOBJ = $(subst include,lib,$(patsubst %.cpp,%.o,$(OBJSRC)))
DBGDYN = $(DBGDYNDIR)/$(PROJNM)
DBGSTC = $(DBGSTCDIR)/$(PROJNM)
TGTDYN = $(RELDYNDIR)/$(PROJNM)
TGTSTC = $(RELSTCDIR)/$(PROJNM)
TSTDYN = $(TSTDYNDIR)/$(PROJNM)
TSTSTC = $(TSTSTCDIR)/$(PROJNM)

TSTEXE = $(TSTDYN) # or $(TSTSTC)
TSTARG = # --help # $(TSTEXE)

# GTKINC = $(shell pkg-config gtkmm-3.0 --cflags)
# GTKLIB = $(shell pkg-config gtkmm-3.0 --libs)

LDFLAG = -I$(INCDIR) -O3 -std=c++17
# LDLIBS = -L$(LIBDIR) -l$(PROJNM)

DBGFLG = -ggdb -Wall -Wextra -std=c++17

SNFLGS = 	-fsanitize=undefined \
			   	-fno-sanitize-recover=all -fsanitize=float-divide-by-zero \
				 	-fsanitize=float-cast-overflow -fno-sanitize=null \
				 	-fno-sanitize=alignment -std=c++17

SNFLGD = $(SNFLGS) -fsanitize=address

STFLAG = -static -static-libgcc -static-libstdc++

all: releasedynamicall

releasedynamicall: cleanreleasedynamic builddirectories buildlibs
	@echo Building dynamic executable
	$(CXX) $(GTKINC) $(LDFLAG) $(SRCFLS) -o $(TGTDYN) $(LDLIBS) $(GTKLIB)

releasedynamic: cleanreleasedynamic builddirectories
	@echo Building dynamic executable
	$(CXX) $(GTKINC) $(LDFLAG) $(SRCFLS) -o $(TGTDYN) $(LDLIBS) $(GTKLIB)

releasestaticall: cleanreleasestatic builddirectories buildlibs
	@echo Building static executable
	$(CXX) $(GTKINC) $(STFLAG) $(LDFLAG) $(SRCFLS) -o $(TGTSTC) $(LDLIBS) $(GTKLIB)

releasestatic: cleanreleasestatic builddirectories
	@echo Building static executable
	$(CXX) $(GTKINC) $(STFLAG) $(LDFLAG) $(SRCFLS) -o $(TGTSTC) $(LDLIBS) $(GTKLIB)

debugdynamicall: cleandebugdynamic builddirectories buildlibs
	@echo Building debug executable
	$(CXX) $(GTKINC) -I$(INCDIR) -std=c++17 $(DBGFLG) $(SRCFLS) -o $(DBGDYN) $(LDLIBS) $(GTKLIB)

debugdynamic: cleandebugdynamic builddirectories
	@echo Building debug executable
	$(CXX) $(GTKINC) -I$(INCDIR) $(DBGFLG) $(SRCFLS) -o $(DBGDYN) $(LDLIBS) $(GTKLIB)

debugstaticall: cleandebugstatic builddirectories buildlibs
	@echo Building debug executable
	$(CXX) $(STFLAG) $(GTKINC) -I$(INCDIR) -std=c++17 $(DBGFLG) $(SRCFLS) -o $(DBGSTC) $(LDLIBS) $(GTKLIB)

debugstatic: cleandebugstatic builddirectories
	@echo Building debug executable
	$(CXX) $(STFLAG) $(GTKINC) -I$(INCDIR) $(DBGFLG) $(SRCFLS) -o $(DBGSTC) $(GTKLIB) $(LDLIBS) $(GTKLIB)

debugbuilds: debugdynamic debugstatic

releasebuilds: releasedynamic releasestatic

allbuilds: debugbuilds releasebuilds

.PHONY: test

test:
	@echo Running test of $(TSTEXE)
	./$(TSTEXE) $(TSTARG)

buildlibs: buildallobjects buildarchive

buildallobjects: cleanobjects
	@echo Building object files from $(INCDIR) to $(LIBDIR)
	$(shell IFS=$(echo -en "\n\b") array=( $(OBJSRC) );\
		for file in "$${array[@]}";do \
			lib=$${file//include/lib}; \
			lib=$${lib//.cpp/.o}; \
			$(CXX) $(GTKINC) $(LDFLAG) -c $${file} -o $${lib} $(LDLIBS) $(GTKLIB); \
		done \
	)

buildarchive: cleanarchive
	@echo Building object archive
	ar rcs $(LIBDIR)/lib$(PROJNM).a $(OBJOBJ)

builddirectories:
	@echo Building project directories
	$(shell \
	mkdir -p $(INCDIR) $(LIBDIR) \
	$(DBGDYNDIR) $(DBGSTCDIR) \
	$(RELDYNDIR) $(RELSTCDIR) \
	$(TSTDYNDIR) $(TSTSTCDIR) \
	)

clean: cleanrelease cleandebug cleantest cleanobjects cleanarchive

cleanrelease: cleanreleasedynamic cleanreleasestatic

cleanreleasedynamic:
	@echo Cleaning dynamic release
	rm -f $(TGTDYN)

cleanreleasestatic:
	@echo Cleaning static release
	rm -f $(TGTSTC)

cleandebug: cleandebugdynamic cleandebugstatic

cleandebugdynamic:
	@echo Cleaning dynamic debug
	rm -f $(DBGDYN)

cleandebugstatic:
	@echo Cleaning static debug
	rm -f $(DBGSTC)

cleantest: cleantestdynamic cleanteststatic

cleantestdynamic:
	@echo Cleaning dynamic test
	rm -f $(TSTDYN)

cleanteststatic:
	@echo Cleaning static test
	rm -f $(TSTSTC)

cleanobjects:
	@echo Cleaning objects
	rm -f $(LIBDIR)/*.o

cleanarchive:
	@echo Cleaning archive
	rm -f $(LIBDIR)/*.a

install: installdynamic

installdynamic:
	@echo Installing $(PROJNM)
	cp -f $(TGTDYN) /usr/bin/$(PROJNM)

installstatic:
	@echo Installing $(PROJNM)
	cp -f $(TGTSTC) /usr/bin/$(PROJNM)
