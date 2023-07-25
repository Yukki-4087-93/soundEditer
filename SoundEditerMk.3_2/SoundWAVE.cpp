//-----------------------------------------------------------------------------
//
//サウンド
//Author::TAKANO
//
//-----------------------------------------------------------------------------

//--------------------------------------
//インクルードファイル
//--------------------------------------
#include "application.h"
#include "input.h"
#include "SoundWAVE.h"
#include <assert.h>

//--------------------------------------
// 定数定義
//--------------------------------------
namespace 
{
struct SParam
{//サウンドパラメーターの構造体
	char *m_pFilename;									// ファイル名
	int m_nCountLoop;									// ループカウント
};

const SParam param[] =
{
	{ "Data/BGM/battleban.wav", -1 },				// BGM Number0 ゲームで使用する
	{ "Data/BGM/last_meeting.wav", -1 },			// BGM Number1 タイトルで使用する
	{ "Data/BGM/result_bgm.wav", -1 },				// BGM Number2 リザルトで使用する
	{ "Data/BGM/Virtual_mission.wav", -1 },			// BGM Number3 チュートリアルで使用する
	{ "Data/BGM/battlemeeting_ver_2.wav", -1 },		// BGM Number4 未実装(サウンドマネージャーで使用)
	{ "Data/BGM/No_name.wav", -1 },					// BGM Number5 未実装(サウンドマネージャーで使用)
	{ "Data/BGM/challenge_to_tomorrow.wav", -1 },	// BGM Number6 未実装(サウンドマネージャーで使用)
	{ "Data/BGM/battlemeeting.wav", -1 },			// BGM Number7 未実装(サウンドマネージャーで使用)
	{ "Data/BGM/Heart_sound.wav", -1 },				// BGM Number8 未実装(サウンドマネージャーで使用)
	{ "Data/BGM/Drum_Voice.wav", -1 },				// BGM Number9 未実装(サウンドマネージャーで使用)
	{ "Data/BGM/Ranking.wav", -1 },					// BGM Number10 ランキングで使用する
	{ "Data/SE/explosion000.wav", 0 },				// SE Number0 未実装(サウンドマネージャーで使用)
	{ "Data/SE/hit000.wav", 0 },					// SE Number1 未実装(サウンドマネージャーで使用)
	{ "Data/SE/shot000.wav", 0 },					// SE Number2 未実装(サウンドマネージャーで使用)
	{ "Data/SE/gameOver_SE.wav", 0 }				// SE Number3 未実装(サウンドマネージャーで使用)
};

const float MAX_CONSTANT = 11.0f;						//定数の最大値
const float MIN_CONSTANT_VOLUME = 0.0f;					//音量定数の最小値
const float MIN_CONSTANT_PITCH = -11.0f;				//音程定数の最小値
const float SOUND_PITCH = 1.0f;							//音程の初期値
const float SOUND_VOLUME = 1.0f;						//音量の初期値
const float CHANGE_VOLUME = 0.002f;						//徐々に変わる音量の変更値
const int MAX_COUNT = 24;								//カウンターの最大数
}

// 上位のパラメータ設定で、指定した列挙の
// 数字と会わなかったらエラーを起こしてくれます。
static_assert(sizeof(param) / sizeof(param[0]) == CSoundWave::WAVE_MAX, "Hahaha!! Error! !rorrE !!ahahaH");


//--------------------------------------
//コンストラクタ
//--------------------------------------
CSoundWave::CSoundWave()
{
	m_type = CSoundWave::WAVE_NONE;
	m_nNumber = 0;
	m_nCounter = 0;

	// ソースボイスのクリア
	memset(m_apSourceVoice,0,sizeof(m_apSourceVoice[0][0]));

	// オーディオデータのクリア
	memset(m_apDataAudio, 0, sizeof(m_apDataAudio[0]));
	
	// オーディオデータサイズのクリア
	memset(m_aSizeAudio, 0, sizeof(m_aSizeAudio[0]));

	/*サウンド再生フラグのクリア*/
	for (int nFlagSound = 0; nFlagSound < CSoundWave::WAVE_MAX; nFlagSound++)
	{//サウンドの最大数だけ繰り返す
		for (int nNumSound = 0; nNumSound < NUM_PLAT_MAX; nNumSound++)
		{//サウンドの最大再生分繰り返す
			m_aPlaySound[nFlagSound][nNumSound] = false;		// サウンド再生フラグのクリア
		}
	}
}

