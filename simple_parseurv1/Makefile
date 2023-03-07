NAME := VINCENT_MICHEL_RENIER_SIMPLE_PARSEUR
INC_DIR := include
MAIN := simple_parseur
SRC_C := $(wildcard src/*.c)

$(MAIN): $(SRC_C)
	gcc $^ -o $@ -Og -g -Wall -Wextra -I$(INC_DIR)

tests: $(MAIN)
	@ python3 execute.py -v

clean:
	rm -f $(MAIN) src/*~ src/*.swap
	rm -rf __pycache__ .pytest_cache

tar: clean
	@ dir=$$(basename "$$PWD") && cd .. && tar cvfz $(NAME).tgz  "$$dir"
	@ echo "==="; echo "Created ../$(NAME).tgz"
