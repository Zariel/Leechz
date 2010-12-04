class Usenet
{
private:
    int connected;
    int sockfd;

    int _send(std::string data);

public:
    Usenet(char *host, int port, int ipv6 = 0);
    ~Usenet();
};