//--------------------------------------
//デストラクタ
//--------------------------------------
CSoundWave::~CSoundWave()
{
}

//--------------------------------------
//初期化
//--------------------------------------
void CSoundWave::Init()
{
	HRESULT SoundEntity;			//サウンドの実体情報を格納する変数の宣言

	m_type = CSoundWave::WAVE_NONE;		//タイプの初期化
	m_nVolSeter = 0;
	m_nNumber = 0;
	m_nCounter = 0;

	// XAudio2オブジェクトの情報取得
	IXAudio2 *XAudeo2Obj = CSound::GetXAudioObject();

	// COMライブラリの初期化
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	SoundEntity = XAudio2Create(&XAudeo2Obj, 0);
	if (FAILED(SoundEntity))
	{
		// COMライブラリの終了処理
		CoUninitialize();

		//プログラムを止める
		assert(false);		//XAudio2オブジェクトの作成に失敗してます
	}

	// マスターボイスの情報取得
	IXAudio2MasteringVoice * MasterVoice = CSound::GetMasteringVoice();

	// マスターボイスの生成
	SoundEntity = XAudeo2Obj->CreateMasteringVoice(&MasterVoice);
	if (FAILED(SoundEntity))
	{//生成に失敗した場合

		if (XAudeo2Obj)
		{//オーディオインターフェースに値が入っていたら
			XAudeo2Obj->Release();		// XAudio2オブジェクトの開放
			XAudeo2Obj = nullptr;		// NULLを代入
		}

		// COMライブラリの終了処理
		CoUninitialize();

		//プログラムを止める
		assert(false);		//マスターボイスの生成に失敗してます
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < CSoundWave::WAVE_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(param[nCntSound].m_pFilename,
			GENERIC_READ,
			FILE_SHARE_READ,
			nullptr,
			OPEN_EXISTING,
			0,
			nullptr);

		if (hFile == INVALID_HANDLE_VALUE)
		{//生成に失敗した
			
			//プログラムを止める
			assert(false);	//サウンドデータファイルの生成に失敗しています
		}
		if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動

			/*ファイルポインタと最初のポインタの値が同値 = 失敗したら*/

			//プログラムを止める
			assert(false);	//サウンドデータファイルの生成に失敗しています
		}

		// WAVEファイルのチェック
		SoundEntity = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(SoundEntity))
		{//ファイルチェックに失敗したら
			//プログラムを止める
			assert(false);	//WAVEファイルチェックに失敗しています
		}
		SoundEntity = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(SoundEntity))
		{//データの読み込みに失敗したら
			//プログラムを止める
			assert(false);	//WAVEファイルのデータ読込に失敗しています
		}
		if (dwFiletype != 'EVAW')
		{//WAVEファイルではなかったから
			//プログラムを止める
			assert(false);	//WAVEファイルの以外を読み込んでいます。
		}

		// フォーマットチェック
		SoundEntity = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(SoundEntity))
		{//フォーマットの確認に失敗したら
			 //プログラムを止める
			assert(false);	//フォーマットチェックに失敗しています。
		}
		SoundEntity = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(SoundEntity))
		{//データの読み込みに失敗したら
			//プログラムを止める
			assert(false);	//フォーマットの読み込みに失敗しています。
		}

		// オーディオデータ読み込み
		SoundEntity = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(SoundEntity))
		{//データサイズの読み込みに失敗したら
			//プログラムを止める
			assert(false);	//オーディオデータの読み込みに失敗しています。
		}

		//サウンドの動的確保
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);

		//オーディオデータチェック
		SoundEntity = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(SoundEntity))
		{//読み込みに失敗した場合
			//プログラムを止める
			assert(false);	//オーディオデータチェックに失敗しています。
		}

		for (int i = 0; i < NUM_PLAT_MAX; i++)
		{
			// ソースボイスの生成
			SoundEntity = XAudeo2Obj->CreateSourceVoice(&m_apSourceVoice[nCntSound][i], &(wfx.Format));
			if (FAILED(SoundEntity))
			{// 生成に失敗した場合
				// プログラムを止める
				assert(false);	// ソースボイスの生成に失敗しています。
			}

			// オーディオバッファの登録
			m_apSourceVoice[nCntSound][i]->SubmitSourceBuffer(&buffer);
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = param[nCntSound].m_nCountLoop;

		// ファイルを閉じます
		CloseHandle(hFile);
	}
}

