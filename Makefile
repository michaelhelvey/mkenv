CC = gcc
CFLAGS = -O -Wall -Werror -Wpedantic -std=c11
BUILD_DIR = build
EFILE = $(BUILD_DIR)/mkenv
INSTALL_LOC = ~/.local/bin/mkenv
OBJS = \
		  main.o 	\
		  args.o 	\
		  file.o

$(EFILE): $(OBJS)
	@echo "Linking..."
	@$(CC) $(CFLAGS) -o $(EFILE) $(foreach src,$(OBJS),./build/$(src))
	@echo "Finished."

$(OBJS):
	$(CC) $(CFLAGS) -c src/$*.c -o build/$*.o

install: $(EFILE)
	cp $(EFILE) $(INSTALL_LOC)

