# Compilador y opciones de compilación
CXX = g++
CXXFLAGS = -std=c++14

# Directorio de objetos y ejecutables
OBJDIR = exec
BINDIR = exec

# Archivos fuente y ejecutable
SRCS = Punto.cpp Direccion.cpp tests.cpp
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/tests

all: $(BINDIR) $(OBJDIR) $(EXEC)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Regla genérica para compilar archivos fuente a objetos
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(BINDIR)
