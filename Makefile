# let's keep this short and sweet
TARGET = wasp
SOURCE = brute.c asp.c
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) -Ofast -o $(TARGET) $(SOURCE)

clean:
	$(RM) $(TARGET)
