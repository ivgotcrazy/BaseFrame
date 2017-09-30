#############################################################################
## Customizable Section: adapt those variables to suit your program.
##==========================================================================

# Main config.
OUTPUT_LIBDIR	:= ../../../
OUTPUT_BINDIR	:= ../../../
GROUPNAME	:= BaseFrame/bin/linux
PROJECTNAME	:= baseframe

# The pre-processor and compiler options.
# Users can override those variables from the command line.
COMMONFLAGS 	:= -fPIC -Wl,-Bsymbolic -D_LINUX -m64 -Wa,--noexecstack -z,defs
CFLAGS      	:= $(COMMONFLAGS)
CXXFLAGS    	:= $(COMMONFLAGS) -Wl,--no-undefined -Wl,-z,relro -Wl,-z,now -fno-exceptions -std=c++11
DEBUG_CXXFLAGS  := ${CXXFLAGS} -O0 -g -DDEBUG -D_DEBUG
RELEASE_CXXFLAGS:= ${CXXFLAGS} -O2 -g -DNDEBUG

# The options used in linking as well as in any direct use of ld.
COMMON_LDFLAGS	:= -Wl,-z,defs,-Bsymbolic
LDFLAGS   	+= $(COMMON_LDFLAGS) -shared

# The pre-processor and compiler options.
ifeq (YES, ${DEBUG})
	MY_CFLAGS = ${INCLUDEDIR}
else
	MY_CFLAGS = ${INCLUDEDIR}
endif

# The linker options.
ifeq (YES, ${DEBUG})
	MY_LIBS  := 
else
	MY_LIBS  := 
endif
MY_LIBS  += ${EXTRA_LIBS}

# The pre-processor options used by the cpp (man cpp for more).
ifeq (YES, ${DEBUG})
	CPPFLAGS  = ${INCLUDEDIR} ${DEBUG_CXXFLAGS}
else
	CPPFLAGS  = ${INCLUDEDIR} ${RELEASE_CXXFLAGS}
endif

# Include files.
INCLUDEDIR  :=	-I ../../include \
		-I ../../src/core \
		-I ../../src/linux

# The files will be excluded
EXCLUDES  =  

# The directories in which source files reside.Character '/' at the end of directories is forbidden,because it
# will lead to failure of filter-out excluded files.  
SRCDIRS   = ../../src/core ../../src/linux

# The target file name.
ifeq (YES, ${DEBUG})
	OUTPUT   = ${OUTPUT_BINDIR}${GROUPNAME}/lib${PROJECTNAME}D.so
else
	OUTPUT   = ${OUTPUT_BINDIR}${GROUPNAME}/lib${PROJECTNAME}.so
endif

## Implicit Section: change the following only when necessary.
##==========================================================================

# The source file types (headers excluded).
# .c indicates C source files, and others C++ ones.
SRCEXTS = .c .C .cc .cpp .CPP .c++

# The header file types.
HDREXTS = .h .H .hh .hpp .HPP .h++


# The C program compiler.
CC     = gcc

# The C++ program compiler.
CXX    = g++

# Un-comment the following line to compile C programs as C++ ones.
#CC     = $(CXX)

# The command used to delete file.
RM     = rm -f

# The command used to generate timestamp.
DATE   = `date '+%Y%m%d-%H%M%S'`

# The command used to pack
TAR    = tar -zcf

# The command used to create archives
AR     = ar rcs

## Stable Section: usually no need to be changed. But you can add more.
##==========================================================================
SHELL   = /bin/sh
EMPTY   =
SPACE   = $(EMPTY) $(EMPTY)
SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
SOURCES := $(filter-out $(EXCLUDES), $(SOURCES))
HEADERS = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(HDREXTS))))
SRC_CXX = $(filter-out %.c,$(SOURCES))
OBJS    = $(addsuffix .o, $(basename $(SOURCES)))
DEPS    = $(OBJS:.o=.d)

## Define some useful variables.
DEP_OPT = $(shell if `$(CC) --version | grep -i "GCC" >/dev/null`; then \
                  echo "-MM -MP"; else echo "-M"; fi )
DEPEND      = $(CC)  $(DEP_OPT)  $(MY_CFLAGS) $(CFLAGS) $(CPPFLAGS)
DEPEND.d    = $(subst -g ,,$(DEPEND))
COMPILE.c   = $(CC)  $(MY_CFLAGS) $(CFLAGS) -c
COMPILE.cxx = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
LINK.c      = $(CC)  $(LDFLAGS)
LINK.cxx    = $(CXX) $(LDFLAGS)

.PHONY: all dist clean distclean

# Delete the default suffixes
.SUFFIXES:

all: $(OUTPUT)

# Rules for creating dependency files (.d).
#------------------------------------------
%.d:%.c
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.C
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.cc
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.cpp
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.CPP
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

%.d:%.c++
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

# Rules for generating object files (.o).
#----------------------------------------
%.o:%.c
	$(COMPILE.c) $< -o $@

%.o:%.C
	$(COMPILE.cxx) $< -o $@

%.o:%.cc
	$(COMPILE.cxx) $< -o $@

%.o:%.cpp
	$(COMPILE.cxx) $< -o $@

%.o:%.CPP
	$(COMPILE.cxx) $< -o $@

%.o:%.c++
	$(COMPILE.cxx) $< -o $@

# Rules for generating the executable.
#-------------------------------------
$(OUTPUT):$(OBJS)
ifeq ($(SRC_CXX),)              # C program
	$(LINK.c)   $(OBJS) $(MY_LIBS) -o $@
else                            # C++ program
	$(LINK.cxx) $(OBJS) $(MY_LIBS) -o $@
endif
	@echo Building $@ completed.

ifneq ($(DEPS),)
  sinclude $(DEPS)
endif

clean:
	$(RM) $(OBJS) $(OUTPUT) $(DEPS)
