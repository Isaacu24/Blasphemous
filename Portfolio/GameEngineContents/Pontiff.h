#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

enum class PontiffState
{
	Opening,
	OpenIdle,
	Closing,
	CloseIdle,
	Death
};

//�ι�° ��Ȳ
class Pontiff : public GameEngineActor, public BossMonster
{
public:
	Pontiff();
	~Pontiff();

	Pontiff(const Pontiff& _Other) = delete;
	Pontiff(Pontiff&& _Other) noexcept = delete;
	Pontiff& operator=(const Pontiff& _Other) = delete;
	Pontiff& operator=(Pontiff&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	class GameEngineTextureRenderer* Helmet_;
	class GameEngineTextureRenderer* Body_;

};


//�÷��� ������ Ŭ������ ������ ��. 
//�װ� �÷���������(Ȥ�� ��������. �ٵ� �Ƹ� ���� Ŭ������ ����� ���� ����.)�� �� ��. 
//��Ȳ�� ���� �ȴ�.