//-----------------------------------------------------------------------------
//
//�T�E���h
//Author::TAKANO
//
//-----------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "input.h"
#include "SoundWAVE.h"
#include <assert.h>

//--------------------------------------
// �萔��`
//--------------------------------------
namespace 
{
struct SParam
{//�T�E���h�p�����[�^�[�̍\����
	char *m_pFilename;									// �t�@�C����
	int m_nCountLoop;									// ���[�v�J�E���g
};

const SParam param[] =
{
	{ "Data/BGM/battleban.wav", -1 },				// BGM Number0 �Q�[���Ŏg�p����
	{ "Data/BGM/last_meeting.wav", -1 },			// BGM Number1 �^�C�g���Ŏg�p����
	{ "Data/BGM/result_bgm.wav", -1 },				// BGM Number2 ���U���g�Ŏg�p����
	{ "Data/BGM/Virtual_mission.wav", -1 },			// BGM Number3 �`���[�g���A���Ŏg�p����
	{ "Data/BGM/battlemeeting_ver_2.wav", -1 },		// BGM Number4 ������(�T�E���h�}�l�[�W���[�Ŏg�p)
	{ "Data/BGM/No_name.wav", -1 },					// BGM Number5 ������(�T�E���h�}�l�[�W���[�Ŏg�p)
	{ "Data/BGM/challenge_to_tomorrow.wav", -1 },	// BGM Number6 ������(�T�E���h�}�l�[�W���[�Ŏg�p)
	{ "Data/BGM/battlemeeting.wav", -1 },			// BGM Number7 ������(�T�E���h�}�l�[�W���[�Ŏg�p)
	{ "Data/BGM/Heart_sound.wav", -1 },				// BGM Number8 ������(�T�E���h�}�l�[�W���[�Ŏg�p)
	{ "Data/BGM/Drum_Voice.wav", -1 },				// BGM Number9 ������(�T�E���h�}�l�[�W���[�Ŏg�p)
	{ "Data/BGM/Ranking.wav", -1 },					// BGM Number10 �����L���O�Ŏg�p����
	{ "Data/SE/explosion000.wav", 0 },				// SE Number0 ������(�T�E���h�}�l�[�W���[�Ŏg�p)
	{ "Data/SE/hit000.wav", 0 },					// SE Number1 ������(�T�E���h�}�l�[�W���[�Ŏg�p)
	{ "Data/SE/shot000.wav", 0 },					// SE Number2 ������(�T�E���h�}�l�[�W���[�Ŏg�p)
	{ "Data/SE/gameOver_SE.wav", 0 }				// SE Number3 ������(�T�E���h�}�l�[�W���[�Ŏg�p)
};

const float MAX_CONSTANT = 11.0f;						//�萔�̍ő�l
const float MIN_CONSTANT_VOLUME = 0.0f;					//���ʒ萔�̍ŏ��l
const float MIN_CONSTANT_PITCH = -11.0f;				//�����萔�̍ŏ��l
const float SOUND_PITCH = 1.0f;							//�����̏����l
const float SOUND_VOLUME = 1.0f;						//���ʂ̏����l
const float CHANGE_VOLUME = 0.002f;						//���X�ɕς�鉹�ʂ̕ύX�l
const int MAX_COUNT = 24;								//�J�E���^�[�̍ő吔
}

// ��ʂ̃p�����[�^�ݒ�ŁA�w�肵���񋓂�
// �����Ɖ��Ȃ�������G���[���N�����Ă���܂��B
static_assert(sizeof(param) / sizeof(param[0]) == CSoundWave::WAVE_MAX, "Hahaha!! Error! !rorrE !!ahahaH");


