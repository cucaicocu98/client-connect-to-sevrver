#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS_
#pragma comment(lib, "ws2_32.lib")



int main(int argc, char* argv[]) {
    #pragma warning(disable : 4996)
    //  if(argc != 3){
    //  	printf("sai so luong tham so");
    //  	return 1;
    //  }
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    system("pause");

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR) {
        printf(" connect() failed");
        return 1;
    }
    char buf[256];
    ret = recv(client, buf, sizeof(buf), 0);
    if (ret <= 0) {
        printf(" recv() failed");
        return 1;
    }
    buf[ret] = 0;
    printf("Received: %\n", buf);

    while (1)
    {
        printf("Enter a string: ");
        gets_s(buf);

        if (strcmp(buf, "exit") == 0)
        {
            break;
        }

        else {
            send(client, buf, strlen(buf), 0);
        }

    }

    closesocket(client);
    WSACleanup();

}