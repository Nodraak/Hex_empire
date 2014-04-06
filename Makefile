
#=== VARIABLES ===
NAME = Hex_Empire
INC_DIR = includes/
SRCS_DIR = srcs/
SRCS = ft_sdl.c main.c ft_map.c ft_event.c ft_tile.c ft_game.c ft_ia.c
OBJ = $(SRCS:.c=.o)
OBJ_DIR = obj/
INCLUDE = -I/usr/local/include/SDL2
LIBS = -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx

BONUS = -Wswitch-default -Wunreachable-code -Waggregate-return -Wcast-align -Wcast-qual -Wconversion -Winline -Wlong-long -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wpointer-arith -Wredundant-decls -Wreturn-type -Wstrict-prototypes -Wswitch -Wvla

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -I $(INC_DIR) $(INCLUDE) $(BONUS)


#=== SPECIAL ===
.PHONY: all, clean, mrproper, re, cls
.SUFFIXES:

#=== REGLES BINAIRES ===
all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJ))
	@echo "building app"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(LIBS) $^ -o $@

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(INC_DIR)constantes.h $(INC_DIR)%.h
	@echo "building $@"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(SRCS_DIR)main.c $(INC_DIR)constantes.h
	@echo "building $@"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

#=== REGLES SPECIALES ===
cls:
	clear

clean:
	@echo "cleaning directory (*.obj)"
	@rm -f $(addprefix $(OBJ_DIR), $(OBJ))

mrproper: clean
	@echo "cleaning directory (app + *.obj)"
	@rm -f $(NAME)

re: cls mrproper all
	@echo "re"

