CXX = clang++ -g -std=c++14

GAME = noName.out

INCLUDEDIR = ./include
SRCDIR = ./sources
OBJDIR = ./objects

INCLUDES = $(wildcard $(INCLUDEDIR)/*.hpp)
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(GAME)

$(GAME): $(OBJS)
	$(CXX) $^ -o $@ -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -I$(INCLUDEDIR) -o $@

clean:
	$(RM) $(OBJS) $(GAME)

run:
	./$(GAME)
