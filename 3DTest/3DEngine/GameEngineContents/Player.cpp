#include "PreCompile.h"
#include "Player.h"
#include "PlayMap.h"
#include "Monster.h"
#include "ContentsEnum.h"
#include "ContentsSpriteRenderer.h"
#include "GameEngineCore/GameEngineFBXRenderer.h"

Player::Player() 
{	
}

Player::~Player() 
{
}

void Player::Start()
{
	{
		FBXRenderer = CreateComponent<GameEngineFBXRenderer>();
		FBXRenderer->SetFBXMesh("AnimMan.FBX", "FBXColor");
		FBXRenderer->RenderBaseInfoValue.BaseColor = float4::RED;
	}

	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
		Col->SetCollisionType(ColType::SPHERE2D);
		Col->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });
	}

	GameEngineInput::AddInputObject(this);

	{
		CreateStateParameter NewPara;

		// 한번만 실행되는 겁니다.
		NewPara.Init = [=](class GameEngineState* _Parent)
			{
				// MainSpriteRenderer->ChangeAnimation("Idle");
			};


		NewPara.Start = [=](class GameEngineState* _Parent) 
			{
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (3.0f <= _Parent->GetStateTime())
				{
					_Parent->ChangeState(PlayerState::Smoke);
					return;
				}

				if (GameEngineInput::IsPress('A', this))
				{
					_Parent->ChangeState(PlayerState::Move);
				}


				if (GameEngineInput::IsPress('D', this))
				{
					_Parent->ChangeState(PlayerState::Move);
				}
			};

		PlayerState.CreateState(PlayerState::Idle, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (GameEngineInput::IsPress('A', this))
				{
					_Parent->ChangeState(PlayerState::Move);
				}


				if (GameEngineInput::IsPress('D', this))
				{
					_Parent->ChangeState(PlayerState::Move);
				}
			};

		PlayerState.CreateState(PlayerState::Smoke, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
			};

		NewPara.Stay = [=](float _Delta, class GameEngineState* _Parent)
			{
				if (GameEngineInput::IsFree('A', this) && GameEngineInput::IsFree('D', this))
				{			
					_Parent->ChangeState(PlayerState::Idle);
					return;
				}


				if (GameEngineInput::IsPress('A', this))
				{
					Transform.AddLocalPosition(float4::LEFT * _Delta * MoveSpeed);
				}


				if (GameEngineInput::IsPress('D', this))
				{
					Transform.AddLocalPosition(float4::RIGHT * _Delta * MoveSpeed);
				}
			};


		PlayerState.CreateState(PlayerState::Move, NewPara);
	}

	PlayerState.ChangeState(PlayerState::Idle);

}

void Player::Update(float _Delta)
{
	PlayerState.Update(_Delta);
}