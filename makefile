CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

SRCS = Board.cpp Catan.cpp Tile.cpp Road.cpp Player.cpp Building.cpp DevelopmentCard.cpp 
HDRS = Board.hpp catan.hpp Tile.hpp Road.hpp Player.hpp Building.hpp DevelopmentCard.hpp 

TESTSOURCES = TestCounter.cpp Test.cpp
TESTOBJS = $(TESTSOURCES:.cpp=.o)

OBJS = $(SRCS:.cpp=.o)

TARGET = catan
TESTTARGET = test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(TESTTARGET): $(TESTOBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TESTTARGET) $(TESTOBJS) $(filter-out Catan.o, $(OBJS))

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# tidy:
# 	clang-tidy $(SRCS) $(HDRS) -- $(CXXFLAGS)
tidy:
	clang-tidy $(SRCS) $(HDRS) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

# valgrind: $(TARGET) $(TESTTARGET)
# 	valgrind --leak-check=full --track-origins=yes --log-file=valgrind-report.txt ./$(TARGET)
# 	valgrind --leak-check=full --track-origins=yes --log-file=valgrind-test-report.txt ./$(TESTTARGET)
valgrind: $(TARGET) 
	valgrind --leak-check=full --track-origins=yes --log-file=valgrind-report.txt ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TESTOBJS) $(TESTTARGET) valgrind-report.txt valgrind-test-report.txt

distclean: clean

.PHONY: all clean distclean