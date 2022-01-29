ifeq ($(OS),Windows_NT)
    detected_os := Windows
else
    detected_os := $(shell uname)
endif

ifeq ($(detected_os),Windows)
	$(warning Building on windows not currently supported)
	C      := failhere
	CC     := failhere
	LIB    := failhere
endif
ifeq ($(detected_os),Darwin) # Mac OS X
	C      := clang
	CC     := clang++
	CFLAGS := -Wall -std=c++11
	LIB    := -lglfw3 -framework Cocoa -framework IOKit -framework CoreVideo
endif
ifeq ($(detected_os),Linux)
	C      := gcc
	CC     := g++
	CFLAGS := -Wall -std=c++11 $(shell pkg-config --cflags glfw3) 
	LIB    := $(shell pkg-config --static --libs glfw3)
endif

TARGET      := demo
SRCDIR      := src
INCDIR      := include
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := data
SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o
INC         := -I$(INCDIR) -I/usr/local/include
INCDEP      := -I$(INCDIR)
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT))) $(BUILDDIR)/glad.o

#Defauilt Make
all: resources $(TARGET)
all: directories $(TARGET)

#Remake
remake: cleaner all

#Copy Resources from Resources Directory to Target Directory
resources: directories
	@cp -r $(RESDIR) $(TARGETDIR)/

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

$(BUILDDIR)/glad.o:
	$(C) -Iinclude -c $(SRCDIR)/glad.c -o $@ $<

#Non-File Targets
.PHONY: all remake clean cleaner resources
