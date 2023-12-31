CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

SRC_DIR = functions
OBJ_DIR = obj

# List all source files individually
SRCS = main.cpp $(SRC_DIR)/urlencoder.cpp
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

TGIND_EXEC = tgind

all: $(TGIND_EXEC)

# Pattern rule to compile each source file into an object file
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TGIND_EXEC): $(OBJS)
	$(CXX) $^ -o $@ -L./curl/lib -lcurl

clean:
	rm -rf $(OBJ_DIR)/*.o $(TGIND_EXEC)
