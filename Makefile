CC = gcc
FLAGS = -g -I include

SOURCEDIR = .
BUILDDIR = ./build
TESTDIR = $(SOURCEDIR)/test

dir:
	mkdir -p $(BUILDDIR)

test: $(BUILDDIR)/linked_list_test $(BUILDDIR)/bst_test $(BUILDDIR)/hash_table_test $(BUILDDIR)/vector_test
	$(BUILDDIR)/linked_list_test
	$(BUILDDIR)/bst_test
	$(BUILDDIR)/hash_table_test
	$(BUILDDIR)/vector_test

memtest: $(BUILDDIR)/linked_list_test $(BUILDDIR)/bst_test $(BUILDDIR)/hash_table_test $(BUILDDIR)/vector_test
	valgrind $(BUILDDIR)/linked_list_test
	valgrind $(BUILDDIR)/bst_test
	valgrind $(BUILDDIR)/hash_table_test
	valgrind $(BUILDDIR)/vector_test

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

$(BUILDDIR)/hash_table_test: dir $(BUILDDIR)/hash_table.o $(BUILDDIR)/bst.o $(TESTDIR)/hash_table_test.c
	$(CC) $(FLAGS) $(BUILDDIR)/hash_table.o $(BUILDDIR)/bst.o $(TESTDIR)/hash_table_test.c -o $(BUILDDIR)/hash_table_test

$(BUILDDIR)/vector.o: dir $(SOURCEDIR)/vector.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/vector.c -o $(BUILDDIR)/vector.o

$(BUILDDIR)/vector_test: dir $(BUILDDIR)/vector.o $(TESTDIR)/vector_test.c
	$(CC) $(FLAGS) $(BUILDDIR)/vector.o $(TESTDIR)/vector_test.c -o $(BUILDDIR)/vector_test

clean:
	rm -rf $(BUILDDIR)