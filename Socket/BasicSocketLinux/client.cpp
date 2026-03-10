#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <ctime>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
    int sockFd = -1;
    sockaddr_in serverAddr = {};
    char revBuffer[1024] = { 0, };
    time_t ticks;

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(5000);

    if (connect(sockFd, (sockaddr*)&serverAddr, sizeof(serverAddr)) == 0)
    {
        read(sockFd, revBuffer, sizeof(revBuffer) - 1);
	cout << "Client receive: " << revBuffer;
        close(sockFd);
    } 

    return 0;
}
