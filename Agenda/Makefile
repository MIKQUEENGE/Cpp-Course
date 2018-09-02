CC := g++-4.8
FLAGS := -std=c++11 -w

bin/main: build/AgendaService.o build/Date.o build/Meeting.o build/Storage.o build/User.o build/AgendaUI.o build/Agenda.o
	$(CC) $(FLAGS) -I ./include $^ -o $@

build/%.o: src/%.cpp
	$(CC) $(FLAGS) -I ./include -c -o $@ $<

clean:
	@rm -f ./bin/*
	@rm -f ./build/*
