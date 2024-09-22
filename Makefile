PROJECT := Tetris
CC := g++

CFLAGS  := -ggdb $(shell cat compile_flags.txt)
LDFLAGS := -lm \
		   -L./vendor/raylib-5.0_linux_amd64/lib -l:libraylib.a

OUT_DIR := bin
OBJ_DIR := $(OUT_DIR)/obj
TARGET  := $(OUT_DIR)/$(PROJECT)
SRC_DIR := src

SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ_FILES := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

.PHONY: all
all: build

.PHONY: build
build: $(TARGET)

.PHONY: clean
clean:
	rm -rvf $(OUT_DIR)

.PHONY: run
run: build
	@echo "=== Running: $(TARGET) ==="
	@$(TARGET)

$(TARGET): $(OBJ_FILES)
	@echo "=== Linking ==="
	@echo "$@ <- $^"
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@echo "$@ <- $<"
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) -o $@ -c $<