//--------------------------------------
//終了
//--------------------------------------
void CSoundWave::Uninit()
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < CSoundWave::WAVE_MAX; nCntSound++)
	{
		for (int i = 0; i < NUM_PLAT_MAX; i++)
		{//最大再生数分確認する
			if (m_apSourceVoice[nCntSound][i])
			{// ソースボイスに値が入っている
				// 一時停止
				m_apSourceVoice[nCntSound][i]->Stop(0);

				// ソースボイスの破棄
				m_apSourceVoice[nCntSound][i]->DestroyVoice();
				m_apSourceVoice[nCntSound][i] = nullptr;

			}
		}

		// オーディオデータの開放
		free(m_apDataAudio[nCntSound]);
		m_apDataAudio[nCntSound] = nullptr;
	}

	// XAudeoオブジェクトの破棄
	CSound::DestroyXAudioObject();

	// COMライブラリの終了処理
	CoUninitialize();
}

//--------------------------------------
//更新
//--------------------------------------
void CSoundWave::Update()
{
	for (int nCntType = 0; nCntType < CSoundWave::WAVE_MAX; nCntType++)
	{
		for (int nCntSound = 0; nCntSound < NUM_PLAT_MAX; nCntSound++)
		{
			//XAudioの状態を取得する変数の宣言
			XAUDIO2_VOICE_STATE xa2state;

			// 状態取得
			m_apSourceVoice[nCntType][nCntSound]->GetState(&xa2state);

			if (m_aPlaySound[nCntType][nCntSound] && xa2state.BuffersQueued == 0)
			{//サウンドフラグが真で、オーディオの情報が使用されていたら

			 // 使用していない状態にする。
				m_aPlaySound[nCntType][nCntSound] = false;

				// 一時停止
				m_apSourceVoice[nCntType][nCntSound]->Stop(0);

				// オーディオバッファの削除
				m_apSourceVoice[nCntType][nCntSound]->FlushSourceBuffers();
			}
		}
	}

	if (m_type != WAVE_LABEL::WAVE_NONE &&
		CApplication::GetInput()->GetkeyboardPress(DIK_N))
	{
		if (m_aPlaySound[WAVE_LABEL::WAVE_BGM_BATTLEBAN][0])
		{
			SlowlyUpVolume(m_type,0);
		}
	}

	if (m_type != WAVE_LABEL::WAVE_NONE &&
		CApplication::GetInput()->GetkeyboardPress(DIK_M))
	{
		if (m_aPlaySound[WAVE_LABEL::WAVE_BGM_BATTLEBAN][1])
		{
			SlowlyDownVolume(m_type,1);
		}
	}
}

