build = build

all: $(build)/Makefile
	cd $(build) && make 

$(build)/Makefile: CMakeLists.txt
	mkdir -p $(build) && cd $(build) && cmake .. -DCMAKE_PREFIX_PATH=/usr/local/opt/qt5

clean:
	$(MAKE) -C $(build) clean
	rm -rf $(build)
