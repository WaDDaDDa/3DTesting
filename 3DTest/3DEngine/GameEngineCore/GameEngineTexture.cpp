#include "PreCompile.h"
#include "GameEngineTexture.h"
#include "GameEngineCore.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Release\\DirectXTex.lib")
#endif

const GameEngineColor GameEngineColor::RED = { 255, 0, 0, 255 };
const GameEngineColor GameEngineColor::GREEN = { 0, 255, 0, 255 };
const GameEngineColor GameEngineColor::BLUE = { 0, 0, 255, 255 };
const GameEngineColor GameEngineColor::MAGENTA = { 255, 0, 255, 255 };
const GameEngineColor GameEngineColor::YELLOW = { 255, 255, 0, 255 };
const GameEngineColor GameEngineColor::AQUA = { 0, 255, 255, 255 };
const GameEngineColor GameEngineColor::BLACK = { 0, 0, 0, 255 };
const GameEngineColor GameEngineColor::WHITE = { 255, 255, 255, 255 };

GameEngineTexture::GameEngineTexture() 
{
}

GameEngineTexture::~GameEngineTexture() 
{
	if (nullptr != DSV)
	{
		DSV->Release();
		DSV = nullptr;
	}

	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}

	if (nullptr != RTV)
	{
		RTV->Release();
		RTV = nullptr;
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
	}
}


void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RTV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("��������� ���� �ؽ�ó�� ����Ÿ�ٺ並 �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// �̹����� �����Ҽ� �ִ� ������ '�����'

	HRESULT Result = GameEngineCore::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("����Ÿ�ٺ� ������ �����߽��ϴ�.");
		return;
	}

}

// ���̴� ���ÿ�
void GameEngineTexture::CreateShaderResourceView()
{
	if (nullptr != SRV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("��������� ���� �ؽ�ó�� ���̴� ���ҽ� �� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// �̹����� �����Ҽ� �ִ� ������ '�����'

	HRESULT Result = GameEngineCore::GetDevice()->CreateShaderResourceView(Texture2D, nullptr, &SRV);

	if (S_OK != Result)
	{
		MsgBoxAssert("���̴� ���ҽ� �� ������ �����߽��ϴ�.");
		return;
	}

}

// ������ ���ÿ�
void GameEngineTexture::CreateDepthStencilView()
{
	if (nullptr != DSV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("��������� ���� �ؽ�ó�� ���̴� ���ҽ� �� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// �̹����� �����Ҽ� �ִ� ������ '�����'

	HRESULT Result = GameEngineCore::GetDevice()->CreateDepthStencilView(Texture2D, nullptr, &DSV);

	if (S_OK != Result)
	{
		MsgBoxAssert("���̴� ���ҽ� �� ������ �����߽��ϴ�.");
		return;
	}
}

void GameEngineTexture::ResLoad(std::string_view _Path)
{
	// ���丮�� ��ʹ� 

	// png �� �ټ��� �̹����� �ε� ������ �Լ� 

	GameEnginePath NewPath = _Path;

	std::string Ext = GameEngineString::ToUpperReturn(NewPath.GetExtension());

	std::wstring wPath = GameEngineString::AnsiToUnicode(_Path);

	// �׷��� 
	if (Ext == ".DDS")
	{
		if (S_OK != DirectX::LoadFromDDSFile(wPath.c_str(), DirectX::DDS_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("�ؽ�ó �ε忡 �����߽��ϴ�." + std::string(_Path.data()));
		}
	}
	else if (Ext == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wPath.c_str(), DirectX::TGA_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("�ؽ�ó �ε忡 �����߽��ϴ�." + std::string(_Path.data()));
		}
		
	}
	else if(S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
	{
		MsgBoxAssert("�ؽ�ó �ε忡 �����߽��ϴ�." + std::string(_Path.data()));
	}

	// �ε��� ������ ���̴� ���� ������ �����°��� �������� �����ΰ��̴�
	// �̰͵� ���̺귯�� �Լ�
	if (S_OK != DirectX::CreateShaderResourceView
	(
		GameEngineCore::GetDevice(),
		Image.GetImages(),
		Image.GetImageCount(), // �̹����� ���������� �ִ�.
		Image.GetMetadata(),
		&SRV
	))
	{
		MsgBoxAssert("�ؽ�ó �ε忡 �����߽��ϴ�." + std::string(_Path.data()));
	}

	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height = static_cast<UINT>(Data.height);
}

void GameEngineTexture::VSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::PSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->PSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::CSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->CSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::VSReset(UINT _Slot)
{
	ID3D11ShaderResourceView* ResetRes = nullptr;
	GameEngineCore::GetContext()->VSSetShaderResources(_Slot, 1, &ResetRes);
}
void GameEngineTexture::PSReset(UINT _Slot)
{
	ID3D11ShaderResourceView* ResetRes = nullptr;
	GameEngineCore::GetContext()->PSSetShaderResources(_Slot, 1, &ResetRes);
}

void GameEngineTexture::CSReset(UINT _Slot)
{
	ID3D11ShaderResourceView* ResetRes = nullptr;
	GameEngineCore::GetContext()->CSSetShaderResources(_Slot, 1, &ResetRes);
}

void GameEngineTexture::ResCreate(ID3D11Texture2D* _Res)
{
	Texture2D = _Res;

	Texture2D->GetDesc(&Desc);

	CreateRenderTargetView();

	int a = 0;
}

void GameEngineTexture::ResCreate(const D3D11_TEXTURE2D_DESC& _Desc) 
{
	Desc = _Desc;

	if (S_OK != GameEngineCore::GetDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D))
	{
		MsgBoxAssert("if (S_OK != GameEngineCore::GetDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D))");
	}

	if (D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET & Desc.BindFlags)
	{
		CreateRenderTargetView();
	}

	if (D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE & Desc.BindFlags)
	{
		CreateShaderResourceView();
	}

	if (D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL & Desc.BindFlags)
	{
		CreateDepthStencilView();
	}
}

GameEngineColor GameEngineTexture::GetColor(unsigned int _X, unsigned int _Y, GameEngineColor _DefaultColor)
{

	if (0 > _X)
	{
		return _DefaultColor;
	}

	if (0 > _Y)
	{
		return _DefaultColor;
	}

	if (_X >= GetScale().uiX())
	{
		return _DefaultColor;
	}

	if (_Y >= GetScale().uiY())
	{
		return _DefaultColor;
	}

	DXGI_FORMAT Fmt = Image.GetMetadata().format;


	// ù��° �ּҸ� 1����Ʈ �ڷ������� ���.
	unsigned char* Ptr = Image.GetPixels();

	switch (Fmt)
	{
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	{
		GameEngineColor ResultColor;
		Ptr += ((_Y * GetScale().iX()) + _X) * 4;
		ResultColor.B = Ptr[0];
		ResultColor.G = Ptr[1];
		ResultColor.R = Ptr[2];
		ResultColor.A = Ptr[3];
		return ResultColor;
	}
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UINT:
	case DXGI_FORMAT_R8G8B8A8_SNORM:
	case DXGI_FORMAT_R8G8B8A8_SINT:
	{
		GameEngineColor ResultColor;
		Ptr += ((_Y * GetScale().iX()) + _X) * 4;
		ResultColor.R = Ptr[0];
		ResultColor.G = Ptr[1];
		ResultColor.B = Ptr[2];
		ResultColor.A = Ptr[3];
		return ResultColor;
	}
	default:
		MsgBoxAssert("������ ó���ϴ� �Լ��� ������ ���� �����Դϴ�");
		break;
	}


	return _DefaultColor;
}