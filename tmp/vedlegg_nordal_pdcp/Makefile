all: build doxy
clean: doxy-clean build-clean

build:
	$(MAKE) -C src
doxy:
	doxygen doxy-src/Doxyfile
build-clean:
	rm -rf build
doxy-clean:
	rm -rf doxy
.PHONY: all clean build-clean doxy-clean doxy