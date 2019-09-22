CXX = g++
CXXFLAGS = -Wall -pedantic -Werror -std=c++17 -Wno-unused-variable -g -Wno-unused-but-set-variable -Ilib/cpptoml -Ilib/utf8
LDFLAGS = -lenet -Llib/utf8 -lutf8
LD = g++
builddir = build
srcdir = src
bindir = bin
bin = $(bindir)/srs
sources = $(wildcard $(srcdir)/*.cpp $(srcdir)/srv/*.cpp $(srcdir)/proto/*.cpp)
objs = $(patsubst $(srcdir)/%.cpp,$(builddir)/%.o,$(sources))

all: $(bin)

$(bin): objs utf8 $(bindir) 
	$(LD) -o $@ $(objs) $(LDFLAGS) 

objs: $(builddir) $(objs)

$(objs): $(builddir)/%.o: $(srcdir)/%.cpp 
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(builddir):
	mkdir -p $(builddir)

$(bindir):
	mkdir -p $(bindir)

utf8:
	$(MAKE) -C lib/utf8 all

clean:
	$(MAKE) -C lib/utf8 clean
	rm -rf build/*
	rm -rf bin/*

.PHONY: all utf8 clean
