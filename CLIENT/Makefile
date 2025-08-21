CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23

TARGET = project0_executable

SRCS = main.cpp methods.cpp client_connection.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp headers.h
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(TARGET)
