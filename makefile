# gets workspace folder name (must not contain spaces)
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
ProjectName := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

# compiler
CC = g++
# compile with c++11 standard and in debug mode
CFLAG = -std=c++11 -g -Wall

# path variables
BIN_DIR = build
INC_DIR = include
SRC_DIR = source
OBJ_DIR = obj
LIB_DIR = lib/wx
RSC_DIR = resources

# source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o, $(SRCS))

# library files
LIBS := $(patsubst $(LIB_DIR)/lib%.a,-l %, $(wildcard $(LIB_DIR)/*.a))

# windows resources
# RSC = $(OBJ_DIR)/icon.o

# rules
.PHONY: all run clean echo

all: $(BIN_DIR)/$(ProjectName)

echo:
	@echo $(LIBS)

# build in debug mode
$(BIN_DIR)/$(ProjectName): $(OBJS) # $(RSC) # $< not working!
	@echo bulding project:
	$(CC) $(CFLAG) $(OBJS) $(RSC) -o $@ -I $(INC_DIR) -L $(LIB_DIR) $(LIBS) -mwindows
	@echo done!

# static rule
# genetate .o files in obj_dir from source files
$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo creating object files:
	$(CC) $(CFLAG) -c $< -I $(INC_DIR) -o $@
	@echo done!

# compile resource file for windows app
# $(RSC): $(RSC_DIR)/*.rc
# 	windres $< -o $@

# runs output file in external console
# windows only
run: all
	cmd /c start cmd /k "cd $(BIN_DIR) & $(ProjectName).exe & exit"

# windows only
clean:
	del /f $(OBJ_DIR)\*.o $(BIN_DIR)\*.exe
	@echo Clean Complete!