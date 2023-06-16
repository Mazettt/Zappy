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

void ServerLink::askMapSize() // NOT USED
{
    _socket << "msz\n";
}

void ServerLink::askTileContent(int x, int y) // TODO
{
    _socket << "bct " + std::to_string(x) + " " + std::to_string(y) + "\n";
}

void ServerLink::askMapContent() // NOT USED
{
    _socket << "mct\n";
}

void ServerLink::askTeamNames() // NOT USED
{
    _socket << "tna\n";
}

void ServerLink::askPlayerPosition(int id) // NOT USED
{
    _socket << "ppo " + std::to_string(id) + "\n";
}

void ServerLink::askPlayerLevel(int id) // TODO
{
    _socket << "plv " + std::to_string(id) + "\n";
}

void ServerLink::askPlayerInventory(int id) // TODO
{
    _socket << "pin " + std::to_string(id) + "\n";
}

void ServerLink::askTimeUnit() // NOT USED
{
    _socket << "sgt\n";
}

void ServerLink::modifyTimeUnit(int timeUnit) // NOT USED
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
        // std::cout << "command: " << command << std::endl;
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
    _responseFunctions["egg"] = &ServerLink::_egg;
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
    int x = 0;
    int y = 0;

    iss >> tmp >> x >> y;
    this->_game._map.createMap(x, y);
}

void ServerLink::_bct(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    float x = 0.0;
    float z = 0.0;
    int food = 0;
    int linemate = 0;
    int deraumere = 0;
    int sibur = 0;
    int mendiane = 0;
    int phiras = 0;
    int thystame = 0;

    iss >> tmp >> x >> z >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;

    this->_game._map.updateResourceForTile({ (float)x, (float)z }, IResource::resourceType::BURGER, food);
    this->_game._map.updateResourceForTile({ (float)x, (float)z }, IResource::resourceType::LINEMATE, linemate);
    this->_game._map.updateResourceForTile({ (float)x, (float)z }, IResource::resourceType::DERAUMERE, deraumere);
    this->_game._map.updateResourceForTile({ (float)x, (float)z }, IResource::resourceType::SIBUR, sibur);
    this->_game._map.updateResourceForTile({ (float)x, (float)z }, IResource::resourceType::MENDIANE, mendiane);
    this->_game._map.updateResourceForTile({ (float)x, (float)z }, IResource::resourceType::PHIRAS, phiras);
    this->_game._map.updateResourceForTile({ (float)x, (float)z }, IResource::resourceType::THYSTAME, thystame);
}

void ServerLink::_tna(const std::string &str) // NOT USED
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
    int id = 0;
    int level = 0;
    int orientationNbr = 0;
    float x = 0.0;
    float z = 0.0;
    std::string teamName;

    iss >> tmp >> id >> x >> z >> orientationNbr >> level >> teamName;
    ZappyGui::Player::orientationAxis orientation =
        (orientationNbr == 1 ? ZappyGui::Player::orientationAxis::NORTH :
        (orientationNbr == 2 ? ZappyGui::Player::orientationAxis::EAST :
        (orientationNbr == 3 ? ZappyGui::Player::orientationAxis::SOUTH : ZappyGui::Player::orientationAxis::WEST)));
    PlayerArguments playerArgs = PlayerArguments(id, teamName, { x, 0.0, z }, {0.0f, 1.0f, 0.0f}, orientation, {0.6f, 0.6f, 0.6f}, 0, Player::animationPlayerType::PLAYER_NOTHING);
    this->_game._map.addPlayerForTile(playerArgs);
}

void ServerLink::_ppo(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id = 0;
    int orientationNbr = 0;;
    float x = 0.0;
    float z = 0.0;

    iss >> tmp >> id >> x >> z >> orientationNbr;
    ZappyGui::Player::orientationAxis orientation =
        (orientationNbr == 1 ? ZappyGui::Player::orientationAxis::NORTH :
        (orientationNbr == 2 ? ZappyGui::Player::orientationAxis::EAST :
        (orientationNbr == 3 ? ZappyGui::Player::orientationAxis::SOUTH : ZappyGui::Player::orientationAxis::WEST)));
    this->_game._map.movePlayer(id, x, z, orientation);
}

void ServerLink::_plv(const std::string &str)
{
    std::istringstream iss(str);
    std::string tmp;
    int id = 0;
    int level = 0;

    iss >> tmp >> id >> level;
    this->_game._map.setPlayerLevel(id, level);
}

void ServerLink::_pin(const std::string &str) // TODO
{
    std::istringstream iss(str);
    std::string tmp;
    int id = 0;
    int x = 0;
    int y = 0;
    int food = 0;
    int linemate = 0;
    int deraumere = 0;
    int sibur = 0;
    int mendiane = 0;
    int phiras = 0;
    int thystame = 0;

    iss >> tmp >> id >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
    this->_game._map.updatePlayerInventory(id, food, linemate, deraumere, sibur, mendiane, phiras, thystame);
    std::cout << "Player inventory: " << id << " " << x << " " << y << " -> " << food << " " << linemate << " " << deraumere << " " << sibur << " " << mendiane << " " << phiras << " " << thystame << std::endl;
}

