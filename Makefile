LIBF := -Lthirdparty/lib -static-libgcc -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
CF := -Wall -Werror -Ithirdparty/include $(LIBF)
CF_TEST := -Isrc $(CF)

OBJ_DIR := build/src
SRC_DIR := src
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
	g++ $^ -c -o $@ $(CF)
	g++ $^ -MM > $(OBJ_DIR)/$*.d $(CF)



test: all $(TEST_OBJ_DIR) $(TEST_EXE) $(TEST_SRC)

$(TEST_EXE): $(TEST_OBJ) $(patsubst build/src/main.o, ,$(OBJ))
	g++ $^ -o $@ $(CF_TEST)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	g++ $^ -c -o $@ $(CF_TEST)
	g++ $^ -MM > $(TEST_OBJ_DIR)/$*.d $(CF_TEST)


clean:
	rm -rf build bin

-include $(DEP)
-include $(TEST_DEP)

.PHONY: all clean test