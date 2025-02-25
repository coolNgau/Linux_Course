# Set the source directory and the files to compile
SRC_DIR = src
BIN_DIR = bin
SRC_FILES = $(SRC_DIR)/hala.c $(SRC_DIR)/miniz.c
TARGET = $(BIN_DIR)/hala
ZIP_FILE = kernel.zip

# Set GCC flags
CFLAGS = -Wall -g

# Compilation process
all: $(TARGET)

$(TARGET): $(SRC_FILES)
	@echo "Compiling the program..."
	@mkdir -p $(BIN_DIR)
	@gcc $(CFLAGS) $(SRC_FILES) -o $(TARGET)
	@echo "Compilation successful!"

run: $(TARGET)
	@echo "Running the program..."
	@./$(TARGET) 

clean:
	@echo "Cleaning up compiled files..."
	@rm -f $(TARGET)

.PHONY: all run clean
