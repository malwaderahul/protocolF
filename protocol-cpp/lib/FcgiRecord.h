#ifndef FCGIRECORD_H
#define FCGIRECORD_H

#include "../FCGILib/protocol.pb.h"
#include <string>
namespace fcgirecord
{
class FRecord
{

public:
  fcgiprotocol::Record rec;
  void init_FRecord();
  //~FRecord();
  std::string unpack(std::string);
  std::string __toString();

  int getVersion();
  int getType();
  int getRequestId();
  void setRequestId(int);
  int getContentLength();
  int getPaddingLength();
  void setContentData(std::string);
  void setPaddingData(std::string);
  std::string getContentData();
  std::string getPaddingData();

  std::string packPayload();
  void unpackPayload(std::string);
};
}

#endif