#pragma once
#include <string>

class GameEngineNameObject
{
public:
	GameEngineNameObject();
	virtual ~GameEngineNameObject();

	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(GameEngineNameObject&& _Other) noexcept = delete;

	inline void SetName(const std::string& _Name) 
	{
		ObjectName_ = _Name;
	}

	std::string GetNameCopy()
	{
		return ObjectName_;
	}

	const std::string& GetNameConstRef()
	{
		return ObjectName_;
	}

	const char* GetNameConstPtr()
	{
		return ObjectName_.c_str();
	}


protected:

private:
	std::string ObjectName_;

};

