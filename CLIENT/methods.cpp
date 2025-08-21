#include"headers.h"
void StoreNum::insertNum(unsigned long long numToInsert)
{
	std::string buffer = "";
	long long time_stamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	buffer = "1:"+std::to_string(numToInsert)+":"+std::to_string(time_stamp);
	
	send_buffer_to_server(buffer.c_str(),false);
	return ;
}

void StoreNum::deleteNum(unsigned long long numToDelete)
{
	std::string buffer = "";
	buffer = "2:"+std::to_string(numToDelete)+":NA";
	
	send_buffer_to_server(buffer.c_str(),false);
	return ;
}

void StoreNum::printAllNum()
{
	std::string buffer = "";
	buffer = "3:0:NA";

	send_buffer_to_server(buffer.c_str(),true);
	return ;
}

void StoreNum::deleteAllNum()
{
	std::string buffer = "";
	buffer = "4:0:NA";

	send_buffer_to_server(buffer.c_str(),false);
	return ;
}
