##
## EPITECH PROJECT, 2021
## project
## File description:
## Makefile
##

GUI_PATH	=	gui/
SERVER_PATH	=	server/
AI_PATH		=	ai/ai_martin_thomas/

all:
	make -C $(GUI_PATH)
	make -C $(SERVER_PATH)
	make -C $(AI_PATH)

gui:
	make -C $(GUI_PATH)

server:
	make -C $(SERVER_PATH)

ai:
	make -C $(AI_PATH)

clean:
	make clean -C $(GUI_PATH)
	make clean -C $(SERVER_PATH)
	make clean -C $(AI_PATH)

fclean:
	make fclean -C $(GUI_PATH)
	make fclean -C $(SERVER_PATH)
	make fclean -C $(AI_PATH)

re:	fclean all
