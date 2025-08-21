#include"server_headers.h"

bool startServer(bool print_error_on_console){

	int server_socket;
	int port_no = 1500;
	
	struct sockaddr_in server_addr,client_addr;
	socklen_t size;
	
	// setting up the socket for incoming request
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(server_socket < 0){
		if(print_error_on_console)
			std::cerr<<"ERROR establishing connection...\n";
		exit(1);
	}
	
	if(print_error_on_console)
		std::cout<<"Server connection established...\n";

	bzero((char*)&server_addr, sizeof(server_addr));	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(port_no);

	// binding the server_socket
	if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
		if(print_error_on_console)
			std::cerr<<"ERROR binding socket...\n";
		exit(1);
	}

	size = sizeof(server_addr);
	if(print_error_on_console)
		std::cout << " Waiting for client connections...\n";

	// listening to incoming request
	int listen_status = listen(server_socket,MAX_CLIENTS);
	if(listen_status < 0){
		 if(print_error_on_console)
			std::cerr<<"ERROR while listening...\n";
		exit(1);
	}
	
	StoreNum ob;
	std::vector<std::thread> threads;
	while(true){
		int client = accept(server_socket, (struct sockaddr*)&client_addr, &size);
		if(client<0){
			if(print_error_on_console)
				std::cerr<<"ERROR accepting the client...\n";
			continue;
		}

		
		char buffer[MAXBUFLEN] = {0};
		recv(client,buffer,MAXBUFLEN,0);
		threads.emplace_back(&StoreNum::processBuffer, &ob, client, buffer);
		threads.back().detach();
	}
	
	close(server_socket);
	return 0;
}

int main(int argc, char* argv[]){

	int start_daemon = 0;
	if(argc>1)
	{
		if(strcmp(argv[1],"run-daemon") == 0)
			start_daemon = 1;
		else
		{
			std::cerr<<"ERROR : unknown argument\n";
			return 0;
		}
	}

	if(start_daemon){
		pid_t pid;

		pid = fork();

		if(pid<0)
			exit(EXIT_FAILURE);

		if(pid>0)
			exit(EXIT_SUCCESS);

		if(setsid() < 0)
			exit(EXIT_FAILURE);

		pid = fork();
		if(pid<0)
			exit(EXIT_FAILURE);

		if(pid>0){
			std::cout<<"Server initiated ... => "<<pid<<" \n";
			exit(EXIT_SUCCESS);
		}

		umask(077);
		chdir("/");

		startServer(false);
		return 0;
	}

	startServer(true);
	return 0;
}
