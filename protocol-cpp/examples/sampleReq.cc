#include <iostream>
#include <fstream>
#include <string>

#include <FCGI.pb.h>
#include <BeginReq.pb.h>
#include <Params.pb.h>
#include <stdin.pb.h>
#include <Record.pb.h>

#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <google/protobuf/text_format.h>

#define BUF_SIZE 5000
#define FCGI_SERVER "127.0.0.1"
#define FCGI_PORT "60000"
#define MAXDATASIZE 1000

using namespace std;
using namespace record;
using namespace protocol;

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
    int sockfd;
    // if (argc != 2)
    // {
    //     printf("Usage: %s <Absolute path of file>\n", argv[0]);
    //     return 0;
    // }
    // else
    //     nvs[0].value = argv[1];
    //fcgi_connect(&sockfd);
    //sleep(10);

    GOOGLE_PROTOBUF_VERIFY_VERSION;
    fcgi::Record rec;
    record::BeginRequest req;
    record::Params param;
    record::Stdin sinp;

    rec.set_version(1);
    rec.set_type(1);
    rec.set_request_id(1);
    rec.set_reserved(0);
    rec.set_contentlength(40);
    rec.set_paddinglength(0);
    rec.set_contentdata("");
    rec.set_paddingdata("");

    fstream output("./argv", ios::out | ios::trunc | ios::binary);
    req.set_reserved1("adadsad");
    req.set_role(RESPONDER);
    req.set_flags(0);

    MyPageContent *header = param.add_paramvalues();
    header->set_key("DocumentRoot");
    header->set_value("/var/www/html/");
    MyPageContent *header1 = param.add_paramvalues();
    header1->set_key("SCRIPT_FILE");
    header1->set_value("/var/www/html/phpInfo.php");
    MyPageContent *header2 = param.add_paramvalues();
    header2->set_key("REQUEST_METHOD");
    header2->set_value("GET");

    int size1 = rec.ByteSize();
    void *buffer = malloc(size1);
    rec.SerializeToArray(buffer, size1);

    cout << "Output:: " << string((char *)buffer, size1) << endl;

    // int size = req.ByteSize();
    // void *buffer = malloc(size);
    // req.SerializeToArray(buffer, size);
    //string s;
    // google::protobuf::TextFormat::PrintToString(req, &s);
    //cout << "Output:: " << string((char *)buffer, size) << endl;

    if (!req.SerializeToOstream(&output))
    {
        cerr << "Failed to write address book." << endl;
        return -1;
    }
    //}

    //simple_session_1(sockfd);
    //close(sockfd);
    return 0;
}
