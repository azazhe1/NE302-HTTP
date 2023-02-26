AUTEURS := VINCENT
INC_DIR := include
MAIN := main
SRC_C := $(wildcard src/*.c)

$(MAIN): $(SRC_C)
	gcc $^ -o $@ -Og -g -Wall -Wextra -I$(INC_DIR) -lm
