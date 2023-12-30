CC=gcc
LD=ld
WARNS=-Wall -pedantic -Wextra
CFLAGS=-g3 -std=gnu11 ${WARNS}
LIBS=


# shell3 is an executable I want to build, the rest are handy things
all: tags headers shell


# This builds visual symbol (.vs) files and the header files.
headers: *.c tags
	./headers.sh

# Tags (for C code) are too handy not to keep up to date.
# This lets us use Control-] with vim (ctags command).
# Alternatively, we can use etags with emacs (etags command).
# Comment out the command that you're NOT using.
tags: *.c
#    ctags -R .
	etags -R .


# This is a link rule, we have a universal compile rule down below
# Output is the target of the rule : -o $@
# I want to link all of the dependencies: $^
shell: shell3.o
	${CC} -g -o $@ $^ ${LIBS}

shell3.o: shell3.c
	${CC} -g -c $<

# This is our master compiler rule to generate .o files.
# It needs all 4 warnings (see WARNS variable defined above)
%.o:%.c *.h
	${CC} ${CFLAGS} -c $< -o $@
