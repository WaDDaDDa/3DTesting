#include "PreCompile.h"
#include "GameEngineMaterial.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRasterizer.h"
#include "GameEngineGeometryShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineBlend.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineRenderTarget.h"

GameEngineMaterial::GameEngineMaterial()
{
	RasterizerPtr = GameEngineRasterizer::Find("EngineRasterizer");
	BlendStatePtr = GameEngineBlend::Find("AlphaBlend");;
	DepthStencilPtr = GameEngineDepthStencil::Find("EngineDepth");;
}

GameEngineMaterial::~GameEngineMaterial()
{
}

void GameEngineMaterial::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgBoxAssert("�������� �ʴ� ���ؽ� ���̴��� �����Ϸ��� �߽��ϴ�.");
	}

	VertexShaderPtr->Setting();
}

void GameEngineMaterial::GeometryShader()
{
	if (nullptr == GeometryShaderPtr)
	{
		// ������Ʈ���� �ʼ��ܰ谡 �ƴϱ� ������ ���ϸ� �ϰڽ��ϴ�.
		return;
		// MsgBoxAssert("�������� �ʴ� ���ؽ� ���̴��� �����Ϸ��� �߽��ϴ�.");
	}

	GeometryShaderPtr->Setting();
}

void GameEngineMaterial::GeometryShaderReset()
{
	if (nullptr == GeometryShaderPtr)
	{
		return;
	}

	GeometryShaderPtr->Reset();
}

void GameEngineMaterial::Rasterizer()
{
	if (nullptr == RasterizerPtr)
	{
		MsgBoxAssert("�������� �ʴ� ������ �������� �����Ϸ��� �߽��ϴ�.");
	}

	RasterizerPtr->Setting();
}

void GameEngineMaterial::PixelShader()
{
	if (nullptr == PixelShaderPtr)
	{
		MsgBoxAssert("�������� �ʴ� ������ �������� �����Ϸ��� �߽��ϴ�.");
	}

	PixelShaderPtr->Setting();
}

void GameEngineMaterial::Blend()
{
	if (nullptr == BlendStatePtr)
	{
		MsgBoxAssert("�������� �ʴ� ������ �������� �����Ϸ��� �߽��ϴ�.");
	}

	BlendStatePtr->Setting();
}

void GameEngineMaterial::DepthStencil()
{
	if (false == GameEngineRenderTarget::IsDepth)
	{
		GameEngineCore::GetContext()->OMSetDepthStencilState(nullptr, 0);
		return;
	}

	if (nullptr == DepthStencilPtr)
	{
		MsgBoxAssert("�������� �ʴ� ���� üũ ������ �����Ϸ��� �߽��ϴ�.");
	}

	DepthStencilPtr->Setting();
}

void GameEngineMaterial::SetVertexShader(std::string_view _Value) 
{
	VertexShaderPtr = GameEngineVertexShader::Find(_Value);

	if (nullptr == VertexShaderPtr)
	{
		MsgBoxAssert("�������� �ʴ� ���ؽ� ���̴��� �����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineMaterial::SetGeometryShader(std::string_view _Value)
{
	GeometryShaderPtr = GameEngineGeometryShader::Find(_Value);

	if (nullptr == GeometryShaderPtr)
	{
		MsgBoxAssert("�������� �ʴ� ������Ʈ�����̴��� �����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineMaterial::SetRasterizer(std::string_view _Value) 
{
	RasterizerPtr = GameEngineRasterizer::Find(_Value);

	if (nullptr == RasterizerPtr)
	{
		MsgBoxAssert("�������� �ʴ� ������ �������� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineMaterial::SetPixelShader(std::string_view _Value) 
{
	PixelShaderPtr = GameEnginePixelShader::Find(_Value);

	if (nullptr == PixelShaderPtr)
	{
		MsgBoxAssert("�������� �ʴ� �ȼ����̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineMaterial::SetBlendState(std::string_view _Value) 
{
	BlendStatePtr = GameEngineBlend::Find(_Value);

	if (nullptr == BlendStatePtr)
	{
		MsgBoxAssert("�������� �ʴ� �����带 �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineMaterial::SetDepthState(std::string_view _Value)
{
	DepthStencilPtr = GameEngineDepthStencil::Find(_Value);

	if (nullptr == DepthStencilPtr)
	{
		MsgBoxAssert("�������� �ʴ� ���̹��� ������ ����Ϸ��� �߽��ϴ�.");
		return;
	}
}