#include <iostream>
#include <fstream>
#include <string>

//#include "../FCGILib/protocol.pb.h"
// #include "../FCGILib/BeginReq.pb.h"
// #include "../FCGILib/Params.pb.h"
// #include "../FCGILib/stdin.pb.h"
// #include "../FCGILib/Record.pb.h"

#include "../FCGILib/protocol.pb.h"
#include "../lib/FcgiRecord.h"
#include "../lib/FcgiBeginReq.h"
#include "../lib/FcgiParams.h"

#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <google/protobuf/text_format.h>

#include <map>
#include <iterator>

#define BUF_SIZE 5000
#define FCGI_SERVER "127.0.0.1"
#define FCGI_PORT "60000"
#define MAXDATASIZE 1000

using namespace std;
//using namespace record;
using namespace fcgiprotocol;
using namespace fcgirecord;

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int fcgi_connect(int *sock)
{
    int sockfd; //, numbytes;
    struct addrinfo hints, *servinfo, *p;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(FCGI_SERVER, FCGI_PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1)
        {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    freeaddrinfo(servinfo);
    *sock = sockfd;
    return 0;
}

int main(int argc, char **argv)
{

    map<string, string> paramMap;
    paramMap["DocumentRoot"] = "/var/www/html/";
    paramMap["Script_FileName"] = "phpInfo.php";
    paramMap["Request_Method"] = "GET";

    GOOGLE_PROTOBUF_VERIFY_VERSION;
    FCGIBeginReq *req;
    FCGIParams *param, *emptyParam;
    req = new FCGIBeginReq(RESPONDER);
    param = new FCGIParams(paramMap);
    static map<string, string> m;
    emptyParam = new FCGIParams(m);

    std::cout << "BeginReq:: " << req->__toString() << std::endl;
    param->__toString();
    emptyParam->__toString();

    return 0;
}