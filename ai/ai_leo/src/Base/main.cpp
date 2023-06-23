/*
** EPITECH PROJECT, 2022
** Base
** File description:
** main.cpp
*/

#include "Args.hpp"
#include "ElevCond.hpp"
#include "MyError.hpp"
#include "ServerLink.hpp"
#include "Socket.hpp"
#include "String.hpp"
#include "Tile.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>
#include <vector>

void disp_inventory(std::map<my::Resource, int> inventory)
{
    std::cout << "Inventory:" << std::endl;
    for (auto it = inventory.begin(); it != inventory.end(); it++) {
        std::cout << "\t" << it->first << ": " << it->second << std::endl;
    }
}

void go_to(my::ServerLink &s_l, int destination)
{
    int x = 0;
    int y = 0;

    if (destination == 0) {
        return;
    } else if (destination == 1) {
        x = 1;
        y = -1;
    } else if (destination == 2) {
        x = 1;
        y = 0;
    } else if (destination == 3) {
        x = 1;
        y = 1;
    } else if (destination == 4) {
        x = 2;
        y = -2;
    } else if (destination == 5) {
        x = 2;
        y = -1;
    } else if (destination == 6) {
        x = 2;
        y = 0;
    } else if (destination == 7) {
        x = 2;
        y = 1;
    } else if (destination == 8) {
        x = 2;
        y = 2;
    } else if (destination == 9) {
        x = 3;
        y = -3;
    } else if (destination == 10) {
        x = 3;
        y = -2;
    } else if (destination == 11) {
        x = 3;
        y = -1;
    } else if (destination == 12) {
        x = 3;
        y = 0;
    } else if (destination == 13) {
        x = 3;
        y = 1;
    } else if (destination == 14) {
        x = 3;
        y = 2;
    } else if (destination == 15) {
        x = 3;
        y = 3;
    } else if (destination == 16) {
        x = 4;
        y = -4;
    } else if (destination == 17) {
        x = 4;
        y = -3;
    } else if (destination == 18) {
        x = 4;
        y = -2;
    } else if (destination == 19) {
        x = 4;
        y = -1;
    } else if (destination == 20) {
        x = 4;
        y = 0;
    } else if (destination == 21) {
        x = 4;
        y = 1;
    } else if (destination == 22) {
        x = 4;
        y = 2;
    } else if (destination == 23) {
        x = 4;
        y = 3;
    } else if (destination == 24) {
        x = 4;
        y = 4;
    }
    if (x > 0) {
        for (int i = 0; i < x; i++) {
            s_l.forward();
        }
    }
    if (y > 0) {
        s_l.right();
        for (int i = 0; i < y; i++) {
            s_l.forward();
        }
    } else if (y < 0) {
        s_l.left();
        for (int i = 0; i < y; i++) {
            s_l.forward();
        }
    }
}

void vacuum(my::ServerLink &s_l)
{
    std::vector<my::Tile> tiles = s_l.look();
    my::Tile first_tile = tiles[0];

    if (first_tile.getNbr(my::Resource::LINEMATE) > 0) {
        for (int i = 0; i < first_tile.getNbr(my::Resource::LINEMATE); i++) {
            s_l.take(my::Resource::LINEMATE);
        }
    }
    if (first_tile.getNbr(my::Resource::DERAUMERE) > 0) {
        for (int i = 0; i < first_tile.getNbr(my::Resource::DERAUMERE); i++) {
            s_l.take(my::Resource::DERAUMERE);
        }
    }
    if (first_tile.getNbr(my::Resource::SIBUR) > 0) {
        for (int i = 0; i < first_tile.getNbr(my::Resource::SIBUR); i++) {
            s_l.take(my::Resource::SIBUR);
        }
    }
    if (first_tile.getNbr(my::Resource::MENDIANE) > 0) {
        for (int i = 0; i < first_tile.getNbr(my::Resource::MENDIANE); i++) {
            s_l.take(my::Resource::MENDIANE);
        }
    }
    if (first_tile.getNbr(my::Resource::PHIRAS) > 0) {
        for (int i = 0; i < first_tile.getNbr(my::Resource::PHIRAS); i++) {
            s_l.take(my::Resource::PHIRAS);
        }
    }
    if (first_tile.getNbr(my::Resource::THYSTAME) > 0) {
        for (int i = 0; i < first_tile.getNbr(my::Resource::THYSTAME); i++) {
            s_l.take(my::Resource::THYSTAME);
        }
    }
    if (first_tile.getNbr(my::Resource::FOOD) > 0) {
        for (int i = 0; i < first_tile.getNbr(my::Resource::FOOD); i++) {
            s_l.take(my::Resource::FOOD);
        }
    }
}

void crave_food(my::ServerLink &s_l)
{
    std::vector<my::Tile> tiles = s_l.look();
    int food_count[25] = {0};
    std::map<my::Resource, int> inventory = s_l.inventory();
    bool found_food = false;

    while (inventory[my::Resource::FOOD] < 7) {
        for (auto it = tiles.begin(); it != tiles.end(); it++) {
            if (it->getNbr(my::Resource::FOOD) > 0) {
                found_food = true;
                go_to(s_l, it - tiles.begin());
                vacuum(s_l);
            }
        }
        if (found_food == false) {
            s_l.forward();
            int random = rand() % 4;
            if (random == 0) {
                s_l.left();
            } else if (random == 1) {
                s_l.right();
            } else if (random == 2) {
                s_l.right();
                s_l.right();
            } else if (random == 3) {
                s_l.left();
                s_l.left();
            }
        }
        std::cout << "Found food: " << found_food << std::endl;
        found_food = false;
        tiles = s_l.look();
        inventory = s_l.inventory();
    }

}

void play(my::ServerLink s_l)
{
    while (1) {
        std::map<my::Resource, int> inventory = s_l.inventory();
        if (inventory[my::Resource::FOOD] < 7) {
            crave_food(s_l);
        }
    }
}

int main(int ac, char **argv)
{
    my::Args args(ac, argv);
    int port = args.getFlagValues<int>("-p")[0];
    std::vector <std::string> teamName = args.getFlagValues<std::string>("-n");
    std::vector <std::string> machineName = args.getFlagValues<std::string>("-h");
    std::string machine_name;
    std::string team_name;
    if (machineName.size() < 1) {
        machine_name = "127.0.0.1";
    } else {
        machine_name = "127.0.0.1";
    }
    if (teamName.size() < 1) {
        std::cerr << "Error: No team name given" << std::endl;
        return 84;
    } else {
        team_name = teamName[0];
    }

    try {
        my::Socket socket(machine_name, port);
    } catch (my::MyError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    try {
        play(my::ServerLink(args));
    } catch (my::MyError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}