# Compilador y opciones de compilación
CXX = g++
CXXFLAGS = -std=c++14 -O3 -pthread

# Directorio de objetos y ejecutables
OBJDIR = exec
BINDIR = exec

# Carpeta de código fuente
SRCDIR = src

# Archivos fuente y ejecutable
SRCS := $(shell find $(SRCDIR) -name "*.cpp")
SRCS := $(filter-out $(SRCDIR)/main.cpp, $(SRCS))
SRCS += main.cpp
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
EXEC = $(BINDIR)/main

all: $(BINDIR) $(EXEC)

$(BINDIR):
	mkdir -p $(BINDIR)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Regla genérica para compilar archivos fuente a objetos
$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)  # Crea directorios si no existen
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BINDIR)
