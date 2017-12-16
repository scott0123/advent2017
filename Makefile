EXENAME = advent
SRC = $(wildcard day*.cpp)
OBJS = $(SRC:.cpp=.o) io.o dsets.o main.o

CXX = clang++
#CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

speed: CXXFLAGS += -O3

all : $(EXENAME)

speed : all

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

day%.o : day%.cpp days.h ../IO/io.h
	$(CXX) $(CXXFLAGS) day*.cpp

io.o : ../IO/io.cpp ../IO/io.h
	$(CXX) $(CXXFLAGS) ../IO/io.cpp

dsets.o : dsets.cpp dsets.h
	$(CXX) $(CXXFLAGS) dsets.cpp

clean :
	-rm -f *.o $(EXENAME)
