////---------------------------------------------------------
////
////サウンドMP3
////Author::TAKANO
////
////---------------------------------------------------------
//#ifndef _SOUNDMP3_H_
//#define _SOUNDMP3_H_
//
////--------------------------------------
////インクルードファイル
////--------------------------------------
//#include "d3dx9.h"
//#include "sound.h"
//#include <dshow.h>
//#pragma comment(lib,"strmiids.lib")
//
////--------------------------------------
////クラス定義
////サウンド関連
////--------------------------------------
//class CSoundMp3 : public CSound
//{
//public:
//
//	enum NUM_MP3
//	{
//		MP3_NONE = -1,									// 使用されていない状態
//		MP3_BGM_BATTLEBAN = 0,							// BGM 0
//		MP3_MAX
//	};
//
//	CSoundMp3();												// コンストラクタ
//	~CSoundMp3();												// デストラクタ
//	void Init() override;										// 初期化
//	void Uninit() override;										// 終了
//	void Update() override;										// 更新
//
//	HRESULT Play();							// 再生
//	void Stop();								// 一部停止
//
//public:
//	
//
//public:
//	//HRESULT CheckChunk(HANDLE hFile,						//一塊(チャンク)の確認
//	//	DWORD format,
//	//	DWORD *pChunkSize,
//	//	DWORD *pChunkDataPosition);
//
//
//	//HRESULT ReadChunkData(HANDLE hFile,						//一塊(チャンク)の読み込み
//	//	void *pBuffer,
//	//	DWORD dwBuffersize,
//	//	DWORD dwBufferoffset);
//
//private:
//	//IXAudio2SourceVoice *m_apSourceVoice[CSoundMp3::MP3_MAX];			// ソースボイス
//	//BYTE *m_apDataAudio[CSoundMp3::MP3_MAX];										// オーディオデータ
//	//DWORD m_aSizeAudio[CSoundMp3::MP3_MAX];										// オーディオデータサイズ
//	//bool m_aPlaySound[CSoundMp3::MP3_MAX];								// サウンド再生フラグ
//	IGraphBuilder* m_pCreatSound;	// 
//	IMediaControl* m_pPlaySound;	//
//	IMediaSeeking* m_pLoop;			//
//	IBaseFilter* m_pMpObject;		//
//	IPin* m_pOutputMp3;
//	NUM_MP3 m_type;
//};
//
//#endif // !_SOUNDMP3_H_
