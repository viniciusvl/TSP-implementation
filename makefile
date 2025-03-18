# Nome do compilador
CXX = g++

# Opções de compilação (pode adicionar -O2 para otimização)
CXXFLAGS = -Wall -Wextra -std=c++17

# Nome do executável
TARGET = tsp.exe

# Arquivos-fonte
SRCS = solution.cpp construcao.cpp main.cpp data.cpp

# Arquivos objeto (transforma .cpp em .o)
OBJS = $(SRCS:.cpp=.o)

# Regra padrão para compilar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar os arquivos objeto individualmente
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Para rodar o programa após a compilação
run: $(TARGET)
	./$(TARGET)
