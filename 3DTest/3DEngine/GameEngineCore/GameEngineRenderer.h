#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"
#include "GameEngineMesh.h"
#include "GameEngineMaterial.h"
#include "GameEngineRenderUnit.h"


struct RenderBaseInfo
{
	float4 ScreenSize;
	float4 BaseColor = float4::BLACK;
	int IsMask = 0;
	int BaseColorOnly = 0;
	int MaskMode = 0;
	int BaseTemp2 = 0;
	float4 RendererScreenPos;
	float4 RenderScreenScale;
	float4 MaskScreeneScale;
	float4 MaskPivot;
	float4 VertexUVPlus;
	float4 VertexUVMul = float4::ONE;
	float DeltaTime = 0.0f;
	float AccDeltaTime = 0.0f;
	int Target0 = 1;
	int Target1 = 0;
	int Target2 = 0;
	int Target3 = 0;
	int Target4 = 0;
	int Target5 = 0;
	int Target6 = 0;
	int Target7 = 0;
};

// ���� : GameEngineRenderer���� Order�� ������ �Ǵ� ������ �ǹ��մϴ�.
// �������� �������ִ� ������
// �ڵ带 ¥�ٺ��� �׳� ������ ����ü�� �̿��ؾ� �ϴ� ��찡 ��������.
// �������� ������Ʈ�ΰ� �����̴�.
// �׷��� �������� �ּҴ��� �������� ���� �߿��� ��Ҹ� ��Ƴ���
// ���� ����Ʈ�� ��ü�� �ǰ�
// �������ε� ����Ҽ� ���� ������ 
// ������ ������ �������̴�.
class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// �̰� ���� ���ٸ�
	// ī�޶��� ��쿡�� 
	// �̰� ������ ȣ��Ǿ� �մϴ�.
	// �ϳ��� �������� �������� �������� ī�޶� �ٶ󺼼� �ִ�.
	// ���� �Ȱܴٴϴ� ������ �ƴϴ�.
	void SetViewCameraSelect(int _Order);

	// ��� ī�޶󿡼� ���� ����

	// ���� ���ִ� ī�޶� �ٲٰڴٴ� 

	// ���ٶ󺸴� ��� ī�޶󿡼� ���� �����ϰ�
	// _Order ī�޶�� �̵��ϴ°�.
	// void SetChangeViewCameraAllClear(int _Order);

	void SetRenderOrder(int _Order);

	template <typename EnumType>
	void SetRenderOrder(EnumType _Order)
	{
		SetRenderOrder(static_cast<int>(_Order));
	}


	void SetCameraOrder(ECAMERAORDER _Order)
	{
		SetCameraOrder(static_cast<int>(_Order));
	}
	void SetCameraOrder(int _Order);

	// Create PushBack������ �ƴմϴ�.
	// 0�� ���� ����Ʈ�� ����ٰ� ġ�� 0��°�� ���� ����Ʈ�� ����� ���ϴ�.
	// 8���� �ϸ� vector�� Ȯ��ǰ� 8��°�� ���� ����Ʈ�� ����� �˴ϴ�.
	std::shared_ptr<GameEngineRenderUnit> CreateAndFindRenderUnit(int _Index = 0);

	void SetMesh(std::string_view _Name, int _Index = 0);
	void SetMaterial(std::string_view _Name, int _Index = 0);

	GameEngineShaderResHelper& GetShaderResHelper(int _Index = 0);

	RenderBaseInfo RenderBaseInfoValue;

	float4 GetScreenPosition();

	GameEngineCamera* GetCamera()
	{
		return Camera;
	}

protected:
	void Start();
	void Update(float _Delta) override;
	virtual void Render(class GameEngineCamera* _Camera, float _Delta);
	virtual void SetMaterialEvent(std::string_view _Name, int _Index = 0);

	//std::shared_ptr<class GameEngineInputLayOut> LayOut;
	//std::shared_ptr<class GameEngineMesh> Mesh;
	//std::shared_ptr<class GameEngineMaterial> Material;
	//GameEngineShaderResHelper ShaderResHelper;

	std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;


private:
	class GameEngineCamera* Camera = nullptr;
};
