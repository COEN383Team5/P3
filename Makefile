CXX			:= g++
CXXFLAGS	:= -Wall -O3 -std=c++11
SRC_SUFFIX	:= .cpp
SRCS		:= $(patsubst src/%$(SRC_SUFFIX), %$(SRC_SUFFIX), $(wildcard src/*$(SRC_SUFFIX)))
OBJ_DIR		:= obj/
BIN_DIR		:= bin/
VPATH		:= src:${OBJ_DIR}

P3: $(SRCS:$(SRC_SUFFIX)=.o)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)$@ $(patsubst %$(SRC_SUFFIX), $(OBJ_DIR)%.o, $(SRCS)) -lpthread
.PHONY: P3

clean:
	@rm -rf $(BIN_DIR)
	@rm -rf $(OBJ_DIR)
.PHONY: clean

%.o: %$(SRC_SUFFIX)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $(OBJ_DIR)$@ $<