//--------------------------------------
//サウンド再生
//--------------------------------------
HRESULT CSoundWave::Play(WAVE_LABEL type, int numLabel)
{
	if (numLabel >= NUM_PLAT_MAX)
	{
		numLabel = 0;
	}

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[type];
	buffer.pAudioData = m_apDataAudio[type];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = param[type].m_nCountLoop;

	// 使用されている状態にする
	m_aPlaySound[type][numLabel] = true;

	// 状態取得
	m_apSourceVoice[type][numLabel]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		m_apSourceVoice[type][numLabel]->Stop(type, numLabel);

		// オーディオバッファの削除
		m_apSourceVoice[type][numLabel]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_apSourceVoice[type][numLabel]->SubmitSourceBuffer(&buffer);

	// 再生
	m_apSourceVoice[type][numLabel]->Start(0);

	return S_OK;
}

//--------------------------------------
//音量の全体設定
//--------------------------------------
void CSoundWave::SetVolume(WAVE_LABEL type, float fVolume)
{
	for (int i = 0; i < NUM_PLAT_MAX; i++)
	{
		m_apSourceVoice[type][i]->SetVolume(fVolume);	// ソースボイス側の音量設定
		CSound::SetVolume(fVolume);						// 親側の音量を設定
	}
}

//--------------------------------------
//ピッチの全体操作
//--------------------------------------
void CSoundWave::SetRate(WAVE_LABEL type, float rate)
{
	for (int i = 0; i < NUM_PLAT_MAX; i++)
	{
		if (type == CSoundWave::WAVE_NONE)
		{
			continue;
		}
		m_apSourceVoice[type][i]->SetFrequencyRatio(rate);	// ソースボイス側の音程設定
		CSound::SetPitch(rate);								// 親側の音量を設定
	}
}

//--------------------------------------
//音量の部分設定
//--------------------------------------
void CSoundWave::SetPartVolume(WAVE_LABEL type, int nNumber, float fVolume)
{
	XAUDIO2_VOICE_STATE xa2state;

	if (type > CSoundWave::WAVE_MAX ||
		nNumber > NUM_PLAT_MAX)
	{
		assert(false);
	}

	// 状態取得
	m_apSourceVoice[type][nNumber]->GetState(&xa2state);

	if (xa2state.BuffersQueued == 0)
	{//再生中でないなら
		assert(false);
	}

	m_apSourceVoice[type][nNumber]->SetVolume(fVolume);
}

//--------------------------------------
//ピッチの部分設定
//--------------------------------------
void CSoundWave::SetPartRate(WAVE_LABEL type, int nNumber, float rate)
{
	XAUDIO2_VOICE_STATE xa2state;

	if (type > CSoundWave::WAVE_MAX ||
		nNumber > NUM_PLAT_MAX)
	{
		assert(false);
	}

	// 状態取得
	m_apSourceVoice[type][nNumber]->GetState(&xa2state);

	if (xa2state.BuffersQueued == 0)
	{//再生中でないなら
		assert(false);
	}

	m_apSourceVoice[type][nNumber]->SetVolume(rate);
}

//--------------------------------------
//サウンド停止
//--------------------------------------
void CSoundWave::Stop(WAVE_LABEL type, int nNumber)
{
	XAUDIO2_VOICE_STATE xa2state;

	if (type > CSoundWave::WAVE_MAX ||
		nNumber > NUM_PLAT_MAX)
	{
		assert(false);
	}

	// 状態取得
	m_apSourceVoice[type][nNumber]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		m_apSourceVoice[type][nNumber]->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice[type][nNumber]->FlushSourceBuffers();
	}

	// 使用されている状態にする
	m_aPlaySound[type][nNumber] = false;
}

//--------------------------------------
//全てのサウンド停止
//--------------------------------------
void CSoundWave::Stop()
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < CSoundWave::WAVE_MAX; nCntSound++)
	{
		for (int i = 0; i < NUM_PLAT_MAX; i++)
		{
			if (!m_aPlaySound[nCntSound][i])
			{//サウンドが使用されていないとき
				continue;		//始めに戻す
			}

			else if (m_apSourceVoice[nCntSound][i])
			{// サウンドを使用している
				// 一時停止
				m_apSourceVoice[nCntSound][i]->Stop(0);

				// 使用されていない状態にする
				m_aPlaySound[nCntSound][i] = false;
			}
		}
	}
}

