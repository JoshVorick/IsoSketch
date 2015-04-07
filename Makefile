FLAGS = -Wall -Werror
LFLAGS = `sdl-config --libs` -lSDL_image -lSDL_mixer -lSDL_ttf
OBJS = src/graphics.o src/main.o
CXX = g++

%.o: %.cpp %.h
	$(CXX) $(FLAGS) -c -s $< -o $@

IsoSketch: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LFLAGS)

clean:
	rm IsoSketch $(OBJS)
