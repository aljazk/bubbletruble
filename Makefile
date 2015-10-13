TARGET=release/ball
CFLAGS=-Wall -Wextra -DSFML_STATIC -O3 -flto
LFLAGS=-static -O3 -flto\
	-lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-network-s \
	-ljpeg -lglew32 -lfreetype -lws2_32 \
	-lgdi32 -lopengl32 -lwinmm
FILES=main.cpp Menu.cpp Bubble.cpp Player.cpp Host.cpp Client.cpp Interface.cpp \
	draw/VertQuad.cpp draw/VertCircle.cpp \
	interface/Button.cpp interface/Input.cpp

OBJS=$(patsubst %,build/%.o,$(basename $(FILES)))
.PHONY: all clean
all: $(TARGET)
$(TARGET): $(OBJS)
	@echo "Linking..."
	@mkdir -p $(@D)
	@g++ $(OBJS) $(LFLAGS) -o $(TARGET)
	@echo "Done."
build/%.o: src/%.cpp
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@g++ -c $< $(CFLAGS) -o $@
build/%.o: src/%.c
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@g++ -c $< $(CFLAGS) -o $@
src/%.cpp : src/%.hpp
src/%.c : src/%.h
clean:
	@rm -rf *.o $(TARGET) $(TARGET).exe build/
	@echo "Cleaned."
