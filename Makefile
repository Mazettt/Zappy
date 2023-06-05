##
## EPITECH PROJECT, 2021
## project
## File description:
## Makefile
##

all: zappy_gui zappy_server zappy_ai

zappy_gui:
	make -C gui

zappy_server:
	make -C server

zappy_ai:
	make -C ai

clean:
	make clean -C gui
	make clean -C server
	make clean -C ai

fclean:
	make fclean -C gui
	make fclean -C server
	make fclean -C ai

re:	fclean all
