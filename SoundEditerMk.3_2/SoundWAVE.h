//---------------------------------------------------------
//
//サウンド
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _SOUNDWAVE_H_
#define _SOUNDWAVE_H_

//--------------------------------------
//インクルードファイル
//--------------------------------------
#include"d3dx9.h"
#include "sound.h"

//--------------------------------------
//定数定義
//--------------------------------------
const int NUM_PLAT_MAX = 24;				//サウンドを再生する最大数

//--------------------------------------
//クラス定義
//サウンド関連
//--------------------------------------
class CSoundWave : public CSound
{
public:

	enum WAVE_LABEL
	{
		WAVE_NONE = -1,									// 使用されていない状態
		WAVE_BGM_BATTLEBAN = 0,							// BGM 0
		WAVE_BGM_LAST_MEETING,							// BGM 1
		WAVE_BGM_RESULT_BGM,							// BGM 2
		WAVE_BGM_VIRTUAL,								// BGM 3
		WAVE_BGM_BATTLEMEETING_VER_2,					// BGM 4
		WAVE_BGM_NO_NAME,								// BGM 5
		WAVE_BGM_CHALLENGE_TO_TOMORROW,					// BGM 6
		WAVE_BGM_BATTLEMEETING,							// BGM 7
		WAVE_BGM_HEART,									// BGM 8
		WAVE_BGM_DRUM_VOICE,							// BGM 9
		WAVE_BGM_RANKING,								// BGM 10
		WAVE_SE_EXPOSION,								// SE1
		WAVE_SE_HIT,									// SE2
		WAVE_SE_SHOT,									// SE3
		WAVE_SE_D,
		WAVE_MAX
	};

	CSoundWave();												// コンストラクタ
	~CSoundWave();												// デストラクタ
	void Init() override;										// 初期化
	void Uninit() override;										// 終了
	void Update() override;										// 更新

	HRESULT Play(WAVE_LABEL type,int numLabel);							// 再生
	void SetVolume(WAVE_LABEL type, float fVolume);						// 音量
	void SetRate(WAVE_LABEL type, float rate);							// ピッチ操作
	void SetPartVolume(WAVE_LABEL type, int nNumber, float fVolume);	// 音量の部分設定
	void SetPartRate(WAVE_LABEL type, int nNumber, float rate);			// ピッチの部分設定
	void Stop(WAVE_LABEL type, int nNumber);							// 一部停止
	void Stop();														// 全停止
	void SetCounter();
	int GetCpounter() { return m_nCounter; }

public:
	void UpVolumeAll(float volume);			// 音量を上げたいときに使う
	void DownVolumeAll(float volume);			// 音量を下げたいときに使う
	void UpPitcheAll(float pitch);				// 音程を上げたいときに使う
	void DownPitcheAll(float pitch);			// 音程を下げたいときに使う
	void SetType(WAVE_LABEL type) { m_type = type; }	// タイプを設定する
	void SlowlyUpVolume(WAVE_LABEL type,int nNumber);				// 緩やかに音量を上げる
	void SlowlyDownVolume(WAVE_LABEL type, int nNumber);			// 緩やかに音量を下げる

public:
	HRESULT CheckChunk(HANDLE hFile,						//一塊(チャンク)の確認
		DWORD format,
		DWORD *pChunkSize,
		DWORD *pChunkDataPosition);


	HRESULT ReadChunkData(HANDLE hFile,						//一塊(チャンク)の読み込み
		void *pBuffer,
		DWORD dwBuffersize,
		DWORD dwBufferoffset);

private:
	IXAudio2SourceVoice *m_apSourceVoice[WAVE_MAX][NUM_PLAT_MAX];		// ソースボイス
	BYTE *m_apDataAudio[WAVE_MAX];										// オーディオデータ
	DWORD m_aSizeAudio[WAVE_MAX];										// オーディオデータサイズ
	bool m_aPlaySound[WAVE_MAX][NUM_PLAT_MAX];							// サウンド再生フラグ
	WAVE_LABEL m_type;													// サウンドのタイプ
	int m_nVolSeter;													// 緩やかにサウンドを下げる時に使用する
	int m_nNumber;														// ナンバーを代入する変数
	int m_nCounter;														// 音量の変更をする変数
};

#endif // !_SOUNDWAVE_H_
