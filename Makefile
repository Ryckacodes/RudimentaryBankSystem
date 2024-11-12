CXX = g++
CXXFLAGS = -Wall -std=c++2b
INC_DIRS = -Iheaders

SRCS = cppFiles/BankSys.cpp cppFiles/transfer.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = BankSys

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
