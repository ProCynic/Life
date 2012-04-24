CC=g++
CFLAGS=-pedantic -ansi -Wall
LDFLAGS=-lcppunit -ldl
RUN=RunLife
TEST=TestLife

all: $(RUN).c++
	@echo "Making"
	@$(CC) $(CFLAGS) $(RUN).c++ -o $(RUN).app
	@echo "Done"

memtest: $(TEST).c++
	@echo "Making Tests"
	@$(CC) $(CFLAGS) $(TEST).c++ -o $(TEST).app $(LDFLAGS)
	@echo "Testing"
	@valgrind ./$(TEST).app

test: $(TEST).c++
	@echo "Making Tests"
	@$(CC) $(CFLAGS) $(TEST).c++ -o $(TEST).app $(LDFLAGS)
	@echo "Testing"
	@./$(TEST).app

clean:
	@echo "Cleaning"
	@rm -f *.app *~ *.out
	@echo "Done"