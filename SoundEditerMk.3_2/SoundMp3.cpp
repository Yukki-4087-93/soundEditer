////-----------------------------------------------------------------------------
////
////�T�E���h
////Author::TAKANO
////
////-----------------------------------------------------------------------------
//
////--------------------------------------
////�C���N���[�h�t�@�C��
////--------------------------------------
//#include "application.h"
//#include "input.h"
//#include "SoundMp3.h"
//#include <assert.h>
//
////--------------------------------------
//// �e���f�ނ̃p�����[�^��`
////--------------------------------------
//const CSoundMp3::PARAM CSoundMp3::param[] =
//{
//	{ "Data/BGM/Test.mp3", -1 },				// BGM Number0 �Q�[���Ŏg�p����
//};
//
//static_assert(sizeof(CSoundMp3::param) / sizeof(CSoundMp3::param[0]) == CSoundMp3::MP3_MAX, "�w�萔���������ł������܂�");
//
////--------------------------------------
////�R���X�g���N�^
////--------------------------------------
//CSoundMp3::CSoundMp3()
//{
//	m_type = CSoundMp3::MP3_NONE;
//	
//}
//
//
////--------------------------------------
////�f�X�g���N�^
////--------------------------------------
//CSoundMp3::~CSoundMp3()
//{
//}
//
////--------------------------------------
////������
////--------------------------------------
//void CSoundMp3::Init()
//{
//	m_type = CSoundMp3::MP3_NONE;		//�^�C�v�̏�����
//
//	m_pCreatSound = nullptr;
//
//	m_pPlaySound = nullptr;
//
//	m_pLoop = nullptr;
//
//	m_pMpObject = nullptr;
//
//	m_pOutputMp3 = nullptr;
//
//	// XAudio2�I�u�W�F�N�g�̏��擾
//	IXAudio2 *XAudeo2Obj = CSound::GetXAudioObject();
//
//	// COM���C�u�����̏�����
//	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
//
//	//�C���X�^���X�̏�����
//	CoCreateInstance(CLSID_FilterGraph,nullptr, CLSCTX_INPROC_SERVER,IID_IGraphBuilder,(void**)&m_pCreatSound);
//
//	// �C���^�[�t�F�[�X�̏�����
//	m_pCreatSound->QueryInterface(IID_IMediaControl,(void**)&m_pPlaySound);
//
//	m_pCreatSound->QueryInterface(IID_IMediaSeeking,(void**)&m_pLoop);
//
//	const wchar_t *lplp = L"Data/BGM/Test.mp3";
//
//	m_pCreatSound->AddSourceFilter(lplp,nullptr, &m_pMpObject);
//
//	m_pMpObject->FindPin((LPCWSTR)"lplp",&m_pOutputMp3);
//
//	m_pCreatSound->Render(m_pOutputMp3);
//}
//
////--------------------------------------
////�I��
////--------------------------------------
//void CSoundMp3::Uninit()
//{
//	
//	// COM���C�u�����̏I������
//	CoUninitialize();
//}
//
////--------------------------------------
////�X�V
////--------------------------------------
//void CSoundMp3::Update()
//{
//	
//}
//
////--------------------------------------
////�T�E���h�Đ�
////--------------------------------------
//HRESULT CSoundMp3::Play()
//{
//	m_pPlaySound->Run();
//	
//	return S_OK;
//}
//
//void CSoundMp3::Stop()
//{
//	m_pPlaySound->Stop();
//}
//
