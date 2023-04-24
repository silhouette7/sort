CC := g++
TARGET := sort
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))

TARGET: $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CC) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ) $(TARGET)