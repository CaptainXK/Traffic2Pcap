.PHONY:clean check_obj_dir

CC := gcc
OBJ_DIR := obj
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS) )
INC := -Iinclude
FLAGS := -lpcap


test.app:check_obj_dir $(OBJS)
	@$(CC) $(INC) $(OBJS) -o $@ -g $(FLAGS)


check_obj_dir:
	@if test ! -d $(OBJ_DIR);\
		then\
		mkdir $(OBJ_DIR);\
	fi


$(OBJ_DIR)/%.o:%.c
	@$(CC) $(INC) -c $< -o $@ -g $(FLAGS)


test:test.app
	@$(EXEC) ./test.app


clean:
	rm -rf $(OBJ_DIR)/*.o *.app *.pcap
