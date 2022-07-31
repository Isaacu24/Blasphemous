#pragma once
#include "PreCompile.h"

//������ �⺻���� Ŭ����
class GameEngineTextureRenderer;
class MonsterBase
{
public:
	MonsterBase();
	~MonsterBase();

	MonsterBase(const MonsterBase& _Other) = delete;
	MonsterBase(MonsterBase&& _Other) noexcept = delete;
	MonsterBase& operator=(const MonsterBase& _Other) = delete;
	MonsterBase& operator=(MonsterBase&& _Other) noexcept = delete;

	inline void SetHP(int _Value)
	{
		HP_ = _Value;
	}

	inline int GetHP()
	{
		return HP_;
	}

	inline void SetTear(int _Value)
	{
		Tear_ = _Value;
	}

	inline int GetTear()
	{
		return Tear_;
	}

	inline void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

	void SetGround(GameEngineTextureRenderer* _Ground);

	inline void ChangeMonsterState(const std::string& _State)
	{
		State_.ChangeState(_State);
	}

protected:
	GameEngineStateManager State_;

	GameEngineTextureRenderer* Renderer_;
	GameEngineTextureRenderer* ColMap_;
	class GravityComponent* Gravity_;

	int HP_;
	float Speed_;

	int Tear_; //�÷��̾�� ������ ����

	bool IsGround_;

	bool GroundCheck(int _X, int _Y);

	bool ObstacleCheck();

private:

};

