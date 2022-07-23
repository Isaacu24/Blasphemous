#include "PreCompile.h"
#include "GameEngineMetaParser.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <iostream>

#include "GameEngineMeta.h"


void GameEngineMetaParser::AutoCompile(const std::string& _Path)
{
	//const char* Second = "second:";
	//const char* Name = "name:";
	const char* Y = "";
	const char* Width = "";
	const char* Height = "height:";
	const char* Pivot = "pivot:";

	std::ifstream InputFile_(_Path);

	std::string Data;

	InputFile_.seekg(0, std::ios::end);
	size_t size = InputFile_.tellg();
	Data.resize(size);
	InputFile_.seekg(0, std::ios::beg);
	InputFile_.read(&Data[0], size);

	std::stringstream RealData{ Data };
	std::string Token_;

	GameEngineMeta* NewMetaData = new GameEngineMeta();

	while (std::getline(RealData, Token_, '\n')) //해당 파일 순회
	{
		InputFile_ >> Token_;
		std::string Temp = ltrim(Token_);

		//GameEngineDebug::OutPutString(Temp);

		if (true == Temp.starts_with("name: "))
		{
			size_t Size = Temp.length();

			Temp = Temp.substr(6);
			NewMetaData->SetName(Temp);
		}

		else if (true == Temp.starts_with("x: "))
		{
			size_t Size = Temp.length();

			Temp = Temp.substr(3);
			NewMetaData->SetX(Temp);
		}

		else if (true == Temp.starts_with("y: "))
		{
			size_t Size = Temp.length();

			Temp = Temp.substr(3);
			NewMetaData->SetY(Temp);
		}

		else if (true == Temp.starts_with("width: "))
		{
			size_t Size = Temp.length();

			Temp = Temp.substr(7);
			NewMetaData->SetWidth(Temp);
		}

		else if (true == Temp.starts_with("height: "))
		{
			size_t Size = Temp.length();

			Temp = Temp.substr(8);
			NewMetaData->SetHeight(Temp);
		}

		else if (true == Temp.starts_with("pivot: "))
		{
			size_t Size = Temp.length();
			Temp = Temp.substr(11); //0.12345, y: 0.123}

			std::string YStr = Temp; //0.12345, y: 0.123}

			size_t nPos = Temp.find(","); //X가 가질 위치

			Temp = Temp.substr(0, nPos); //0.12345

			size_t YPos = YStr.find("y"); //Y의 위치

			YStr = YStr.substr(YPos + 2, YStr.length()); //0.123}

			YStr = YStr.substr(0, YStr.length() - 1); //0.123

			NewMetaData->SetPivotX(Temp);
			NewMetaData->SetPivotY(YStr);
		}
	}

	NewMetaData;

	int aa = 0;
}