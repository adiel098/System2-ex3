CXX=g++
CXXFLAGS=-std=c++11 -g 
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Catan.cpp Player.cpp Board.cpp 
OBJECTS=$(subst .cpp,.o,$(SOURCES))

run: demo
	./$^

demo: Demo.o Player.o Catan.o Board.o
	$(CXX) $(CXXFLAGS) $^ -o demo -lstdc++

# test: TestCounter.o Test.o $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) $^ -o test -lstdc++ -lm

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo 
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }

Demo.o: Demo.cpp Catan.hpp Player.hpp Board.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


Catan.o: Catan.cpp Catan.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Player.o: Player.cpp Player.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Board.o: Board.cpp Board.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f *.o demo 
