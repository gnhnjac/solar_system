CPP_SOURCES = $(wildcard *.cpp)
OBJS = ${CPP_SOURCES:.cpp=.o}
DEPS := $(OBJS:.o=.d)

SFML_VER := 2.5.1
WIN_VER := 32

all: main.exe

run: all
	set PATH=%PATH%;%cd%/SFML-${SFML_VER}-${WIN_VER}/bin
	@./main.exe

main.exe: $(OBJS)
	g++ $^ -o main.exe -LSFML-${SFML_VER}-${WIN_VER}/lib -lsfml-graphics -lsfml-window -lsfml-system

-include ${DEPS}

%.o: %.cpp
	g++ -c $< -o $@ -MMD -Wall -ISFML-${SFML_VER}-${WIN_VER}/include

clean:
	@del *.o
	@del *.d
	@del *.exe