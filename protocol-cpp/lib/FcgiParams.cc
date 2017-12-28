#include "FcgiParams.h"

using namespace fcgirecord;
FCGIParams::FCGIParams(std::map<std::string, std::string> m)
{
    init_FRecord();
    rec.set_type(fcgiprotocol::PARAMS);
    mp = m;
}
FCGIParams::~FCGIParams()
{
}

// std::string FCGIParams::__toString()
// {
//     std::string paramPayload;
//     std::cout << "FCGIParams:__toString" << std::endl;
//     return paramPayload;
// }

std::map<std::string, std::string> FCGIParams::getParamsMap()
{
    return mp;
}

std::string FCGIParams::packPayload()
{
    std::string payload;

    return payload;
}

std::string unpackPayload(std::string data)
{

    std::string payload;

    return payload;
}