EXECUTABLE   := Graphics.exec
OBJ_D        := ./objects
HEADERS      := $(wildcard include/*.h)
SOURCEFILES  := $(wildcard src/*.cpp)
OBJFILES     := $(SOURCEFILES:src/%.cpp=$(OBJ_D)/%.o)
CFlags       := --std=c++17 -msse4 -Ofast -Iinclude/ -I/home/anastas/git/MIPT_3_Sem_C++/MyLib/
LINKFlagsGL	 := -lGL -lGLU -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lGLEW -ldl
LINKFlagsSF	 := -lsfml-graphics -lsfml-window -lsfml-system
Warnings     := -fmax-errors=10 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wno-unused-result -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -fchkp-first-field-has-own-bounds -fchkp-narrow-to-innermost-array -flto-odr-type-merging -fno-omit-frame-pointer -fPIE
NoWarnings   := -Wno-effc++ -Wno-unused-parameter

git_branch   := master


all: $(SOURCEFILES) $(HEADERS) $(EXECUTABLE)
	@./$(EXECUTABLE)

$(EXECUTABLE): $(OBJFILES)
	@g++ $(OBJFILES) -o $@ $(LINKFlags) $(LINKFlagsSF) $(LINKFlagsGL)

$(OBJ_D)/%.o: src/%.cpp
	#@g++ $(CFlags) $(Warnings) $(NoWarnings) -c $< -o $@
	@g++ $(CFlags) $(NoWarnings) -c $< -o $@

$(OBJ_D)/plugin.o: src/plugin.cpp
	@g++ $(CFlags) $(NoWarnings) -c $< -ldl -o $@


test:
	@g++ -c ./testing/main.cpp -o ./testing/main.o
	@g++ -c ./src/glad.cpp -o ./testing/glad.o
	@g++ -c ./src/stb_image.cpp -o ./testing/stb_image.o
	@g++ ./testing/main.o ./testing/glad.o ./testing/stb_image.o -o ./testing/main.exec -lGL -lGLU -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lGLEW -ldl
	@rm -f testing/*.o
	@./testing/main.exec
	@rm -f testing/*.exec
clean:
	@rm -f objects/*.o
install:
	@cp $(EXECUTABLE) /usr/local/bin/$(EXECUTABLE)
uninstall:
	@rm -f /usr/local/bin/$(EXECUTABLE)
push:
	@git push origin $(git_branch)
addall:
	@git add .
commit:
	@git commit -m "Automatic commit" -a

gl:
	@g++ -c  Graphics.cpp -o Graphics.o
	@g++ Graphics.o -o Graphics -lGL -lGLU -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lGLEW
	@./Graphics