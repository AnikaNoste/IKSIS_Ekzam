#include "stdafx.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <algorithm>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) 

using namespace std;

void show(char* reply)
{
	std::cout << reply << endl; //просто выводит параметр на экран
}

int main() {
	//------------------------------------------------------------

	HANDLE hIcmpFile;															//объявление необходимых переменных
	unsigned long ipaddr = INADDR_NONE;
	DWORD dwRetVal = 0;
	char SendData[32] = "Data Buffer";
	LPVOID ReplyBuffer = NULL;
	DWORD ReplySize = 0;
	
	//------------------------------------------------------------

	ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
	ReplyBuffer = (VOID*)malloc(ReplySize);

	const char* pointerToAddres;													//указатель на текущий ip-шник

	list<char*> replyes = {};

	/*for (int i = 0; i <= 255; i++) {
		for (int j = 0; j <= 255; j++) {*/

			//------------------------------------------------------------

	while (true) {

		cout << "Adress: ";

		char layout[16];
		cin >> layout;

		pointerToAddres = layout;

		cout << "Cycle: ";
		int cycle;
		cin >> cycle;

		for (int i = 0; i < cycle; i++) {

			cout << pointerToAddres << "\n";

			ipaddr = inet_addr(pointerToAddres);				//переводим адрес в нужный формат

			hIcmpFile = IcmpCreateFile();						//открываем соединение

			dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData), NULL, ReplyBuffer, ReplySize, 100);  //посылаем запрос

			if (dwRetVal != 0) {
				PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;  //записываем ответ
				struct in_addr ReplyAddr;
				ReplyAddr.S_un.S_addr = pEchoReply->Address;

				printf("Addres: %s ", inet_ntoa(ReplyAddr));						//выводим
				printf("Ping = %ld milliseconds\n", pEchoReply->RoundTripTime);

				replyes.push_back(inet_ntoa(ReplyAddr));
			}
			//------------------------------------------------------------
			IcmpCloseHandle(hIcmpFile);							//закрываем конект
		}

		//----------------------------------------------------------------

		
	}
			
		//}
		/*cout << "Найденные адреса" << endl;
		for_each(replyes.begin(), replyes.end(), show);*/
	//}

	system("pause");
	return 0;
}