#include"headers.h"

int main(){
	

	std::cout<<"WELCOME TO PROJECT0\nA simple project to save all your favorite numbers at one place!\n";
	int input = 0;
	StoreNum ob;

	do{

		std::cout<<"\nPlease select from the given options \n";
		std::cout<<"1) Insert a number\n";
		std::cout<<"2) Delete a number\n";
		std::cout<<"3) Print all numbers\n";
		std::cout<<"4) Delete all numbers\n";
		std::cout<<"5) Exit\n";

		std::cin>>input;
		if(std::cin.fail())
		{
			std::cin.clear();
            		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            		std::cerr << "ERROR: invalid input type\n";
            		input = 0;
            		continue;
		}

		switch(input){
			case 1:
			    {
				std::cout<<"Please enter a number(positive integer) you want to insert: ";
				long long numToInsert = 0;
				std::cin>>numToInsert;
				if(std::cin.fail())
				{
					std::cin.clear();
            				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            				std::cerr << "ERROR: invalid input type\n";
            				input = 0;
            				break;
				}
				if(numToInsert < 1){
					std::cerr<<"ERROR : invalid input, not a postive integer\n";
					input = 0;
					break;
				}
				ob.insertNum(static_cast<unsigned long long>(numToInsert));
				break;
			    }
			case 2:
			    {
				std::cout<<"Please enter a number(positive integer) you want to delete: ";
				long long numToDelete = 0;
				std::cin>>numToDelete;
				if(std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cerr<<"ERROR : invalid input type\n";
					input = 0;
					break;
				}
				if(numToDelete < 1){
					std::cerr<<"ERROR : invalid input, not a postive integer\n";
					input = 0;
					break;
				}
				ob.deleteNum(static_cast<unsigned long long>(numToDelete));
				break;
			    }
			case 3:
				ob.printAllNum();
				break;
			case 4:
				ob.deleteAllNum();
				break;
			case 5:
				std::cout<<"Exiting the project\n";
				break;
			default:
				std::cout<<"Please enter a valid number\n";
				input = 0;
				break;
		}

	}while(input != 5);

	return 0;
}
