#include "PreCompile.h"
#include "GameEngineMetaParser.h"

#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

GameEngineMetaParser* GameEngineMetaParser::Inst_ = new GameEngineMetaParser();

GameEngineMetaParser::GameEngineMetaParser()
{
}

GameEngineMetaParser::~GameEngineMetaParser()
{
	std::map<std::string, std::vector<GameEngineMetaData*>>::iterator StartIter = MetaDatas_.begin();
	std::map<std::string, std::vector<GameEngineMetaData*>>::iterator EndIter = MetaDatas_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		std::vector<GameEngineMetaData*>::iterator DataStart = (*StartIter).second.begin();
		std::vector<GameEngineMetaData*>::iterator DataEnd = (*StartIter).second.end();

		for (; DataStart != DataEnd; ++DataStart)
		{
			if (nullptr != (*DataStart))
			{
				delete (*DataStart);
				(*DataStart) = nullptr;
			}
		}
	}

}

void GameEngineMetaParser::AutoCompile(const std::string& _Path)
{
	Reset();

	std::ifstream InputFile_(_Path);

	std::string Data;

	InputFile_.seekg(0, std::ios::end);
	size_t Size = InputFile_.tellg();
	Data.resize(Size);
	InputFile_.seekg(0, std::ios::beg);
	InputFile_.read(&Data[0], Size);

	std::stringstream RealData{ Data };

	std::string Token;

	std::string Str = _Path;
	size_t Pos = Str.rfind("\\");
	std::string FileName = Str.substr(Pos);
	FileName = FileName.substr(1);
	FileName = FileName.substr(0, FileName.size() - 5);

	while (std::getline(RealData, Token, '\n')) //해당 파일 순회
	{
		InputFile_ >> Token;
		std::string Temp = ltrim(Token);

		if (true == Temp.starts_with("name: "))
		{
			Temp = Temp.substr(6);
			NameVec_.push_back(Temp);
		}

		else if (true == Temp.starts_with("x: "))
		{
			Temp = Temp.substr(3);
			int X = std::stoi(Temp);
			XVec_.push_back(X);
		}

		else if (true == Temp.starts_with("y: "))
		{
			Temp = Temp.substr(3);
			int Y = std::stoi(Temp);
			YVec_.push_back(Y);
		}

		else if (true == Temp.starts_with("width: "))
		{
			Temp = Temp.substr(7);
			int Width = std::stoi(Temp);
			WidthVec_.push_back(Width);
		}

		else if (true == Temp.starts_with("height: "))
		{
			Temp = Temp.substr(8);
			int Height = std::stoi(Temp);
			HeightVec_.push_back(Height);
		}

		else if (true == Temp.starts_with("pivot: "))
		{
			Temp = Temp.substr(11); //0.12345, y: 0.123}

			std::string YStr = Temp; //0.12345, y: 0.123}

			size_t nPos = Temp.find(","); //X가 가질 위치

			Temp = Temp.substr(0, nPos); //0.12345

			size_t YPos = YStr.find("y"); //Y의 위치

			YStr = YStr.substr(YPos + 2, YStr.length()); //0.123}

			YStr = YStr.substr(0, YStr.length() - 1); //0.123

			float PivotX = std::stof(Temp);
			float PivotY = std::stof(YStr);
			PivotVec_.push_back({ PivotX , PivotY });
		}
	}


	for (size_t i = 0; i < NameVec_.size(); i++)
	{
		GameEngineMetaData* NewData = new GameEngineMetaData();

		NewData->SetName(NameVec_[i]);
		NewData->SetX(XVec_[i]);
		NewData->SetY(YVec_[i]);
		NewData->SetWidth(WidthVec_[i]);
		NewData->SetHeight(HeightVec_[i]);
		NewData->SetPivot(PivotVec_[i]);

		MetaVec_.push_back(NewData);
	}

	MetaDatas_.insert(std::make_pair(FileName, MetaVec_));
}

void GameEngineMetaParser::Reset()
{
	MetaVec_.clear();

	NameVec_.clear();
	XVec_.clear();
	YVec_.clear();
	WidthVec_.clear();
	HeightVec_.clear();
	PivotVec_.clear();

}

