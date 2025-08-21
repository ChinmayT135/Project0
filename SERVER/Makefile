CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23

TARGET = project0_server

SRCS = server_main.cpp server_storage.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp server_headers.h
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(TARGET)
