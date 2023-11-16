CC = gcc
FLAGS = -g -I include

SOURCEDIR = .
BUILDDIR = ./build

dir:
	mkdir -p $(BUILDDIR)

test: $(BUILDDIR)/linked_list_test $(BUILDDIR)/bst_test
	./build/linked_list_test
	./build/bst_test

memtest: $(BUILDDIR)/linked_list_test $(BUILDDIR)/bst_test
	valgrind ./build/linked_list_test
	valgrind ./build/bst_test

$(BUILDDIR)/linked_list.o: dir $(SOURCEDIR)/linked_list/linked_list.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/linked_list/linked_list.c -o $(BUILDDIR)/linked_list.o

$(BUILDDIR)/linked_list_test: dir $(BUILDDIR)/linked_list.o $(SOURCEDIR)/linked_list/test.c
	$(CC) $(FLAGS) $(BUILDDIR)/linked_list.o $(SOURCEDIR)/linked_list/test.c -o $(BUILDDIR)/linked_list_test

$(BUILDDIR)/bst.o: dir $(SOURCEDIR)/bst/bst.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/bst/bst.c -o $(BUILDDIR)/bst.o

$(BUILDDIR)/bst_test: dir $(BUILDDIR)/bst.o $(SOURCEDIR)/bst/test.c
	$(CC) $(FLAGS) $(BUILDDIR)/bst.o $(SOURCEDIR)/bst/test.c -o $(BUILDDIR)/bst_test

clean:
	rm -rf $(BUILDDIR)