CXX = g++
CXXFLAGS = -Wall -pedantic -Werror -std=c++17 -Wno-unused-variable -g -Wno-unused-but-set-variable -Ilib/cpptoml -Ilib/utf8 -Ilib/lua/src
LDFLAGS = -lenet -Llib/utf8 -Llib/lua/src -lutf8 -llua
LD = g++
builddir = build
srcdir = src
bindir = bin
bin = $(bindir)/srs
sources = $(wildcard $(srcdir)/*.cpp $(srcdir)/srv/*.cpp $(srcdir)/proto/*.cpp)
objs = $(patsubst $(srcdir)/%.cpp,$(builddir)/%.o,$(sources))

all: $(bin)

$(bin): objs utf8 lua $(bindir) 
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
	$(MAKE) -C lib/lua/src clean
	rm -rf build/*
	rm -rf bin/*

lua:
	$(MAKE) -C lib/lua/src a

.PHONY: all utf8 lua clean
