CC = gcc
FLAGS = -g -I include

SOURCEDIR = ./src
BUILDDIR = ./build
TESTDIR = ./test

dir:
	mkdir -p $(BUILDDIR)

test: $(BUILDDIR)/linked_list_test $(BUILDDIR)/bst_test $(BUILDDIR)/hash_table_test $(BUILDDIR)/vector_test $(BUILDDIR)/generic_vector_test
	$(BUILDDIR)/linked_list_test
	$(BUILDDIR)/bst_test
	$(BUILDDIR)/hash_table_test
	$(BUILDDIR)/vector_test
	$(BUILDDIR)/generic_vector_test

memtest: $(BUILDDIR)/linked_list_test $(BUILDDIR)/bst_test $(BUILDDIR)/hash_table_test $(BUILDDIR)/vector_test
	valgrind $(BUILDDIR)/linked_list_test
	valgrind $(BUILDDIR)/bst_test
	valgrind $(BUILDDIR)/hash_table_test
	valgrind $(BUILDDIR)/vector_test
	valgrind $(BUILDDIR)/generic_vector_test

$(BUILDDIR)/utils.o: dir $(SOURCEDIR)/utils.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/utils.c -o $(BUILDDIR)/utils.o

$(BUILDDIR)/linked_list.o: dir $(SOURCEDIR)/linked_list.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/linked_list.c -o $(BUILDDIR)/linked_list.o

$(BUILDDIR)/linked_list_test: dir $(BUILDDIR)/linked_list.o $(TESTDIR)/linked_list_test.c
	$(CC) $(FLAGS) $(BUILDDIR)/linked_list.o $(TESTDIR)/linked_list_test.c -o $(BUILDDIR)/linked_list_test

$(BUILDDIR)/bst.o: dir $(SOURCEDIR)/bst.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/bst.c -o $(BUILDDIR)/bst.o

$(BUILDDIR)/bst_test: dir $(BUILDDIR)/bst.o $(TESTDIR)/bst_test.c
	$(CC) $(FLAGS) $(BUILDDIR)/bst.o $(TESTDIR)/bst_test.c -o $(BUILDDIR)/bst_test

$(BUILDDIR)/hash_table.o: dir $(SOURCEDIR)/hash_table.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/hash_table.c -o $(BUILDDIR)/hash_table.o

$(BUILDDIR)/hash_table_test: dir $(BUILDDIR)/utils.o $(BUILDDIR)/hash_table.o $(BUILDDIR)/bst.o $(TESTDIR)/hash_table_test.c
	$(CC) $(FLAGS) $(BUILDDIR)/utils.o $(BUILDDIR)/hash_table.o $(BUILDDIR)/bst.o $(TESTDIR)/hash_table_test.c -o $(BUILDDIR)/hash_table_test

$(BUILDDIR)/vector.o: dir $(SOURCEDIR)/vector.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/vector.c -o $(BUILDDIR)/vector.o

$(BUILDDIR)/vector_test: dir $(BUILDDIR)/utils.o $(BUILDDIR)/vector.o $(TESTDIR)/vector_test.c
	$(CC) $(FLAGS) $(BUILDDIR)/utils.o $(BUILDDIR)/vector.o $(TESTDIR)/vector_test.c -o $(BUILDDIR)/vector_test

$(BUILDDIR)/generic_vector.o: dir $(SOURCEDIR)/generic_vector.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/generic_vector.c -o $(BUILDDIR)/generic_vector.o

$(BUILDDIR)/generic_vector_test: dir $(BUILDDIR)/utils.o $(BUILDDIR)/generic_vector.o $(TESTDIR)/generic_vector_test.c
	$(CC) $(FLAGS) $(BUILDDIR)/utils.o $(BUILDDIR)/generic_vector.o $(TESTDIR)/generic_vector_test.c -o $(BUILDDIR)/generic_vector_test

clean:
	rm -rf $(BUILDDIR)