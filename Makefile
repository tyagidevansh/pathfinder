CC = g++
CFLAGS = -I"C:\Users\devan\Documents\Libraries\SFML-2.6.1\include" -DSFML_STATIC
LDFLAGS = -L"C:\Users\devan\Documents\Libraries\SFML-2.6.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static

# Source files
SOURCES = main.cpp grid.cpp BFS.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Target executable
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)




#g++ -c main.cpp -I"C:\Users\devan\OneDrive\Documents\Libraries\SFML-2.6.1\include" -DSFML_STATIC
#g++ main.o -o main -L "C:\Users\devan\OneDrive\Documents\Libraries\SFML-2.6.1\lib" -l sfml-graphics-s -l sfml-window-s -l sfml-system-s -l opengl32 -l freetype -l winmm -l gdi32 -static