void ServerLink::_pex(const std::string &str) // TODO
{
    std::istringstream iss(str);
    std::string tmp;
    int id = 0;

    iss >> tmp >> id;
    std::cout << "Player explosion: " << id << std::endl;
}

void ServerLink::_pbc(const std::string &str) // TODO
{
    std::istringstream iss(str);
    std::string tmp;
    int id = 0;
    std::string message;

    iss >> tmp >> id >> message;
    std::cout << "Player broadcast: " << id << " " << message << std::endl;
}

void ServerLink::_pic(const std::string &str) // TO CHECK
{
    std::istringstream iss(str);
    std::string tmp;
    int level = 0;
    float x = 0.0;
    float z = 0.0;
    std::vector<int> ids;

    iss >> tmp >> x >> z >> level;
    for (int id; iss >> id;)
        ids.push_back(id);
    this->_game._map.StartPlayersLeveling(ids, level, x, z);
    std::cout << std::endl;
}

void ServerLink::_pie(const std::string &str) // TO CHECK
{
    std::istringstream iss(str);
    std::string tmp;
    int result;
    float x = 0.0;
    float z = 0.0;

    iss >> tmp >> x >> z >> result;
    this->_game._map.EndPlayersLeveling(x, z, result);
}

void ServerLink::_pfk(const std::string &str) // TODO
{
    std::istringstream iss(str);
    std::string tmp;
    int id = 0;

    iss >> tmp >> id;
    std::cout << "Player fork: " << id << std::endl;
}

void ServerLink::_pdr(const std::string &str) // TO CHECK
{
    std::istringstream iss(str);
    std::string tmp;
    int id = 0;
    int resource = 0;

    iss >> tmp >> id >> resource;
    this->_game._map.dropResource(id, (ZappyGui::IResource::resourceType) resource); // TO CHECK if resourceType work correctly
}

void ServerLink::_pgt(const std::string &str) // TO CHECK
{
    std::istringstream iss(str);
    std::string tmp;
    int id = 0;
    int resource = 0;

    iss >> tmp >> id >> resource;
    this->_game._map.collectResource(id, (ZappyGui::IResource::resourceType) resource); // TO CHECK if resourceType work correctly
}

void ServerLink::_pdi(const std::string &str) // TO DO
{
    std::istringstream iss(str);
    std::string tmp;
    int id = 0;

    iss >> tmp >> id;
    this->_game._map.deadPlayer(id);
}

void ServerLink::_enw(const std::string &str) // TO DO
{
    std::istringstream iss(str);
    std::string tmp;
    int eggId = 0;
    int playerId = 0;
    int x = 0;
    int y = 0;

    iss >> tmp >> eggId >> playerId >> x >> y;
    std::cout << "Egg layed: " << eggId << " " << playerId << " " << x << " " << y << std::endl;
    this->_game._map.addEggForTile({ (float)x, (float)y }, eggId);
}

void ServerLink::_egg(const std::string &str) // TO DO
{
    std::istringstream iss(str);
    std::string tmp;
    int eggId = 0;
    int x = 0;
    int y = 0;

    iss >> tmp >> eggId >> x >> y;
    std::cout << "New egg: " << eggId << " " << x << " " << y << std::endl;
    this->_game._map.addEggForTile({ (float)x, (float)y }, eggId);
}

void ServerLink::_ebo(const std::string &str) // TO DO
{
    std::istringstream iss(str);
    std::string tmp;
    int eggId = 0;

    iss >> tmp >> eggId;
    std::cout << "Egg born: " << eggId << std::endl;
    this->_game._map.removeEgg(eggId);
}

void ServerLink::_edi(const std::string &str) // TO DO
{
    std::istringstream iss(str);
    std::string tmp;
    int eggId = 0;

    iss >> tmp >> eggId;
    std::cout << "Egg death: " << eggId << std::endl;
}

void ServerLink::_sgt(const std::string &str) // TO DO
{
    std::istringstream iss(str);
    std::string tmp;
    int time = 0;

    iss >> tmp >> time;
    std::cout << "Time unit: " << time << std::endl;
}

void ServerLink::_sst(const std::string &str) // TO DO
{
    std::istringstream iss(str);
    std::string tmp;
    int time = 0;

    iss >> tmp >> time;
    std::cout << "Time unit set: " << time << std::endl;
}

void ServerLink::_seg(const std::string &str) // TO DO
{
    std::istringstream iss(str);
    std::string tmp;
    std::string teamName;

    iss >> tmp >> teamName;
    std::cout << "End of game: " << teamName << std::endl;
}

void ServerLink::_smg(const std::string &str) // TO DO
{
    std::istringstream iss(str);
    std::string tmp;
    std::string message;

    iss >> tmp >> message;
    std::cout << "Server message: " << message << std::endl;
}

void ServerLink::_suc(const std::string &str) // TO DO
{
    std::istringstream iss(str);
    std::string tmp;

    iss >> tmp;
    std::cout << "Unknown command" << std::endl;
}

void ServerLink::_sbp(const std::string &str) // TO DO
{
    std::istringstream iss(str);
    std::string tmp;

    iss >> tmp;
    std::cout << "Bad parameter" << std::endl;
}
