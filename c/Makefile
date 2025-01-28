CC=gcc
#CFLAGS=
#CPPFLAGS=
BUILD := build
FILES := lib/linkedlist.c

all: \
	clean\
	examplemake

examplemake: 
	mkdir $(BUILD) 
	cc main.c -o $(BUILD)/c_examples $(FILES)

clean: 
	rm -rf $(BUILD)