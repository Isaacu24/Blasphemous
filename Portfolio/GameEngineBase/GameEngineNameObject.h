#pragma once
#include <string>

// Ό³Έν :
class GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineNameObject();
	virtual ~GameEngineNameObject();

	inline void SetName(const std::string& _Name)
	{
		ObjectName_ = _Name;
	}

	std::string GetNameCopy() const
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

