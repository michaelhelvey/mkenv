CC = gcc
CFLAGS = -g -Wall -Werror -Wpedantic -std=c11
BUILD_DIR = build
EFILE = $(BUILD_DIR)/mkenv
OBJS = \
		  main.o 	\
		  args.o

$(EFILE): $(OBJS)
	@echo "Linking..."
	@$(CC) $(CFLAGS) -o $(EFILE) $(foreach src,$(OBJS),./build/$(src))
	@echo "Finished."

$(OBJS):
	$(CC) $(CFLAGS) -c src/$*.c -o build/$*.o

