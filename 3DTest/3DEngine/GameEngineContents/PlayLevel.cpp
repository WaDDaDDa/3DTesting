#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "PlayMap.h"
#include "Monster.h"
#include "TileMap.h"
#include "MainUIActor.h"
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/FadePostEffect.h>
#include "PlayerEffect.h"
#include "OldFilm.h"
#include <GameEngineCore/BlurPostEffect.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Start()
{
	GameEngineInput::AddInputObject(this);

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({0, 0, 0, 1});

	CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	if (nullptr != CoreWindow)
	{
		CoreWindow->AddDebugRenderTarget(0, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -1000.0f});
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		std::shared_ptr<Player> Object = CreateActor<Player>(0, "Player");
		PlayerObject = Object;
	}
}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F7, this))
	{
		CoreWindow->OnOffSwitch();
	}
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}
