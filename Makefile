CONFIG ?= Debug

ifeq ($(OS), Windows_NT)
    EXECUTABLE := build/bin/$(CONFIG)/TheIsle
else
    EXECUTABLE := build/bin/$(CONFIG)/TheIsle.exe
endif


all: compile link run

compile: 
	cmake -S . -B build 
 
link:
	cmake --build build --config $(CONFIG)

run:
	$(EXECUTABLE)

.PHONY: set-config
	$(eval CONFIG := $(filter-out $@,$(MAKECMDGOALS)))
	@echo "Set config to $(CONFIG)"

%:
	@: