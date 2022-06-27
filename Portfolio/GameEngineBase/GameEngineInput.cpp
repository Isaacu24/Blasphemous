#include "PreCompile.h"
#include "GameEngineInput.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

#pragma comment(lib, "xinput.lib")

//////////////////////////////////////////////////////////////////

void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	if (true == KeyCheck())
	{
		if (true == Free_)
		{
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ = 0.0f;
			Time_ += _DeltaTime;
		}
		else if (true == Press_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
			Time_ += _DeltaTime;
		}
	}
	else
	{
		if (true == Press_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
			Time_ = 0.0f;
		}
		else if (true == Up_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	}
}

////////////////////////////////////////////////////////////////

GameEngineInput* GameEngineInput::Inst_ = new GameEngineInput();

GameEngineInput::GameEngineInput()
	: WheelValue(),
	CurWheelValue()
{
}

GameEngineInput::~GameEngineInput()
{
}


bool GameEngineInput::IsKey(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() != AllInputKey_.find(UpperKey))
	{
		return true;
	}

	return false;
}

void GameEngineInput::CreateKey(const std::string& _Name, int _Key)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() != AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� Ű�� �� ������� �߽��ϴ�.");
		return;
	}

	AllInputKey_.insert(std::make_pair(UpperKey, GameEngineKey()));
	AllInputKey_[UpperKey].Key_ = _Key;
	AllInputKey_[UpperKey].Reset();
}

void GameEngineInput::Reset() 
{
	CurWheelValue = 0;
	CurWheelValue = WheelValue;
	WheelValue = 0;

	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();

	for (; KeyUpdateStart != KeyUpdateEnd; ++KeyUpdateStart)
	{
		GameEngineKey& CurrentKey = KeyUpdateStart->second;

		CurrentKey.Reset();
	}
}

void GameEngineInput::Update(float _DeltaTime)
{
	CurWheelValue = 0;
	CurWheelValue = WheelValue;
	WheelValue = 0;

	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();

	for (; KeyUpdateStart != KeyUpdateEnd; ++KeyUpdateStart)
	{
		GameEngineKey& CurrentKey = KeyUpdateStart->second;

		CurrentKey.Update(_DeltaTime);
	}

	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE)); //��Ʈ�ѷ� ���� �ʱ�ȭ
		dwResult = XInputGetState(i, &state); //��Ʈ�ѷ� ���� ������

		if (dwResult == ERROR_SUCCESS)
		{
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) 
			{
				int a = 0;
			}

			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				int a = 0;
			}

			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				int a = 0;
			}

			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				int a = 0;
			}

			Sleep(30); //Cpu ������ 100% ����
			dwResult = XInputGetState(0, &state); //���� ���� ������
		}

		else
		{
			// Controller is not connected
		}
	}
}

float GameEngineInput::GetTime(const std::string& _Name) 
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}

	return AllInputKey_[UpperKey].Time_;
}

bool GameEngineInput::IsDown(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}

	return AllInputKey_[UpperKey].Down_;
}

bool GameEngineInput::IsUp(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[UpperKey].Up_;
}

bool GameEngineInput::IsPress(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[UpperKey].Press_;
}

bool GameEngineInput::IsFree(const std::string& _Name)
{
	std::string UpperKey = GameEngineString::ToUpperReturn(_Name);

	if (AllInputKey_.end() == AllInputKey_.find(UpperKey))
	{
		MsgBoxAssert("�������� �ʴ� Ű �Դϴ�.");
		return false;
	}
	return AllInputKey_[UpperKey].Free_;
}
