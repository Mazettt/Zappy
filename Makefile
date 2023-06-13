##
## EPITECH PROJECT, 2021
## project
## File description:
## Makefile
##

all:
	make -C gui
	make -C server
	make -C ai

gui:
	make -C gui

server:
	make -C server

ai:
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
