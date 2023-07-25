////-----------------------------------------------------------------------------
////
////サウンド
////Author::TAKANO
////
////-----------------------------------------------------------------------------
//
////--------------------------------------
////インクルードファイル
////--------------------------------------
//#include "application.h"
//#include "input.h"
//#include "SoundMp3.h"
//#include <assert.h>
//
////--------------------------------------
//// 各音素材のパラメータ定義
////--------------------------------------
//const CSoundMp3::PARAM CSoundMp3::param[] =
//{
//	{ "Data/BGM/Test.mp3", -1 },				// BGM Number0 ゲームで使用する
//};
//
//static_assert(sizeof(CSoundMp3::param) / sizeof(CSoundMp3::param[0]) == CSoundMp3::MP3_MAX, "指定数がちげぇでごぜぇます");
//
////--------------------------------------
////コンストラクタ
////--------------------------------------
//CSoundMp3::CSoundMp3()
//{
//	m_type = CSoundMp3::MP3_NONE;
//	
//}
//
//
////--------------------------------------
////デストラクタ
////--------------------------------------
//CSoundMp3::~CSoundMp3()
//{
//}
//
////--------------------------------------
////初期化
////--------------------------------------
//void CSoundMp3::Init()
//{
//	m_type = CSoundMp3::MP3_NONE;		//タイプの初期化
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
//	// XAudio2オブジェクトの情報取得
//	IXAudio2 *XAudeo2Obj = CSound::GetXAudioObject();
//
//	// COMライブラリの初期化
//	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
//
//	//インスタンスの初期化
//	CoCreateInstance(CLSID_FilterGraph,nullptr, CLSCTX_INPROC_SERVER,IID_IGraphBuilder,(void**)&m_pCreatSound);
//
//	// インターフェースの初期化
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
////終了
////--------------------------------------
//void CSoundMp3::Uninit()
//{
//	
//	// COMライブラリの終了処理
//	CoUninitialize();
//}
//
////--------------------------------------
////更新
////--------------------------------------
//void CSoundMp3::Update()
//{
//	
//}
//
////--------------------------------------
////サウンド再生
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
