//--------------------------------------------------------------------------------------
//
// �����_�����O
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "renderer.h"
#include "main.h"
#include "SoundWAVE.h"
#include <tchar.h> // _T

//--------------------------------------
//�萔��`
//--------------------------------------
// �X�N���[���̕�
const int SCREEN_WIDTH = 1280;
// �X�N���[���̍���
const int SCREEN_HEIGHT = 720;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CRenderer::CRenderer()
{
	m_nCountFPS = 0;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CRenderer::~CRenderer()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`��ƒ��_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{
		// �������s
		return E_FAIL;
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 24, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CRenderer::Uninit()
{

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//--------------------------------------
//�X�V
//--------------------------------------
void CRenderer::Update()
{
	//CObject::UpdateAll();
}

//--------------------------------------
//�`��
//--------------------------------------
void CRenderer::Draw()
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//CObject::DrawAll();
		
#ifdef _DEBUG
		// FPS�\��
		DrawFPS();
#endif // _DEBUG

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef _DEBUG
//--------------------------------------
//FPS�̕`��
//--------------------------------------
void CRenderer::DrawFPS()
{
	int nCountFPS = GetCount();
	int nLength = 0;
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	wsprintf(str, _T("\nFPS : %d\n\n"), nCountFPS);
	nLength = (int)strlen(&str[0]);
	wsprintf(&str[nLength], "L�L�[�c�ȑւ�\n\n");
	nLength = (int)strlen(&str[0]);
	wsprintf(&str[nLength], "���L�[�c���ʂ��グ��\n\n");
	nLength = (int)strlen(&str[0]);
	wsprintf(&str[nLength], "���L�[�c���ʂ�������\n\n");
	nLength = (int)strlen(&str[0]);
	wsprintf(&str[nLength], "���L�[�c�t�F�[�h�C��\n\n");
	nLength = (int)strlen(&str[0]);
	wsprintf(&str[nLength], "���L�[�c�t�F�[�h�A�E�g\n\n");
	nLength = (int)strlen(&str[0]);
	wsprintf(&str[nLength], "O�L�[�c�s�b�`�グ\n\n");
	nLength = (int)strlen(&str[0]);
	wsprintf(&str[nLength], "P�L�[�c�s�b�`����\n\n");
	nLength = (int)strlen(&str[0]);
	wsprintf(&str[nLength], "�V�@�\�ǉ��\��");
	nLength = (int)strlen(&str[0]);

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif // _DEBUG

//--------------------------------------
//�f�o�C�X�̏��擾
//--------------------------------------
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
}