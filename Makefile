CXX = g++
CXXFLAGS = -Wall -pedantic -Werror -std=c++17 -Wno-unused-variable -g -Wno-unused-but-set-variable
CC = gcc
CFLAGS = -Wall -pedantic -Werror -std=c11
LDFLAGS = -lenet
sourcedir = src
sources = $(wildcard $(sourcedir)/*.cpp) $(wildcard $(sourcedir)/srv/*.cpp) $(wildcard $(sourcedir)/srv/gm/*.cpp) $(wildcard $(sourcedir)/proto/*.cpp)
csources = $(wildcard $(sourcedir)/utf8/*.c)
objs = $(patsubst %.cpp,%.o,$(sources)) $(patsubst %.c,%.o,$(csources)) 

srs: $(objs)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(objs) srs