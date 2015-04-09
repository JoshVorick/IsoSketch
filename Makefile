FLAGS = -std=c++11
LFLAGS = `sdl-config --libs` -lSDL_image -lSDL_mixer -lSDL_ttf
OBJS = src/display.o src/dots.o src/init.o src/input.o src/graphics.o src/main.o src/saves.o
CXX = g++

%.o: %.cpp %.h
	$(CXX) $(FLAGS) -c -s $< -o $@

IsoSketch: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LFLAGS)

clean:
	rm IsoSketch $(OBJS)
