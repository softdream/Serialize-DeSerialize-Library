#ifndef __MESSAGE_PARSE_H_
#define __MESSAGE_PARSE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

namespace serialize{

class Serialize
{

	struct ElementInfo {
		int type;
		int length;
		std::string name;
	};
	typedef struct ElementInfo ElementInfo; 

public:
	Serialize();
	~Serialize();

	void setReadPath( const std::string &path );

//private:
	bool read();
	void elementsPrintTest() const;
	
private:
	bool findDataElement( const std::string &temp, const int position, const int typeLength );

private:
	std::string readPath;	

	std::ifstream infile;
	std::ofstream outfile;

	std::vector<std::string> elementsVec;


	std::vector<ElementInfo> elementsInfoVec;
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

void Serialize::elementsPrintTest() const
{
	if( !elementsVec.empty() ){
		std::cout<<"---------- Messages Number ---------"<<std::endl;
		for( auto it : elementsVec ){
			std::cout<<it<<std::endl;
		}
		std::cout<<"------- End of Message Number ------"<<std::endl;
	}
}

bool Serialize::findDataElement( const std::string &temp, const int position, const int typeLength ) 
{
	int semicolon = temp.find(";");
        if( semicolon != -1 ){
        	std::string data = temp.substr( position + typeLength, semicolon - position - typeLength );
                std::cout<<"data: "<<data<<std::endl;

                ElementInfo eI;
                eI.type = 3;
                eI.length = -1;
                eI.name = data;

                elementsInfoVec.push_back( eI );
        }

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

		//------------- find the data name --------------//
		int keyWord = temp.find( "message" );
		if( keyWord != -1 ){
			std::cout<<"KeyWord Position: "<<keyWord<<std::endl;

			std::string element;
			int brace = temp.find( "{" );
			if( brace == -1 ){
				element = temp.substr( keyWord + 7 );
			}
			else {
				element = temp.substr( keyWord + 7, brace - keyWord - 7 );
			}
			std::cout<<"element: "<<element<<std::endl;
			elementsVec.push_back( element );
		}	
		
		//------------ find the data type and it's name -------------//
		int typeInt8 = temp.find( "int8 " );
		if( typeInt8 != -1 ){
			
		}

		int typeInt16 = temp.find( "int16 " );
		if( typeInt16 != -1 ){

		}
	
		int typeInt32 = temp.find( "int32 " );
		if( typeInt32 != -1 ){
			/*int semicolon = temp.find(";");
			if( semicolon != -1 ){
				std::string data = temp.substr( typeInt32 + 6, semicolon - typeInt32 - 6 );
				std::cout<<"data: "<<data<<std::endl;

				ElementInfo eI;
				eI.type = 3;
				eI.length = -1;
				eI.name = data;
	
				elementsInfoVec.push_back( eI );
			}*/
			findDataElement( temp, typeInt32, 6 );
		}
	
		int typeInt64 = temp.find( "int64 " );	
		int typeFloat32 = temp.find( "float32 " );
		int typeFloat64 = temp.find( "float64 " );
	}

	infile.close();

	return true;
}

}


#endif
