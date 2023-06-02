##
## EPITECH PROJECT, 2021
## project
## File description:
## Makefile
##

all: zappy_gui zappy_server

zappy_gui:
	make -C gui

zappy_server:
	make -C server

clean:
	make clean -C gui
	make clean -C server

fclean:
	make fclean -C gui
	make fclean -C server

re:	fclean all
