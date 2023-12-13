#pragma once
#include "GameEngineShaderResHelper.h"
#include "GameEngineFont.h"
// ���� :
// �������� �ּҴ���
// �̳༮�� ������ �������� �ȴ�.
// ���̻� ��� ��������.
//
//class GameEngineRenderUnitBase
//{
//public:
//	virtual void ResSetting() {}
//	virtual void Draw() {}
//};

enum class RenderMode
{
	Indexed,
	Instancing,
};

class GameEngineRenderUnit final : public GameEngineObjectBase, std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
	// constrcuter destructer
	GameEngineRenderUnit();
	~GameEngineRenderUnit();

	void SetText(const std::string& _Font, const std::string& _Text, float _Scale = 20.0f, float4 Color = float4::RED, FW1_TEXT_FLAG Flag = FW1_LEFT);
	void ChangeText(std::string_view _Text);
	void ChangeFontScale(float _Size);
	void SetTextColor(const float4& _Color = float4::RED);
	void SetTextAlpha(float _AlphaValue = 0.0f);

	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);

	void SetMesh(std::shared_ptr<class GameEngineMesh> _Mesh);
	void SetMaterial(std::shared_ptr<class GameEngineMaterial> _Material);

	void ResSetting();
	void ResReset();
	void Draw();

	void Render();

	void SetParentRenderer(class GameEngineRenderer* _Renderer)
	{
		ParentRenderer = _Renderer;
	}

	class GameEngineRenderer* GetParentRenderer()
	{
		return ParentRenderer;
	}

	GameEngineShaderResHelper ShaderResHelper;

	inline void SetRenderMode(RenderMode _Mode)
	{
		Mode = _Mode;
	}

	inline void SetInstancingCount(int _Count)
	{
		InstancingCount = _Count;
	}

private:
	class GameEngineRenderer* ParentRenderer = nullptr;

	std::shared_ptr<class GameEngineFont> Font = nullptr;
	std::string FontText;
	float FontScale = 20.0f;
	float4 FontColor = float4::RED;
	FW1_TEXT_FLAG FontFlag;

	RenderMode Mode = RenderMode::Indexed;

	int InstancingCount = 0;


	// ����ȭ ����� �ɼ� �ִ�.
	// �̰� ��Ե� ������ ����� ã�°� �´�.
	std::shared_ptr<class GameEngineInputLayOut> LayOut = nullptr;


	std::shared_ptr<class GameEngineMesh> Mesh = nullptr;
	std::shared_ptr<class GameEngineMaterial> Material = nullptr;
};
