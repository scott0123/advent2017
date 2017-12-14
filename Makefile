EXENAME = advent
OBJS = main.o day*.o io.o

CXX = clang++
#CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp days.h ../IO/io.h
	$(CXX) $(CXXFLAGS) main.cpp

day%.o : day%.cpp days.h ../IO/io.h
	$(CXX) $(CXXFLAGS) day*.cpp

io.o : ../IO/io.cpp ../IO/io.h
	$(CXX) $(CXXFLAGS) ../IO/io.cpp

clean :
	-rm -f *.o $(EXENAME)
