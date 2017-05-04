ifeq ($(shell uname -o), Linux)
	CF := -std=c++14 -Wall -Werror -Isrc/h -Ithirdparty/include_linux
else
    LIBF := -Lthirdparty/lib -static-libgcc -static-libstdc++ -static -lregraph -lstdc++ -lgdi32
	CF := -std=c++14 -Wall -Werror -Isrc/h -Ithirdparty/include $(LIBF)
endif
CF_TEST := $(CF)

OBJ_DIR := build/src
SRC_DIR := src/cpp
TEST_OBJ_DIR := build/test
TEST_SRC_DIR := test

EXE := bin/GM-life
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
DEP := $(OBJ:.o=.d)

TEST_EXE := bin/GM-life-test
TEST_SRC := $(wildcard $(TEST_SRC_DIR)/*.cpp)
TEST_OBJ := $(patsubst $(TEST_SRC_DIR)/%.cpp, $(TEST_OBJ_DIR)/%.o, $(TEST_SRC))
TEST_DEP := $(TEST_OBJ:.o=.d)


all: build $(OBJ_DIR) bin $(EXE) $(SRC)

build $(OBJ_DIR) $(TEST_OBJ_DIR) bin:
	mkdir $@

$(EXE): $(OBJ)
	g++ $^ -o $@ $(CF)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $< -c -o $@ $(CF) -MMD -MF $(OBJ_DIR)/$*.d



test: all $(TEST_OBJ_DIR) $(TEST_EXE) $(TEST_SRC)

$(TEST_EXE): $(TEST_OBJ) $(patsubst build/src/main.o, ,$(OBJ))
	g++ $^ -o $@ $(CF_TEST)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	g++ $< -c -o $@ $(CF_TEST) -MMD -MF $(TEST_OBJ_DIR)/$*.d


clean:
	rm -rf build bin

run:
	./$(EXE)
	
runtest:
	./$(TEST_EXE)
	
-include $(DEP)
-include $(TEST_DEP)

.PHONY: all clean test run runtest