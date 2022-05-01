TARGET_EXEC := exec

BUILD_DIR := ./bin
SRC_DIRS := ./src
OBJ_BUILD := $(BUILD_DIR)/obj


SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)

INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -MMD -MP -g -DDEBUG
LDFLAGS = -lpthread -lrt -D_XOPEN_SOURCE=500 -D_REENTRANT

# The final build step.
$(TARGET_EXEC): $(OBJS)
	$(CC) -Wall -pthread $(subst src,obj,$(OBJS)) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(OBJ_BUILD)
	$(CC) -Wall $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -c $< -o $(subst src,obj,$@)


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
	rm $(TARGET_EXEC)

-include $(DEPS)