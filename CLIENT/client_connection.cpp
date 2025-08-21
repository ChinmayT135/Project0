#include"headers.h"

void StoreNum::send_buffer_to_server(const char* buffer, bool keepReceiving)
{
    	client = socket(AF_INET, SOCK_STREAM, 0);

    	if(client < 0){
        	std::cerr<<"ERROR: failed connecting to server...\n";
        	return ;
    	}

    	server_addr.sin_family = AF_INET;
    	server_addr.sin_port = htons(port_no);
    	inet_pton(AF_INET, ip, &server_addr.sin_addr);

    	if(connect(client,(struct sockaddr *)&server_addr,sizeof(server_addr)) == 0)
        	std::cout<<"\nConnection established...\n";
    	else{
        	std::cerr<<"ERROR: Failed to establish connection !\n";
		return ;
	}

	send(client,buffer,strlen(buffer),0);
	if(keepReceiving)
	{
		do
		{
			recv(client,output_buf,MAXBUFLEN,0);
			if(strlen(output_buf)>1)
				std::cout<<output_buf<<std::endl;
		}while(output_buf[0] != '0');
	}
	else
	{
		recv(client,output_buf,MAXBUFLEN,0);
		std::cout<<output_buf<<std::endl;
	}

	close(client);
	return ;
}


