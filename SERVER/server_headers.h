#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<syslog.h>
#include<signal.h>
#include<unordered_map>
#include<string>
#include<sstream>
#include<cstring>
#include<thread>
#include<mutex>
#include<ctime>
#include<vector>
#include<algorithm>

#define MAXBUFLEN 1024
#define MAX_CLIENTS 400


class StoreNum{
	private:
		std::unordered_map<unsigned long long, std::string> storage;

		int operation = 0;
		unsigned long long num;
		std::string epochTime;
		std::mutex mtx;

		void parseBufferAndSetValues(char* buffer);
		std::string epochToStringConversion(std::string epochTimeForConversion);
		void insertNumber(int client);
		void deleteNumber(int client);
		void printAllNumbers(int client);
		void deleteAllNumbers(int client);
	public:
		void processBuffer(int client, char* buffer);
};