//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CSoundWave::CSoundWave()
{
	m_type = CSoundWave::WAVE_NONE;
	m_nNumber = 0;
	m_nCounter = 0;

	// �\�[�X�{�C�X�̃N���A
	memset(m_apSourceVoice,0,sizeof(m_apSourceVoice[0][0]));

	// �I�[�f�B�I�f�[�^�̃N���A
	memset(m_apDataAudio, 0, sizeof(m_apDataAudio[0]));
	
	// �I�[�f�B�I�f�[�^�T�C�Y�̃N���A
	memset(m_aSizeAudio, 0, sizeof(m_aSizeAudio[0]));

	/*�T�E���h�Đ��t���O�̃N���A*/
	for (int nFlagSound = 0; nFlagSound < CSoundWave::WAVE_MAX; nFlagSound++)
	{//�T�E���h�̍ő吔�����J��Ԃ�
		for (int nNumSound = 0; nNumSound < NUM_PLAT_MAX; nNumSound++)
		{//�T�E���h�̍ő�Đ����J��Ԃ�
			m_aPlaySound[nFlagSound][nNumSound] = false;		// �T�E���h�Đ��t���O�̃N���A
		}
	}
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CSoundWave::~CSoundWave()
{
}

//--------------------------------------
//������
//--------------------------------------
void CSoundWave::Init()
{
	HRESULT SoundEntity;			//�T�E���h�̎��̏����i�[����ϐ��̐錾

	m_type = CSoundWave::WAVE_NONE;		//�^�C�v�̏�����
	m_nVolSeter = 0;
	m_nNumber = 0;
	m_nCounter = 0;

	// XAudio2�I�u�W�F�N�g�̏��擾
	IXAudio2 *XAudeo2Obj = CSound::GetXAudioObject();

	// COM���C�u�����̏�����
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	SoundEntity = XAudio2Create(&XAudeo2Obj, 0);
	if (FAILED(SoundEntity))
	{
		// COM���C�u�����̏I������
		CoUninitialize();

		//�v���O�������~�߂�
		assert(false);		//XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s���Ă܂�
	}

	// �}�X�^�[�{�C�X�̏��擾
	IXAudio2MasteringVoice * MasterVoice = CSound::GetMasteringVoice();

	// �}�X�^�[�{�C�X�̐���
	SoundEntity = XAudeo2Obj->CreateMasteringVoice(&MasterVoice);
	if (FAILED(SoundEntity))
	{//�����Ɏ��s�����ꍇ

		if (XAudeo2Obj)
		{//�I�[�f�B�I�C���^�[�t�F�[�X�ɒl�������Ă�����
			XAudeo2Obj->Release();		// XAudio2�I�u�W�F�N�g�̊J��
			XAudeo2Obj = nullptr;		// NULL����
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		//�v���O�������~�߂�
		assert(false);		//�}�X�^�[�{�C�X�̐����Ɏ��s���Ă܂�
	}

	// �T�E���h�f�[�^�̏�����
	for (int nCntSound = 0; nCntSound < CSoundWave::WAVE_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(param[nCntSound].m_pFilename,
			GENERIC_READ,
			FILE_SHARE_READ,
			nullptr,
			OPEN_EXISTING,
			0,
			nullptr);

		if (hFile == INVALID_HANDLE_VALUE)
		{//�����Ɏ��s����
			
			//�v���O�������~�߂�
			assert(false);	//�T�E���h�f�[�^�t�@�C���̐����Ɏ��s���Ă��܂�
		}
		if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�

			/*�t�@�C���|�C���^�ƍŏ��̃|�C���^�̒l�����l = ���s������*/

			//�v���O�������~�߂�
			assert(false);	//�T�E���h�f�[�^�t�@�C���̐����Ɏ��s���Ă��܂�
		}

		// WAVE�t�@�C���̃`�F�b�N
		SoundEntity = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(SoundEntity))
		{//�t�@�C���`�F�b�N�Ɏ��s������
			//�v���O�������~�߂�
			assert(false);	//WAVE�t�@�C���`�F�b�N�Ɏ��s���Ă��܂�
		}
		SoundEntity = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(SoundEntity))
		{//�f�[�^�̓ǂݍ��݂Ɏ��s������
			//�v���O�������~�߂�
			assert(false);	//WAVE�t�@�C���̃f�[�^�Ǎ��Ɏ��s���Ă��܂�
		}
		if (dwFiletype != 'EVAW')
		{//WAVE�t�@�C���ł͂Ȃ���������
			//�v���O�������~�߂�
			assert(false);	//WAVE�t�@�C���̈ȊO��ǂݍ���ł��܂��B
		}

		// �t�H�[�}�b�g�`�F�b�N
		SoundEntity = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(SoundEntity))
		{//�t�H�[�}�b�g�̊m�F�Ɏ��s������
			 //�v���O�������~�߂�
			assert(false);	//�t�H�[�}�b�g�`�F�b�N�Ɏ��s���Ă��܂��B
		}
		SoundEntity = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(SoundEntity))
		{//�f�[�^�̓ǂݍ��݂Ɏ��s������
			//�v���O�������~�߂�
			assert(false);	//�t�H�[�}�b�g�̓ǂݍ��݂Ɏ��s���Ă��܂��B
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		SoundEntity = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(SoundEntity))
		{//�f�[�^�T�C�Y�̓ǂݍ��݂Ɏ��s������
			//�v���O�������~�߂�
			assert(false);	//�I�[�f�B�I�f�[�^�̓ǂݍ��݂Ɏ��s���Ă��܂��B
		}

		//�T�E���h�̓��I�m��
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);

		//�I�[�f�B�I�f�[�^�`�F�b�N
		SoundEntity = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(SoundEntity))
		{//�ǂݍ��݂Ɏ��s�����ꍇ
			//�v���O�������~�߂�
			assert(false);	//�I�[�f�B�I�f�[�^�`�F�b�N�Ɏ��s���Ă��܂��B
		}

		for (int i = 0; i < NUM_PLAT_MAX; i++)
		{
			// �\�[�X�{�C�X�̐���
			SoundEntity = XAudeo2Obj->CreateSourceVoice(&m_apSourceVoice[nCntSound][i], &(wfx.Format));
			if (FAILED(SoundEntity))
			{// �����Ɏ��s�����ꍇ
				// �v���O�������~�߂�
				assert(false);	// �\�[�X�{�C�X�̐����Ɏ��s���Ă��܂��B
			}

			// �I�[�f�B�I�o�b�t�@�̓o�^
			m_apSourceVoice[nCntSound][i]->SubmitSourceBuffer(&buffer);
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = param[nCntSound].m_nCountLoop;

		// �t�@�C������܂�
		CloseHandle(hFile);
	}
}

