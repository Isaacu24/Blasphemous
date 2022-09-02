#pragma once

class SpawnerBase
{
public:
	SpawnerBase();
	~SpawnerBase();

	SpawnerBase(const SpawnerBase& _Other) = delete;
	SpawnerBase(SpawnerBase&& _Other) noexcept = delete;
	SpawnerBase& operator=(const SpawnerBase& _Other) = delete;
	SpawnerBase& operator=(SpawnerBase&& _Other) noexcept = delete;

	inline bool GetSpawnerEnd() 
	{ 
		return SpawnerEnd_;
	}

	
	inline void SetSpawnerEnd(bool _Value) { SpawnerEnd_ = _Value; }

protected:
    bool SpawnerEnd_;

private:

};

