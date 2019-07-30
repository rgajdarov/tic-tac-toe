CC = g++
CXXFLAGS = -Wall -std=c++11
LIBS = -lncurses
EXECDIR = bin
EXEC = tic-tac-toe
OBJDIR = obj
OBJS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(wildcard *.cpp))
MKDIR = @mkdir -p $(@D)

$(EXECDIR)/$(EXEC): $(OBJS)
	$(MKDIR)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(@D)/$(EXEC) $(LIBS) 

$(OBJDIR)/%.o: %.cpp
	$(MKDIR)
	$(CC) $(CXXFLAGS) -c $< -o $@
clean:
	rm $(EXECDIR)/$(EXEC) $(OBJDIR)/*.o
