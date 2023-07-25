//-----------------------------------------------------------------------------
//
//サウンド
//Author::TAKANO
//
//-----------------------------------------------------------------------------

//--------------------------------------
//インクルードファイル
//--------------------------------------
#include "sound.h"
#include <assert.h>

//--------------------------------------
//定数定義
//--------------------------------------
const float SOUND_VOLUME = 1.0f;						//定数の最大値
const float SOUND_PITCH = 1.0f;							//音程の初期値

//--------------------------------------
//コンストラクタ
//--------------------------------------
CSound::CSound()
{
	m_pXAudio2 = nullptr;				// XAudio2オブジェクトへのインターフェイスのクリア
	m_pMasteringVoice = nullptr;		// マスターボイスのクリア
	
	m_fVol = SOUND_VOLUME;				//音量の初期化
	m_fPitch = SOUND_PITCH;				//音程の初期化
}

//--------------------------------------
//デストラクタ
//--------------------------------------
CSound::~CSound()
{
}

//--------------------------------------
//XAudioObjectの解放
//--------------------------------------
void CSound::DestroyXAudioObject()
{
	if (m_pMasteringVoice != nullptr)
	{
		// マスターボイスの破棄
		m_pMasteringVoice->DestroyVoice();
		m_pMasteringVoice = nullptr;
	}

	if (m_pXAudio2 != nullptr)
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
		m_pXAudio2 = nullptr;
	}
}
