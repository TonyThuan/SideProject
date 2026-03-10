#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <ctime>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>

int main()
{
    int listenFd = -1;
    int connectFd = -1;
    struct sockaddr_in serverAddr = {};
    char sendBuffer[1024] = {0,};
    time_t ticks;

    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(5000);

    bind(listenFd, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(listenFd, 10);

    while(1)
    {
	    connectFd = accept(listenFd, (sockaddr*)NULL, NULL);
	    ticks = time(NULL);
	    sprintf(sendBuffer, "Server reply %s", ctime(&ticks));
	    write(connectFd, sendBuffer, strlen(sendBuffer));
	    close(connectFd);
    }
    close(listenFd);

    return 0;
}
