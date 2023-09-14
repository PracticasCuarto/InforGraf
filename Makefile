# Compilador y opciones de compilación
CXX = g++
CXXFLAGS = -std=c++14

# Archivos fuente y ejecutable
SRCS = Punto.cpp Direccion.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Regla genérica para compilar archivos fuente a objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
