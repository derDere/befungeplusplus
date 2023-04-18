SRC = $(wildcard src/*.cpp)
APP = "befunge++"

All: $(APP)
	@echo Done

$(APP): $(SRC)
	g++ -o $(APP) $(SRC) -lncursesw -lpanelw -std=c++17

debug:
	g++ -g -o $(APP) $(SRC) -lncursesw -lpanelw -std=c++17
	gdb -ex run $(APP)

test: $(APP)
	./$(APP)

install: $(APP)
	cp $(APP) /usr/local/bin/$(APP)

uninstall:
	rm /usr/local/bin/$(APP)
