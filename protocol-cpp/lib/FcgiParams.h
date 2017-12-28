#ifndef FCGIPARAMS_H
#define FCGIPARAMS_H

#include "../FCGILib/protocol.pb.h"
#include "FcgiRecord.h"
#include <string>
#include <map>
#include <iterator>
namespace fcgirecord
{
class FCGIParams : public fcgirecord::FRecord
{
    std::map<std::string, std::string> mp;

  public:
    FCGIParams(std::map<std::string, std::string> mp);
    ~FCGIParams();
    //std::string __toString();
    std::map<std::string, std::string> getParamsMap();
    virtual std::string packPayload();
    std::string unpackPayload(std::string data);
};
}

#endif
