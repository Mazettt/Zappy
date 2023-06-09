#include "../../includes/Server/ServerLink.hpp"
#include "../../includes/Game.hpp"

using namespace ZappyGui;

ServerLink::ServerLink(Game &game): _game(game) {
    _init();
}

ServerLink::ServerLink(Game &game, const std::string &ip, uint16_t port): _game(game), _socket(ip, port) {
    _init();
    connect(ip, port);
}

ServerLink::ServerLink(ServerLink &&other): _game(other._game), _socket(std::move(other._socket)) {}

ServerLink::~ServerLink() {}

ServerLink &ServerLink::operator=(ServerLink &&other)
{
    _socket = std::move(other._socket);
    return *this;
}

void ServerLink::connect(const std::string &ip, uint16_t port)
{
    _socket.connect(ip, port);
    _socket << "GRAPHIC\n";
}

void ServerLink::askMapSize()
{
    _socket << "msz\n";
}

void ServerLink::askTileContent(int x, int y)
{
    _socket << "bct " + std::to_string(x) + " " + std::to_string(y) + "\n";
}

void ServerLink::askMapContent()
{
    _socket << "mct\n";
}

void ServerLink::askTeamNames()
{
    _socket << "tna\n";
}

void ServerLink::askPlayerPosition(int id)
{
    _socket << "ppo " + std::to_string(id) + "\n";
}

void ServerLink::askPlayerLevel(int id)
{
    _socket << "plv " + std::to_string(id) + "\n";
}

void ServerLink::askPlayerInventory(int id)
{
    _socket << "pin " + std::to_string(id) + "\n";
}

void ServerLink::askTimeUnit()
{
    _socket << "sgt\n";
}

void ServerLink::modifyTimeUnit(int timeUnit)
{
    _socket << "sst " + std::to_string(timeUnit) + "\n";
}

void ServerLink::update()
{
    std::string buff;
    if (!_socket.tryRead(buff))
        return;
    buff = buff.substr(0, buff.size() - 1);
    std::vector<std::string> commands = split(buff, '\n');
    for (const auto &command : commands) {
        std::cout << "command: " << command << std::endl;
        if (_responseFunctions.find(command.substr(0, 3)) != _responseFunctions.end())
            (this->*_responseFunctions[command.substr(0, 3)])(command);
    }
}

void ServerLink::_init()
{
    _responseFunctions["msz"] = &ServerLink::_msz;
    _responseFunctions["bct"] = &ServerLink::_bct;
    _responseFunctions["tna"] = &ServerLink::_tna;
    _responseFunctions["pnw"] = &ServerLink::_pnw;
    _responseFunctions["ppo"] = &ServerLink::_ppo;
    _responseFunctions["plv"] = &ServerLink::_plv;
    _responseFunctions["pin"] = &ServerLink::_pin;
    _responseFunctions["pex"] = &ServerLink::_pex;
    _responseFunctions["pbc"] = &ServerLink::_pbc;
    _responseFunctions["pic"] = &ServerLink::_pic;
    _responseFunctions["pie"] = &ServerLink::_pie;
    _responseFunctions["pfk"] = &ServerLink::_pfk;
    _responseFunctions["pdr"] = &ServerLink::_pdr;
    _responseFunctions["pgt"] = &ServerLink::_pgt;
    _responseFunctions["pdi"] = &ServerLink::_pdi;
    _responseFunctions["enw"] = &ServerLink::_enw;
    _responseFunctions["ebo"] = &ServerLink::_ebo;
    _responseFunctions["edi"] = &ServerLink::_edi;
    _responseFunctions["sgt"] = &ServerLink::_sgt;
    _responseFunctions["sst"] = &ServerLink::_sst;
    _responseFunctions["seg"] = &ServerLink::_seg;
    _responseFunctions["smg"] = &ServerLink::_smg;
    _responseFunctions["suc"] = &ServerLink::_suc;
    _responseFunctions["sbp"] = &ServerLink::_sbp;
}

void ServerLink::_msz(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int x, y;

    iss >> tmp >> x >> y;
    this->_game._map.createMap(x, y);
}

