# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -std=c++11 -I.

# Directories
SRC_DIR = .
ACRONYM_DIR = Acronym_Generator
DIAL_DIR = Dial_Generator
SVG_DIR = SVG
WORD_DIR = Word_Generator

# Source Files
SRC_FILES = $(SRC_DIR)/Synthetic.cpp \
            $(ACRONYM_DIR)/AcronymGenerator.cpp \
            $(DIAL_DIR)/DialGenerator.cpp \
            $(SVG_DIR)/SVGBuilder.cpp \
						$(SVG_DIR)/SVGElements/Rectangle.cpp \
						$(SVG_DIR)/SVGElements/Header.cpp \
						$(SVG_DIR)/SVGElements/Text.cpp \
						$(SVG_DIR)/Transforms/Rotation.cpp \
						$(SVG_DIR)/Transforms/Scale.cpp \
						$(SVG_DIR)/Transforms/Translation.cpp \
            $(WORD_DIR)/WordGenerator.cpp

# Object Files
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Executable
EXEC = bin/Synthetic

# Rules
all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ_FILES) $(EXEC)

.PHONY: all clean
