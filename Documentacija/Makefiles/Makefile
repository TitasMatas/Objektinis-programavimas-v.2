# Makefile (Unix/Linux/macOS)
# Naudojimas:
#   make         # kompiliuoja 'programa'
#   make run     # paleidžia ./programa
#   make clean   # išvalo build artefaktus

CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic
LDFLAGS :=

SRCS := main.cpp v.pradine.cpp vector.cpp  # Keep the correct filenames here
HDRS := functions.h student.h

TARGET := programa
OBJDIR := build
OBJS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJDIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)
