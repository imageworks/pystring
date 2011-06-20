LIBTOOL = libtool
LIBDIR = /usr/lib
CXX = g++
CXXFLAGS = -g -O3 -Wall

all: libpystring.la

pystring.lo: pystring.h pystring.cpp
	$(LIBTOOL) --mode=compile --tag=CXX $(CXX) $(CXXFLAGS) -c pystring.cpp

libpystring.la: pystring.lo
	$(LIBTOOL) --mode=link --tag=CXX $(CXX) -o $@ $< -rpath $(LIBDIR)

install: libpystring.la
	$(LIBTOOL) --mode=install install -c $< $(LIBDIR)/$<

clean:
	$(RM) -fr pystring.lo pystring.o libpystring.la .libs

.PHONY: test
test:
	$(RM) -fr test
	$(CXX) pystring.cpp test.cpp -o test
	./test
