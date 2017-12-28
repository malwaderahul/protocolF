#ifndef __FCGIBEGINREQ_H
#define __FCGIBEGINREQ_H

#include "../FCGILib/protocol.pb.h"
#include "FcgiRecord.h"
#include <string>
namespace fcgirecord
{

class FCGIBeginReq : public fcgirecord::FRecord
{
  fcgiprotocol::BeginRequest req;
  //fcgiprotocol::Record rec;

public:
  FCGIBeginReq(int role = fcgiprotocol::UNKNOWN_ROLE, int flags = 0, std::string reserved1 = "");
  ~FCGIBeginReq();
  int getRole();
  int getFlags();
  //  Record unpackPayload();
  //  std::string packPayload();
};
}

#endif
