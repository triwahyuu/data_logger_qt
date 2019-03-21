all: debug build

run:
	./build/Debug/data_logger

debug: data_logger.pro src/*.cpp inc/*.h ui/*.ui
	@if [ ! -d "./build/Debug/" ]; then mkdir -p ./build/Debug/; fi
	@qmake data_logger.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug -o build/Debug/

release: data_logger.pro src/*.cpp inc/*.h ui/*.ui
	@if [ ! -d "./build/Release/" ]; then mkdir -p ./build/Release/ ; fi
	@qmake data_logger.pro -spec linux-g++ CONFIG+=release -o build/Release/

build: build/Debug/Makefile
	@make -j4 --directory build/Debug

.PHONY: clean
clean:
	rm -rf build/*