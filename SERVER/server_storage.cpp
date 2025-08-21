#include"server_headers.h"

void StoreNum::processBuffer(int client, char* buffer)
{
	parseBufferAndSetValues(buffer);
	switch(operation)
	{
		case 1:
			insertNumber(client);
			break;
		case 2:
			deleteNumber(client);
			break;
		case 3:
			printAllNumbers(client);
			break;
		case 4:
			deleteAllNumbers(client);
			break;
	}
	close(client);
}

void StoreNum::insertNumber(int client)
{
	std::string output = "";

	if(storage.find(num) != storage.end())
	{
		output = "Entry already exists => ";
	}
	else
	{
		mtx.lock();
		storage[num] = epochTime;
		mtx.unlock();

		output = "Entry Inserted => ";
	}

	output = output + "Number: " + std::to_string(num) + " Time of insertion: " + epochToStringConversion(storage[num]); 
	send(client,output.c_str(),MAXBUFLEN,0);

	return ;
}

void StoreNum::deleteNumber(int client)
{
	std::string output = "";

	if(storage.find(num) == storage.end())
	{
		output = "Entered number does not exists in storage";
	}
	else
	{
		mtx.lock();
		std::string epochTimeOfNum = epochToStringConversion(storage[num]);
		storage.erase(num);
		mtx.unlock();

		output = "The number is delete from the storage successfully => Number: "+ std::to_string(num) + " Time of insertion: " + epochTimeOfNum;
	}

	send(client,output.c_str(),MAXBUFLEN,0);

	return ; 
}

void StoreNum::printAllNumbers(int client)
{
	if(storage.empty())
	{
		std::string output = "No entries found in the storage";
		send(client,output.c_str(),MAXBUFLEN,0);
	}
	else
	{
		mtx.lock();
		std::vector<std::pair<unsigned long long, std::string>> sortingVector(storage.begin(),storage.end());
		mtx.unlock();

		std::sort(sortingVector.begin(),sortingVector.end(),[](std::pair<unsigned long long,std::string>& value1, std::pair<unsigned long long,std::string>& value2){return value1.first<value2.first;});

		for(std::pair<unsigned long long, std::string>& iterator : sortingVector)
		{
			std::string output = "Entry => Number: "+ std::to_string(iterator.first) + " Time of insertion: " + epochToStringConversion(iterator.second);
	
			send(client,output.c_str(),MAXBUFLEN,0);
		}
	}
	std::string end = "0";
	send(client,end.c_str(),MAXBUFLEN,0);
}

void StoreNum::deleteAllNumbers(int client)
{
	std::string output = "";

	if(storage.empty())
	{
		output = "Storage is already empty";
	}
	else
	{
		mtx.lock();
		storage.clear();
		mtx.unlock();

		output = "Storage cleard successfully";
	}

	send(client,output.c_str(),MAXBUFLEN,0);

	return ;
}

void StoreNum::parseBufferAndSetValues(char* buffer)
{
	std::string bufferToParse(buffer);
	std::stringstream bufferStream(bufferToParse);
	std::string token;
	int count = 1;

	while(std::getline(bufferStream, token, ':'))
	{
		switch(count)
		{
			case 1:
				operation = std::stoi(token);
				break;
			case 2:
				num = std::stoull(token);
				break;
			case 3:
				epochTime = token;
				break;

		}
		count++;
	}
	return ;
}

std::string StoreNum::epochToStringConversion(std::string epochTimeForConversion)
{
	std::time_t insertTime = static_cast<std::time_t>(std::stoll(epochTimeForConversion));
	std::tm* readableTime = std::localtime(&insertTime);

	char  humanReadableFormat[100];
	std::strftime(humanReadableFormat, sizeof(humanReadableFormat), "%Y-%m-%d %H:%M:%S", readableTime);

	return std::string(humanReadableFormat);
}
