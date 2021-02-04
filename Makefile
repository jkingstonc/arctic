

BUILDDIR=./build
SRC=$(wildcard src/*.cpp) \
	$(wildcard src/cpu/*.cpp) \
	$(wildcard src/dev/*.cpp) \
	$(wildcard src/io/*.cpp) \
	$(wildcard src/memory/*.cpp) \
	$(wildcard src/shell/*.cpp) \
	$(wildcard src/utils/*.cpp) \
CXXFLAGS = -m32 -ffreestanding -nostdinc -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions
OBJ = $(SRC:.cpp=.o)
TARGET = kernel

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) -c $(SRC) -o $(BUILDDIR)

clean:
	$(RM) $(TARGET)