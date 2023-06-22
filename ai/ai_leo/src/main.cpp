/*
** EPITECH PROJECT, 2022
** ai_leo
** File description:
** main.cpp
*/

#include "Socket/Socket.hpp"
#include "ProgramArgs/ProgramArgs.hpp"
#include "Player/Player.hpp"

void aff_usage()
{
    std::cout << "USAGE:\t./zappy_ai -p port -n name -h machine" << std::endl;
    std::cout << "\tport\tis the port number" << std::endl;
    std::cout << "\tname\tis the name of the team" << std::endl;
    std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
}

void first_connection(Socket &socket, ProgramArgs &args, Player &player)
{
    socket.connectSocket(args.getMachine(), args.getPort());
    std::string msg = socket.receiveSocket();

    socket.sendSocket(args.getName() + "\n");
    msg = socket.receiveSocket();
    std::string p_num_str = msg.substr(0, msg.find("\n"));
    int p_num = std::stoi(p_num_str);
    player.playerNumber = p_num;
    std::string map_size_str_x = msg.substr(msg.find("\n") + 1, msg.find(" "));
    int map_size_x = std::stoi(map_size_str_x);
    std::string map_size_str_y = msg.substr(msg.find(" ") + 1, msg.find("\n"));
    int map_size_y = std::stoi(map_size_str_y);
    player.mapSizeX = map_size_x;
    player.mapSizeY = map_size_y;
}

int main(int ac, char **av)
{
    ProgramArgs args(ac, av);
    Player player;
    Socket socket;
    player.socket = socket;
    first_connection(socket, args, player);
    player.play();
}