void ServerLink::_bct(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame;

    iss >> tmp >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
    
    this->_game._map.addResourceForTile({ (float)x, (float)y }, IResource::resourceType::BURGER, food);
    this->_game._map.addResourceForTile({ (float)x, (float)y }, IResource::resourceType::LINEMATE, linemate);
    this->_game._map.addResourceForTile({ (float)x, (float)y }, IResource::resourceType::DERAUMERE, deraumere);
    this->_game._map.addResourceForTile({ (float)x, (float)y }, IResource::resourceType::SIBUR, sibur);
    this->_game._map.addResourceForTile({ (float)x, (float)y }, IResource::resourceType::MENDIANE, mendiane);
    this->_game._map.addResourceForTile({ (float)x, (float)y }, IResource::resourceType::PHIRAS, phiras);
    this->_game._map.addResourceForTile({ (float)x, (float)y }, IResource::resourceType::THYSTAME, thystame);

}

void ServerLink::_tna(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp, teamName;

    iss >> tmp >> teamName;
    std::cout << "Team name: " << teamName << std::endl;
}

void ServerLink::_pnw(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, x, y, orientation, level;
    std::string teamName;

    iss >> tmp >> id >> x >> y >> orientation >> level >> teamName;
    std::cout << "Player new: " << id << " " << x << " " << y << " " << orientation << " " << level << " " << teamName << std::endl;
}

void ServerLink::_ppo(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, x, y, orientation;

    iss >> tmp >> id >> x >> y >> orientation;
    std::cout << "Player position: " << id << " " << x << " " << y << " " << orientation << std::endl;
}

void ServerLink::_plv(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, level;

    iss >> tmp >> id >> level;
    std::cout << "Player level: " << id << " " << level << std::endl;
}

void ServerLink::_pin(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, x, y, food, linemate, deraumere, sibur, mendiane, phiras, thystame;

    iss >> tmp >> id >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
    std::cout << "Player inventory: " << id << " " << x << " " << y << " -> " << food << " " << linemate << " " << deraumere << " " << sibur << " " << mendiane << " " << phiras << " " << thystame << std::endl;
}

void ServerLink::_pex(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id;

    iss >> tmp >> id;
    std::cout << "Player explosion: " << id << std::endl;
}

void ServerLink::_pbc(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id;
    std::string message;

    iss >> tmp >> id >> message;
    std::cout << "Player broadcast: " << id << " " << message << std::endl;
}

void ServerLink::_pic(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int x, y, level;
    std::vector<int> ids;

    iss >> tmp >> x >> y >> level;
    for (int id; iss >> id;)
        ids.push_back(id);
    std::cout << "Player incantation: " << x << " " << y << " " << level << " -> ";
    for (auto id : ids)
        std::cout << id << " ";
    std::cout << std::endl;
}

void ServerLink::_pie(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int x, y, result;

    iss >> tmp >> x >> y >> result;
    std::cout << "Player incantation end: " << x << " " << y << " " << result << std::endl;
}

void ServerLink::_pfk(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id;

    iss >> tmp >> id;
    std::cout << "Player fork: " << id << std::endl;
}

void ServerLink::_pdr(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, resource;

    iss >> tmp >> id >> resource;
    std::cout << "Player drop: " << id << " " << resource << std::endl;
}

void ServerLink::_pgt(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id, resource;

    iss >> tmp >> id >> resource;
    std::cout << "Player take: " << id << " " << resource << std::endl;
}

void ServerLink::_pdi(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id;

    iss >> tmp >> id;
    std::cout << "Player death: " << id << std::endl;
}

void ServerLink::_enw(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int eggId, playerId, x, y;

    iss >> tmp >> eggId >> playerId >> x >> y;
    std::cout << "Egg new: " << eggId << " " << playerId << " " << x << " " << y << std::endl;
}

void ServerLink::_ebo(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int eggId;

    iss >> tmp >> eggId;
    std::cout << "Egg born: " << eggId << std::endl;
}

void ServerLink::_edi(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int eggId;

    iss >> tmp >> eggId;
    std::cout << "Egg death: " << eggId << std::endl;
}

void ServerLink::_sgt(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int time;

    iss >> tmp >> time;
    std::cout << "Time unit: " << time << std::endl;
}

void ServerLink::_sst(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int time;

    iss >> tmp >> time;
    std::cout << "Time unit set: " << time << std::endl;
}

void ServerLink::_seg(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    std::string teamName;

    iss >> tmp >> teamName;
    std::cout << "End of game: " << teamName << std::endl;
}

void ServerLink::_smg(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    std::string message;

    iss >> tmp >> message;
    std::cout << "Server message: " << message << std::endl;
}

void ServerLink::_suc(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;

    iss >> tmp;
    std::cout << "Unknown command" << std::endl;
}

void ServerLink::_sbp(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;

    iss >> tmp;
    std::cout << "Bad parameter" << std::endl;
}
