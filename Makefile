
INCLUDEDIR = -I./inc \

LIBDIR = -lpthread  -lm 

GCC = /usr/bin/g++
#CXX_IND_FLAGS  = -c -fpic -O3 -DNDEBUG -DPPLM_FLOAT
CXX_IND_FLAGS  = -c -fpic -g -DPPLM_DEBUG -DDEBUG_OUTPUT_FILE -DPPLM_FLOAT

SRCDIR   = src
OBJDIR   = obj_dir

SRC      = $(wildcard $(SRCDIR)/*.cc)
OBJ      = $(patsubst $(SRCDIR)%.cc,$(OBJDIR)%.o,$(SRC))

OUTPUT   = ./MaxMatch_CWS

all: makedir  $(OBJ)
	$(GCC) -o $(OUTPUT) $(OBJ) $(LIBDIR)  
	#rm -rf $(OBJDIR)

makedir:
	rm -rf $(OBJDIR)
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) 

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	$(GCC) $(CXX_IND_FLAGS) $(INCLUDEDIR) $< -o $@