//--------------------------------------
//音量をカウントをカウントする
//--------------------------------------
void CSoundWave::SetCounter(int count)
{
	m_nCounter += count;

	if (m_nCounter > MAX_COUNT)
	{
		m_nCounter = 0;
	}
}

//--------------------------------------
//音量を上げる
//--------------------------------------
void CSoundWave::UpVolumeAll(float volume)
{
	//音量情報を取得する
	float fVol = CSound::GetVolume();

	//音量を加算
	fVol += volume;

	if (fVol >= MAX_CONSTANT)
	{//音量が定数を上回る数値になったら
		fVol = MAX_CONSTANT;				//定数に設定
	}

	//音量の設定
	SetVolume(m_type, fVol);
}

//--------------------------------------
//音量を下げる
//--------------------------------------
void CSoundWave::DownVolumeAll(float volume)
{
	//音量情報を取得する
	float fVol = CSound::GetVolume();

	//音量を減算
	fVol -= volume;

	if (fVol <= MIN_CONSTANT_VOLUME)
	{//音量が定数を下回る数値になったら
		fVol = MIN_CONSTANT_VOLUME;		//定数に設定
	}

	//音量を設定
	SetVolume(m_type, fVol);
}

//--------------------------------------
//音程を上げる
//--------------------------------------
void CSoundWave::UpPitcheAll(float pitch)
{
	//音量情報を取得する
	float fPit = CSound::GetPitch();

	//音程を上げる
	fPit += pitch;

	//if (fPit >= MAX_CONSTANT)
	//{//音程が定数を上回る数値になったら
	//	fPit = MAX_CONSTANT;				//定数に設定
	//}

	//音程を設定
	SetRate(m_type, fPit);
}

//--------------------------------------
//音程を下げる
//--------------------------------------
void CSoundWave::DownPitcheAll(float pitch)
{
	//音量情報を取得する
	float fPit = CSound::GetPitch();

	//音程の減算
	fPit -= pitch;

	if (fPit <= MIN_CONSTANT_PITCH)
	{//音量が定数を下回る数値になったら
		fPit = MIN_CONSTANT_PITCH;		//定数に設定
	}

	//音程を設定
	SetRate(m_type, fPit);
}

//--------------------------------------
//反響の生成
//--------------------------------------
void CSoundWave::SlowlyUpVolume(WAVE_LABEL type, int nNumber)
{
	if (type == WAVE_LABEL::WAVE_NONE)
	{//サウンドが使用されていなかったら
		return;			//返す
	}

	// 現在の音量を取得
	float ChangeVolume = CSound::GetVolume();

	m_nVolSeter++;
	
	// 音量を変える変数に代入
	ChangeVolume = ((sinf(m_nVolSeter * CHANGE_VOLUME * D3DX_PI * 2.0f) + 1.0f) * 0.5f);

	//音量の設定
	SetPartVolume(type, nNumber, ChangeVolume);
}

//--------------------------------------
//反響の生成
//--------------------------------------
void CSoundWave::SlowlyDownVolume(WAVE_LABEL type, int nNumber)
{
	if (type == WAVE_LABEL::WAVE_NONE)
	{//サウンドが使用されていなかったら
		return;			//返す
	}

	// 現在の音量を取得
	float ChangeVolume = CSound::GetVolume();

	m_nVolSeter++;

	// 音量を変える変数に代入
	ChangeVolume = ((sinf(m_nVolSeter * CHANGE_VOLUME * D3DX_PI * 2.0f) + 1.0f) * 0.5f);

	//音量の設定
	SetPartVolume(type, nNumber, ChangeVolume);
}

//--------------------------------------
//一塊の確認
//--------------------------------------
HRESULT CSoundWave::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, nullptr) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, nullptr) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, nullptr) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, nullptr, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//--------------------------------------
//一塊の読み取り
//--------------------------------------
HRESULT CSoundWave::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, nullptr) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
