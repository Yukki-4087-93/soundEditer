//---------------------------------------------------------
//
//�T�E���h
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _SOUNDWAVE_H_
#define _SOUNDWAVE_H_

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include"d3dx9.h"
#include "sound.h"

//--------------------------------------
//�萔��`
//--------------------------------------
const int NUM_PLAT_MAX = 24;				//�T�E���h���Đ�����ő吔

//--------------------------------------
//�N���X��`
//�T�E���h�֘A
//--------------------------------------
class CSoundWave : public CSound
{
public:

	enum WAVE_LABEL
	{
		WAVE_NONE = -1,									// �g�p����Ă��Ȃ����
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

	CSoundWave();												// �R���X�g���N�^
	~CSoundWave();												// �f�X�g���N�^
	void Init() override;										// ������
	void Uninit() override;										// �I��
	void Update() override;										// �X�V

	HRESULT Play(WAVE_LABEL type,int numLabel);							// �Đ�
	void SetVolume(WAVE_LABEL type, float fVolume);						// ����
	void SetRate(WAVE_LABEL type, float rate);							// �s�b�`����
	void SetPartVolume(WAVE_LABEL type, int nNumber, float fVolume);	// ���ʂ̕����ݒ�
	void SetPartRate(WAVE_LABEL type, int nNumber, float rate);			// �s�b�`�̕����ݒ�
	void Stop(WAVE_LABEL type, int nNumber);							// �ꕔ��~
	void Stop();														// �S��~
	void SetCounter();
	int GetCpounter() { return m_nCounter; }

public:
	void UpVolumeAll(float volume);			// ���ʂ��グ�����Ƃ��Ɏg��
	void DownVolumeAll(float volume);			// ���ʂ����������Ƃ��Ɏg��
	void UpPitcheAll(float pitch);				// �������グ�����Ƃ��Ɏg��
	void DownPitcheAll(float pitch);			// ���������������Ƃ��Ɏg��
	void SetType(WAVE_LABEL type) { m_type = type; }	// �^�C�v��ݒ肷��
	void SlowlyUpVolume(WAVE_LABEL type,int nNumber);				// �ɂ₩�ɉ��ʂ��グ��
	void SlowlyDownVolume(WAVE_LABEL type, int nNumber);			// �ɂ₩�ɉ��ʂ�������

public:
	HRESULT CheckChunk(HANDLE hFile,						//���(�`�����N)�̊m�F
		DWORD format,
		DWORD *pChunkSize,
		DWORD *pChunkDataPosition);


	HRESULT ReadChunkData(HANDLE hFile,						//���(�`�����N)�̓ǂݍ���
		void *pBuffer,
		DWORD dwBuffersize,
		DWORD dwBufferoffset);

private:
	IXAudio2SourceVoice *m_apSourceVoice[WAVE_MAX][NUM_PLAT_MAX];		// �\�[�X�{�C�X
	BYTE *m_apDataAudio[WAVE_MAX];										// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[WAVE_MAX];										// �I�[�f�B�I�f�[�^�T�C�Y
	bool m_aPlaySound[WAVE_MAX][NUM_PLAT_MAX];							// �T�E���h�Đ��t���O
	WAVE_LABEL m_type;													// �T�E���h�̃^�C�v
	int m_nVolSeter;													// �ɂ₩�ɃT�E���h�������鎞�Ɏg�p����
	int m_nNumber;														// �i���o�[��������ϐ�
	int m_nCounter;

};

#endif // !_SOUNDWAVE_H_
