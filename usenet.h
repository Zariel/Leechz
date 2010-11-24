
class Usenet
{
private:
    int connected;
    struct sockaddr_in *addr; /* ipv4, maybe ipv6 later */
    int sockfd;

public:
    Usenet(char *host, int port);
    ~Usenet();
};
