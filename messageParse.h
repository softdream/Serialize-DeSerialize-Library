#ifndef __MESSAGE_PARSE_H_
#define __MESSAGE_PARSE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>

namespace serialize{

class Serialize
{
public:
	Serialize();
	~Serialize();

	void setReadPath( const std::string &path );

//private:
	bool read();

private:
	std::string readPath;	

	std::ifstream infile;
	std::ofstream outfile;
};

Serialize::Serialize()
{


}

Serialize::~Serialize()
{


}

void Serialize::setReadPath( const std::string &path )
{
	readPath = path;
}

bool Serialize::read()
{
	infile.open( readPath, std::ios::in );
	if( !infile.is_open() ){
		std::cerr<<"Message File is Not Opened ..."<<std::endl;
		return false;
	}

	std::string temp;
	while( std::getline( infile, temp ) ){
		std::cout<<"temp:  "<<temp<<std::endl;
	}

	infile.close();

	return true;
}

}


#endif
