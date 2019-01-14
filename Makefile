CC := g++
PROJECT_NAME := bogtris

LIBRARIES := SDL2 SDL2_image
LIBRARIES_FLAGS = $(foreach lib, $(LIBRARIES), -l$(lib) )

COMPILER_FLAGS := -Wall

OBJS = Bogtris.o Window.o Game.o Screen.o MainGameScreen.o
OBJS_FILES = $(foreach obj, $(OBJS), ./obj/$(obj) )

all: $(OBJS)
	$(CC) $(OBJS_FILES) $(COMPILER_FLAGS) $(LIBRARIES_FLAGS) -o ./bin/$(PROJECT_NAME)

$(OBJS): %.o: ./src/%.cpp
	$(CC) -c $(COMPILER_FLAGS) $< -o ./obj/$@

.PHONY: clean
clean:
	rm ./bin/$(PROJECT_NAME) \
		./obj/*.o
