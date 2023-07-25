//---------------------------------------------------------
//
//サウンド
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _SOUND_H_
#define _SOUND_H_

//--------------------------------------
//インクルードファイル
//--------------------------------------
#include"d3dx9.h"
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include"xaudio2.h"

//--------------------------------------
//クラス定義
//サウンド関連
//--------------------------------------
class CSound
{
public:
	CSound();												// コンストラクタ
	~CSound();												// デストラクタ
	virtual void Init() = 0;								// 初期化
	virtual void Uninit() = 0;								// 終了
	virtual void Update() = 0;								// 更新
	void DestroyXAudioObject();								// XAudioObjectの解放

public:
	void SetVolume(float fvol) { m_fVol = fvol; }			// 音量の設定
	float GetVolume() { return m_fVol; }					// 音量の情報取得
	void SetPitch(float fpit) { m_fPitch = fpit; }			// 音量の設定
	float GetPitch() { return m_fPitch; }					// 音程の情報取得
	IXAudio2 *GetXAudioObject() { return m_pXAudio2; }
	IXAudio2MasteringVoice *GetMasteringVoice() { return m_pMasteringVoice; }

private:
	IXAudio2 *m_pXAudio2;												// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;							// マスターボイス
	int m_nCountFade;													// フェード用カウンター
	float m_fVol;														// サウンドの音量を変化させる変数
	float m_fPitch;														// サウンドの音程を変化させる変数
	
};

#endif // !_SOUND_H_
