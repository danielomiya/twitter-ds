TARGET_EXEC ?= app

DATA_DIR ?= ./data
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

CXX = g++

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -g -Wall -Wshadow -pedantic -std=c++17 -MMD -MP

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR) $(DATA_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

### END OF C++ COMPILATION TARGETS

PY ?= python3

pyenv:
	$(PY) -m venv venv
	source venv/bin/activate && pip install -r requirements.txt

PLACE ?= BRAZIL
MODE ?= append
OUTPUT_FILE ?= data/out.csv
trends:
	@$(MKDIR_P) data
	$(PY) scripts/twitter_service.py -o $(OUTPUT_FILE) --place $(PLACE) --mode $(MODE)

graph:
	dot -Tpng $(IN) -o $(subst .dot,.png,$(IN))
