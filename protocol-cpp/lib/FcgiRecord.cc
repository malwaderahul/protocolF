#include "FcgiRecord.h"

using namespace fcgirecord;

void FRecord::init_FRecord()
{
    rec.set_version(fcgiprotocol::VERSION_1);
    rec.set_type(fcgiprotocol::UNKNOWN_TYPE);
    rec.set_request_id(fcgiprotocol::NULL_REQUEST_ID);
    rec.set_reserved(0);
    rec.set_contentlength(0);
    rec.set_paddinglength(0);
    rec.set_contentdata("");
    rec.set_paddingdata("");
}
// FRecord::~FRecord()
// {
// }

std::string FRecord::unpack(std::string data)
{
    std::string headerPacket;
}

/**
     * Returns the binary message representation of record
     *
     * @return string
*/
std::string FRecord::__toString()
{
    std::string headerPacket, payloadPacket, paddingPacket("");
    rec.SerializeToString(&headerPacket);
    payloadPacket = this->packPayload();
    paddingPacket += "";
    std::cout << "Record::toString : " << headerPacket << std::endl;
    return headerPacket + payloadPacket + paddingPacket;
}

int FRecord::getVersion()
{
    return rec.version();
}
int FRecord::getType()
{
    return rec.type();
}
int FRecord::getRequestId()
{
    return rec.request_id();
}
void FRecord::setRequestId(int id)
{
    rec.set_request_id(id);
}
int FRecord::getContentLength()
{
    return rec.contentlength();
}
int FRecord::getPaddingLength()
{
    return rec.paddinglength();
}
void FRecord::setContentData(std::string data)
{
    rec.set_contentdata(data);
    rec.set_contentlength(data.length());
    int extraLength = data.length() % 8;
    int paddingLength = extraLength ? (8 - extraLength) : 0;
    rec.set_paddinglength(paddingLength);
}
void FRecord::setPaddingData(std::string data)
{
    rec.set_paddingdata(data);
}
std::string FRecord::getContentData()
{
    return rec.contentdata();
}
std::string FRecord::getPaddingData()
{
    return rec.paddingdata();
}

std::string FRecord::packPayload()
{
    std::string payloadPacket;
    payloadPacket += "";
    return payloadPacket;
}
void FRecord::unpackPayload(std::string)
{
}