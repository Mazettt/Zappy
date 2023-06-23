#pragma once

#include <functional>
#include <map>
#include "Socket.hpp"
#include "../../Utils/String.hpp"

namespace ZappyGui {
    class Game;

    class ServerLink {
        public:
            ServerLink(Game &game);
            ServerLink(Game &game, const std::string &ip, uint16_t port);
            ServerLink(const ServerLink &other) = delete;
            ServerLink(ServerLink &&other);
            ~ServerLink();

            ServerLink &operator=(const ServerLink &other) = delete;
            ServerLink &operator=(ServerLink &&other);

            void connect(const std::string &ip, uint16_t port);
            void disconnect();

            void askMapSize();
            void askTileContent(int x, int y);
            void askMapContent();
            void askTeamNames();
            void askPlayerPosition(int id);
            void askPlayerLevel(int id);
            void askPlayerInventory(int id);
            void askTimeUnit();
            void modifyTimeUnit(int timeUnit);

            void update();

        private:
            void _init();

            void _msz(const std::string &str);
            void _bct(const std::string &str);
            void _tna(const std::string &str);
            void _pnw(const std::string &str);
            void _ppo(const std::string &str);
            void _plv(const std::string &str);
            void _pin(const std::string &str);
            void _pex(const std::string &str);
            void _pbc(const std::string &str);
            void _pic(const std::string &str);
            void _pie(const std::string &str);
            void _pfk(const std::string &str);
            void _pdr(const std::string &str);
            void _pgt(const std::string &str);
            void _pdi(const std::string &str);
            void _enw(const std::string &str);
            void _egg(const std::string &str);
            void _ebo(const std::string &str);
            void _edi(const std::string &str);
            void _sgt(const std::string &str);
            void _sst(const std::string &str);
            void _seg(const std::string &str);
            void _smg(const std::string &str);
            void _suc(const std::string &str);
            void _sbp(const std::string &str);

            Game &_game;
            Socket _socket;
            std::map<std::string, void (ServerLink::*)(const std::string &str)> _responseFunctions;

            std::string _backup;
    };
}