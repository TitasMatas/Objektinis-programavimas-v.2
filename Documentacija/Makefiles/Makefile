# Makefile (Unix/Linux/macOS)
# Naudojimas:
#   make            # kompiliuoja 'programa'
#   make run        # paleidžia ./programa
#   make test       # sukompiliuoja ir paleidžia unit testus
#   make clean      # išvalo build artefaktus

CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic
LDFLAGS :=

SRCS := main.cpp v.pradine.cpp vector.cpp student.cpp
HDRS := functions.h student.h zmogus.h
TARGET := programa

TEST_SRCS := Tests/tests.cpp student.cpp vector.cpp
TEST_TARGET := unit_tests

OBJDIR := build
OBJS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(OBJDIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

# Unit tests (Doctest)
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRCS) Tests/doctest.h
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -I./Tests -o $(TEST_TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TEST_TARGET)
