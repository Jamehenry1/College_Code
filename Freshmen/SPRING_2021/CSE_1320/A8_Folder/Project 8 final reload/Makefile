TARGET_EXEC := creature_list

BUILD_DIR := ./build
SRC_DIR := ./problem2

SRCS := $(SRC_DIR)/creature_list.c
SRCS2 := $(SRC_DIR)/utils.c
SRCS3 := $(SRC_DIR)/bst.c

RELEASE := $(BUILD_DIR)/$(TARGET_EXEC)

all: release

release: $(SRCS)
	mkdir -p $(dir $(RELEASE))
	$(CC) $(CFLAGS) $< $(SRCS2) $(SRCS3) -o $(RELEASE)

clean:
	rm -rf $(BUILD_DIR)