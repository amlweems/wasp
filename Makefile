# let's keep this short and sweet
TARGET = wasp
all: $(TARGET)
$(TARGET):
	gcc -Ofast -o wasp brute.c asp.c
