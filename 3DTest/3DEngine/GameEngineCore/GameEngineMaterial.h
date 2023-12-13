#pragma once
#include "GameEngineResources.h"

// ������ ������
// ������ ��� ��� �� ������ ������ ��� ĥ������ ���� ���ҽ��� ���� ���� ���õ� ���ҽ��� ��� ��������
// ��Ƽ���� �̶�� �մϴ�.

// ���� : 
class GameEngineMaterial : public GameEngineResources<GameEngineMaterial>
{
public:
	// constrcuter destructer
	GameEngineMaterial();
	~GameEngineMaterial();

	// delete Function
	GameEngineMaterial(const GameEngineMaterial& _Other) = delete;
	GameEngineMaterial(GameEngineMaterial&& _Other) noexcept = delete;
	GameEngineMaterial& operator=(const GameEngineMaterial& _Other) = delete;
	GameEngineMaterial& operator=(GameEngineMaterial&& _Other) noexcept = delete;

	static std::shared_ptr<class GameEngineMaterial> Create(std::string_view _Name)
	{
		std::shared_ptr<class GameEngineMaterial> NewRes = GameEngineResources::CreateRes(_Name);
		return NewRes;
	}

	void VertexShader();
	void GeometryShader();
	void Rasterizer();
	void PixelShader();
	void Blend();
	void DepthStencil();


	void SetVertexShader(std::string_view _Value);
	void SetGeometryShader(std::string_view _Value);
	void SetRasterizer(std::string_view _Value);
	void SetPixelShader(std::string_view _Value);
	void SetBlendState(std::string_view _Value);
	void SetDepthState(std::string_view _Value);

	std::shared_ptr<class GameEngineVertexShader> GetVertexShader()
	{
		return VertexShaderPtr;
	}

	std::shared_ptr<class GameEngineGeometryShader> GetGeometryShader()
	{
		return GeometryShaderPtr;
	}

	std::shared_ptr<class GameEnginePixelShader> GetPixelShader()
	{
		return PixelShaderPtr;
	}

	void GeometryShaderReset();


protected:

private:
	std::shared_ptr<class GameEngineVertexShader> VertexShaderPtr;
	std::shared_ptr<class GameEngineGeometryShader> GeometryShaderPtr;
	std::shared_ptr<class GameEngineRasterizer> RasterizerPtr;
	std::shared_ptr<class GameEnginePixelShader> PixelShaderPtr;
	std::shared_ptr<class GameEngineBlend> BlendStatePtr;
	std::shared_ptr<class GameEngineDepthStencil> DepthStencilPtr;
};
