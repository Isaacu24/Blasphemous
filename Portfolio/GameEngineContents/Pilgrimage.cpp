#include "Pilgrimage.h"
#include "PreCompile.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include "Penitent.h"
#include "Stage01.h"
#include <GameEngineBase/GameEngineWindow.h>

Pilgrimage::Pilgrimage() 
{

}

Pilgrimage::~Pilgrimage() 
{
}
void Pilgrimage::Start()
{
	//�������� �ʱ�ȭ(ī�޶�
	CreateActor<GameEngineCameraActor>();
	CreateActor<Penitent>(1);


}

void Pilgrimage::Update(float _DeltaTime)
{
}

void Pilgrimage::End()
{
}
