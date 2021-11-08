NAME=gbemu
BUILD_DIR=build

default: cmake-debug

clean:
	@rm -rf $(BUILD_DIR)

build-dir:
	@mkdir -p $(BUILD_DIR)

compile:
	@cd $(BUILD_DIR) && make

cmake-debug: build-dir compile
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=on ..
