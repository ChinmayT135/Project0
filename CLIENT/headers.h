#include<iostream>
#include<string>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<fstream>
#include<chrono>
#include<thread>

#define KEY 'C'
#define MAXBUFLEN 1024

class StoreNum{
	private:
		int client;
        	int port_no = 1500;
        	const char* ip = "127.0.0.1";
        	char output_buf[MAXBUFLEN] = {0};
        	struct sockaddr_in server_addr;

		void send_buffer_to_server(const char* buffer, bool keepReceiving);
	public:
		void insertNum(unsigned long long numToInsert);
		void deleteNum(unsigned long long numToDelete);
		void printAllNum();
		void deleteAllNum();	
};

