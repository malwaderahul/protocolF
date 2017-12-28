#include "FcgiBeginReq.h"
using namespace fcgirecord;
FCGIBeginReq::FCGIBeginReq(int role, int flags, std::string reserved1)
{
    init_FRecord();
    rec.set_type(fcgiprotocol::BEGIN_REQUEST);
    req.set_role(role);
    req.set_flags(flags);
    req.set_reserved1(reserved1);
}
FCGIBeginReq::~FCGIBeginReq()
{
}

int FCGIBeginReq::getRole()
{
    return req.role();
}
int FCGIBeginReq::getFlags()
{
    return req.flags();
}
// Record FCGIBeginReq::unpackPayload(){

// }
// std::string FCGIBeginReq::packPayload(){

// }