//--------------------------------------
//�I��
//--------------------------------------
void CSoundWave::Uninit()
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < CSoundWave::WAVE_MAX; nCntSound++)
	{
		for (int i = 0; i < NUM_PLAT_MAX; i++)
		{//�ő�Đ������m�F����
			if (m_apSourceVoice[nCntSound][i])
			{// �\�[�X�{�C�X�ɒl�������Ă���
				// �ꎞ��~
				m_apSourceVoice[nCntSound][i]->Stop(0);

				// �\�[�X�{�C�X�̔j��
				m_apSourceVoice[nCntSound][i]->DestroyVoice();
				m_apSourceVoice[nCntSound][i] = nullptr;

			}
		}

		// �I�[�f�B�I�f�[�^�̊J��
		free(m_apDataAudio[nCntSound]);
		m_apDataAudio[nCntSound] = nullptr;
	}

	// XAudeo�I�u�W�F�N�g�̔j��
	CSound::DestroyXAudioObject();

	// COM���C�u�����̏I������
	CoUninitialize();
}

//--------------------------------------
//�X�V
//--------------------------------------
void CSoundWave::Update()
{
	for (int nCntType = 0; nCntType < CSoundWave::WAVE_MAX; nCntType++)
	{
		for (int nCntSound = 0; nCntSound < NUM_PLAT_MAX; nCntSound++)
		{
			//XAudio�̏�Ԃ��擾����ϐ��̐錾
			XAUDIO2_VOICE_STATE xa2state;

			// ��Ԏ擾
			m_apSourceVoice[nCntType][nCntSound]->GetState(&xa2state);

			if (m_aPlaySound[nCntType][nCntSound] && xa2state.BuffersQueued == 0)
			{//�T�E���h�t���O���^�ŁA�I�[�f�B�I�̏�񂪎g�p����Ă�����

			 // �g�p���Ă��Ȃ���Ԃɂ���B
				m_aPlaySound[nCntType][nCntSound] = false;

				// �ꎞ��~
				m_apSourceVoice[nCntType][nCntSound]->Stop(0);

				// �I�[�f�B�I�o�b�t�@�̍폜
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
//�T�E���h�Đ�
//--------------------------------------
HRESULT CSoundWave::Play(WAVE_LABEL type, int numLabel)
{
	if (numLabel >= NUM_PLAT_MAX)
	{
		numLabel = 0;
	}

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[type];
	buffer.pAudioData = m_apDataAudio[type];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = param[type].m_nCountLoop;

	// �g�p����Ă����Ԃɂ���
	m_aPlaySound[type][numLabel] = true;

	// ��Ԏ擾
	m_apSourceVoice[type][numLabel]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
	 // �ꎞ��~
		m_apSourceVoice[type][numLabel]->Stop(type, numLabel);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[type][numLabel]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[type][numLabel]->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_apSourceVoice[type][numLabel]->Start(0);

	return S_OK;
}

//--------------------------------------
//���ʂ̑S�̐ݒ�
//--------------------------------------
void CSoundWave::SetVolume(WAVE_LABEL type, float fVolume)
{
	for (int i = 0; i < NUM_PLAT_MAX; i++)
	{
		m_apSourceVoice[type][i]->SetVolume(fVolume);	// �\�[�X�{�C�X���̉��ʐݒ�
		CSound::SetVolume(fVolume);						// �e���̉��ʂ�ݒ�
	}
}

//--------------------------------------
//�s�b�`�̑S�̑���
//--------------------------------------
void CSoundWave::SetRate(WAVE_LABEL type, float rate)
{
	for (int i = 0; i < NUM_PLAT_MAX; i++)
	{
		if (type == CSoundWave::WAVE_NONE)
		{
			continue;
		}
		m_apSourceVoice[type][i]->SetFrequencyRatio(rate);	// �\�[�X�{�C�X���̉����ݒ�
		CSound::SetPitch(rate);								// �e���̉��ʂ�ݒ�
	}
}

//--------------------------------------
//���ʂ̕����ݒ�
//--------------------------------------
void CSoundWave::SetPartVolume(WAVE_LABEL type, int nNumber, float fVolume)
{
	XAUDIO2_VOICE_STATE xa2state;

	if (type > CSoundWave::WAVE_MAX ||
		nNumber > NUM_PLAT_MAX)
	{
		assert(false);
	}

	// ��Ԏ擾
	m_apSourceVoice[type][nNumber]->GetState(&xa2state);

	if (xa2state.BuffersQueued == 0)
	{//�Đ����łȂ��Ȃ�
		assert(false);
	}

	m_apSourceVoice[type][nNumber]->SetVolume(fVolume);
}

//--------------------------------------
//�s�b�`�̕����ݒ�
//--------------------------------------
void CSoundWave::SetPartRate(WAVE_LABEL type, int nNumber, float rate)
{
	XAUDIO2_VOICE_STATE xa2state;

	if (type > CSoundWave::WAVE_MAX ||
		nNumber > NUM_PLAT_MAX)
	{
		assert(false);
	}

	// ��Ԏ擾
	m_apSourceVoice[type][nNumber]->GetState(&xa2state);

	if (xa2state.BuffersQueued == 0)
	{//�Đ����łȂ��Ȃ�
		assert(false);
	}

	m_apSourceVoice[type][nNumber]->SetVolume(rate);
}

//--------------------------------------
//�T�E���h��~
//--------------------------------------
void CSoundWave::Stop(WAVE_LABEL type, int nNumber)
{
	XAUDIO2_VOICE_STATE xa2state;

	if (type > CSoundWave::WAVE_MAX ||
		nNumber > NUM_PLAT_MAX)
	{
		assert(false);
	}

	// ��Ԏ擾
	m_apSourceVoice[type][nNumber]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
	 // �ꎞ��~
		m_apSourceVoice[type][nNumber]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[type][nNumber]->FlushSourceBuffers();
	}

	// �g�p����Ă����Ԃɂ���
	m_aPlaySound[type][nNumber] = false;
}

//--------------------------------------
//�S�ẴT�E���h��~
//--------------------------------------
void CSoundWave::Stop()
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < CSoundWave::WAVE_MAX; nCntSound++)
	{
		for (int i = 0; i < NUM_PLAT_MAX; i++)
		{
			if (!m_aPlaySound[nCntSound][i])
			{//�T�E���h���g�p����Ă��Ȃ��Ƃ�
				continue;		//�n�߂ɖ߂�
			}

			else if (m_apSourceVoice[nCntSound][i])
			{// �T�E���h���g�p���Ă���
				// �ꎞ��~
				m_apSourceVoice[nCntSound][i]->Stop(0);

				// �g�p����Ă��Ȃ���Ԃɂ���
				m_aPlaySound[nCntSound][i] = false;
			}
		}
	}
}

//--------------------------------------
//���ʂ��J�E���g���J�E���g����
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
//���ʂ��グ��
//--------------------------------------
void CSoundWave::UpVolumeAll(float volume)
{
	//���ʏ����擾����
	float fVol = CSound::GetVolume();

	//���ʂ����Z
	fVol += volume;

	if (fVol >= MAX_CONSTANT)
	{//���ʂ��萔�����鐔�l�ɂȂ�����
		fVol = MAX_CONSTANT;				//�萔�ɐݒ�
	}

	//���ʂ̐ݒ�
	SetVolume(m_type, fVol);
}

//--------------------------------------
//���ʂ�������
//--------------------------------------
void CSoundWave::DownVolumeAll(float volume)
{
	//���ʏ����擾����
	float fVol = CSound::GetVolume();

	//���ʂ����Z
	fVol -= volume;

	if (fVol <= MIN_CONSTANT_VOLUME)
	{//���ʂ��萔������鐔�l�ɂȂ�����
		fVol = MIN_CONSTANT_VOLUME;		//�萔�ɐݒ�
	}

	//���ʂ�ݒ�
	SetVolume(m_type, fVol);
}

//--------------------------------------
//�������グ��
//--------------------------------------
void CSoundWave::UpPitcheAll(float pitch)
{
	//���ʏ����擾����
	float fPit = CSound::GetPitch();

	//�������グ��
	fPit += pitch;

	//if (fPit >= MAX_CONSTANT)
	//{//�������萔�����鐔�l�ɂȂ�����
	//	fPit = MAX_CONSTANT;				//�萔�ɐݒ�
	//}

	//������ݒ�
	SetRate(m_type, fPit);
}

//--------------------------------------
//������������
//--------------------------------------
void CSoundWave::DownPitcheAll(float pitch)
{
	//���ʏ����擾����
	float fPit = CSound::GetPitch();

	//�����̌��Z
	fPit -= pitch;

	if (fPit <= MIN_CONSTANT_PITCH)
	{//���ʂ��萔������鐔�l�ɂȂ�����
		fPit = MIN_CONSTANT_PITCH;		//�萔�ɐݒ�
	}

	//������ݒ�
	SetRate(m_type, fPit);
}

//--------------------------------------
//�����̐���
//--------------------------------------
void CSoundWave::SlowlyUpVolume(WAVE_LABEL type, int nNumber)
{
	if (type == WAVE_LABEL::WAVE_NONE)
	{//�T�E���h���g�p����Ă��Ȃ�������
		return;			//�Ԃ�
	}

	// ���݂̉��ʂ��擾
	float ChangeVolume = CSound::GetVolume();

	m_nVolSeter++;
	
	// ���ʂ�ς���ϐ��ɑ��
	ChangeVolume = ((sinf(m_nVolSeter * CHANGE_VOLUME * D3DX_PI * 2.0f) + 1.0f) * 0.5f);

	//���ʂ̐ݒ�
	SetPartVolume(type, nNumber, ChangeVolume);
}

//--------------------------------------
//�����̐���
//--------------------------------------
void CSoundWave::SlowlyDownVolume(WAVE_LABEL type, int nNumber)
{
	if (type == WAVE_LABEL::WAVE_NONE)
	{//�T�E���h���g�p����Ă��Ȃ�������
		return;			//�Ԃ�
	}

	// ���݂̉��ʂ��擾
	float ChangeVolume = CSound::GetVolume();

	m_nVolSeter++;

	// ���ʂ�ς���ϐ��ɑ��
	ChangeVolume = ((sinf(m_nVolSeter * CHANGE_VOLUME * D3DX_PI * 2.0f) + 1.0f) * 0.5f);

	//���ʂ̐ݒ�
	SetPartVolume(type, nNumber, ChangeVolume);
}

//--------------------------------------
//���̊m�F
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
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, nullptr) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, nullptr) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, nullptr) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, nullptr, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
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
//���̓ǂݎ��
//--------------------------------------
HRESULT CSoundWave::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, nullptr) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
