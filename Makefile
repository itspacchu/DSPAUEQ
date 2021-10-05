## this is a test make file and is not to be used
SHELL := /bin/bash

.PHONY: help
help: ## Show this help
	@egrep -h '\s##\s' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

.PHONY: build
build: ## make build

.PHONY: test
test: ## make test
	echo "Using the testbench script"
	g++ -std=c++17 -I./DSP ./tests/testbench.cpp -o build/testbenchOut
	
.PHONY: realtime
rtime: ## make test
	echo "Realtime ffmpeg playback"
	g++ -std=c++17 -I./DSP ./realtime.cpp -o build/realtime