# Compilador y opciones de compilación
CXX = g++
CXXFLAGS = -std=c++14

# Directorio de objetos y ejecutables
OBJDIR = exec
BINDIR = exec

# Carpeta de código fuente
SRCDIR = src

# Archivos fuente y ejecutable
SRCS := $(wildcard $(SRCDIR)/*.cpp)
SRCS := $(filter-out $(SRCDIR)/main.cpp, $(SRCS))
SRCS += main.cpp
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/main

all: $(BINDIR) $(OBJDIR) $(EXEC)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Regla genérica para compilar archivos fuente a objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BINDIR)
