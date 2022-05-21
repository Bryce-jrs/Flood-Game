GSL_PATH ?= /net/ens/renault/save/gsl-2.6/install/gsl-2.6/install
LDFLAGS = -L $(GSL_PATH)/lib
LIBFLAGS = -ldl -lgsl -lm -lgslcblas

INSTALL_DIR = install
SRC_DIR = src
TST_DIR = tests
CFLAGS = -Wall -Wextra -std=c99 -g -O0 -I $(GSL_PATH)/include -I $(SRC_DIR)

LIB_NAME = player_2.so player_1.so 
EXEC_NAME = alltests server

GCC = gcc




.PHONY = clear install

build: server $(LIB_NAME)

test: alltests

install: $(EXEC_NAME) $(LIB_NAME)
	cp $(EXEC_NAME) $(LIB_NAME) ./$(INSTALL_DIR)/




## SERVER ##

server.o: $(SRC_DIR)/server.c
	$(GCC) -c $(CFLAGS) $(<) -o $@

server: server.o players.o graph.o matrix.o graph_update.o random_generator.o check_validity.o winning_cond.o options.o
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBFLAGS)




## OPTIONS ##

options.o: $(SRC_DIR)/options.c
	$(GCC) -c $(CFLAGS) $(<) -o $@




## CHECK ##

check_validity.o: $(SRC_DIR)/check_validity.c
	$(GCC) -c $(CFLAGS) $(<) -o $@

check_validity: check_validity.o graph.o matrix.o players.o
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBFLAGS)

test_check_validity: tests/test_check_validity.c check_validity.o graph.o matrix.o players.o update_graph.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBFLAGS)

## MATRIX ##

matrix.o: $(SRC_DIR)/matrix.c
	$(GCC) -c $(CFLAGS) $< -o $@

test_matrix.o: $(TST_DIR)/test_matrix.c
	$(GCC) -c $(CFLAGS) $< -o $@




## GRAPH ##

graph.o: $(SRC_DIR)/graph.c
	$(GCC) -c $(CFLAGS) $< -o $@

test_graph.o: $(TST_DIR)/test_graph.c
	$(GCC) -c $(CFLAGS) $< -o $@

graph_update.o: $(SRC_DIR)/graph_update.c
	$(GCC) -c $(CFLAGS) $< -o $@

test_graph_update.o: $(TST_DIR)/test_graph_update.c
	$(GCC) -c $(CFLAGS) $< -o $@

## player_1 ##


player_1.so: $(SRC_DIR)/player_1.c graph.o matrix.o graph_update.o random_generator.o check_validity.o winning_cond.o
	$(CC) $(CFLAGS) -fPIC -shared $^ -o $@

player_2.so: $(SRC_DIR)/player_1.c graph.o matrix.o graph_update.o random_generator.o check_validity.o winning_cond.o
	$(CC) $(CFLAGS) -fPIC -shared $^ -o $@


## PLAYERS ##

players.o: $(SRC_DIR)/players.c
	$(GCC) -c $(CFLAGS) $< -o $@




## CLIENT ##

libSophie.so: $(SRC_DIR)/player_random_move.c $(SRC_DIR)/graph.c $(SRC_DIR)/matrix.c $(SRC_DIR)/graph_update.c $(SRC_DIR)/random_generator.c
	$(CC) $(CFLAGS) -fPIC -shared $^ -o $@

libDavid.so: $(SRC_DIR)/player_max_point.c $(SRC_DIR)/graph.c $(SRC_DIR)/matrix.c $(SRC_DIR)/strategy.c $(SRC_DIR)/graph_update.c $(SRC_DIR)/check_validity.c $(SRC_DIR)/players.c
	$(CC) $(CFLAGS) -fPIC -shared $^ -o $@

test_player.o: $(TST_DIR)/test_player.c player_1.so
	$(GCC) -c $(CFLAGS) $< -o $@




## VICTORY ##

winning_cond.o : $(SRC_DIR)/winning_cond.c $(SRC_DIR)/winning_cond.h
	$(CC) -c $(CFLAGS) $< -o $@

winning_cond : winning_cond.o check_validity.o graph.o matrix.o players.o graph_update.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBFLAGS)

test_winning_cond.o: $(TST_DIR)/test_winning_cond.c $(SRC_DIR)/winning_cond.h
	$(CC) -c $(CFLAGS) $< -o $@ --coverage

test_winning_cond: test_winning_cond.o winning_cond.o check_validity.o graph.o graph_update.o random_generator.o matrix.o players.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBFLAGS)




## FILE MANAGER ##

file_manager.o: $(SRC_DIR)/file_manager.c
	$(GCC) -c $(CFLAGS) $< -o $@




## RANDOM GENERATOR ##

random_generator.o: $(SRC_DIR)/random_generator.c
	$(GCC) -c $(CFLAGS) $< -o $@




## STRATEGY ##

strategy.o : $(SRC_DIR)/strategy.c $(SRC_DIR)/strategy.h
	$(CC) -c $(CFLAGS) $< -o $@

strategy : strategy.o check_validity.o graph.o matrix.o players.o update_graph.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBFLAGS)




## TEST ##

alltests.o: $(TST_DIR)/alltests.c
	$(GCC) -c $(CFLAGS) $< -o $@ --coverage

alltests: alltests.o test_player.o test_graph.o test_matrix.o file_manager.o players.o graph.o matrix.o graph_update.o random_generator.o check_validity.o winning_cond.o
	$(GCC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBFLAGS) -lgcov




## CLEAN ##

clean:
	rm -f *~  *.so *.o *.gcno *.gcov *.gcda $(EXEC_NAME) $(LIB_NAME) $(GCOV_NAME) ./$(SRC_DIR)/*~ ./$(TST_DIR)/*~
