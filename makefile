SRCS=$(shell find -name '*.cpp')
CPPFLAGS=-std=c++17 -O3
OBJS = $(SRCS:.cpp=.o)

OUT=prog.out

$(OUT): $(OBJS)
	g++-9 $(OBJS) $(CPPFLAGS) -o $@ $(LDFLAGS)

%.o: %.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@



clean:
	$(RM) $(shell find -name '*.o')


