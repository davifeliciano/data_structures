CC = gcc
FLAGS = -g

SOURCEDIR = .
BUILDDIR = ./build

dir:
	mkdir -p $(BUILDDIR)

test: $(BUILDDIR)/linked_list_test
	./build/linked_list_test

memtest: $(BUILDDIR)/linked_list_test
	valgrind ./build/linked_list_test

$(BUILDDIR)/linked_list.o: dir $(SOURCEDIR)/linked_list/linked_list.c $(SOURCEDIR)/linked_list/linked_list.h
	$(CC) $(FLAGS) -c $(SOURCEDIR)/linked_list/linked_list.c -o $(BUILDDIR)/linked_list.o

$(BUILDDIR)/linked_list_test: dir $(BUILDDIR)/linked_list.o $(SOURCEDIR)/linked_list/test.c
	$(CC) $(FLAGS) $(BUILDDIR)/linked_list.o $(SOURCEDIR)/linked_list/test.c -o $(BUILDDIR)/linked_list_test

clean:
	rm -rf $(BUILDDIR)