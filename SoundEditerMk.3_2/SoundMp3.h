////---------------------------------------------------------
////
////�T�E���hMP3
////Author::TAKANO
////
////---------------------------------------------------------
//#ifndef _SOUNDMP3_H_
//#define _SOUNDMP3_H_
//
////--------------------------------------
////�C���N���[�h�t�@�C��
////--------------------------------------
//#include "d3dx9.h"
//#include "sound.h"
//#include <dshow.h>
//#pragma comment(lib,"strmiids.lib")
//
////--------------------------------------
////�N���X��`
////�T�E���h�֘A
////--------------------------------------
//class CSoundMp3 : public CSound
//{
//public:
//
//	enum NUM_MP3
//	{
//		MP3_NONE = -1,									// �g�p����Ă��Ȃ����
//		MP3_BGM_BATTLEBAN = 0,							// BGM 0
//		MP3_MAX
//	};
//
//	CSoundMp3();												// �R���X�g���N�^
//	~CSoundMp3();												// �f�X�g���N�^
//	void Init() override;										// ������
//	void Uninit() override;										// �I��
//	void Update() override;										// �X�V
//
//	HRESULT Play();							// �Đ�
//	void Stop();								// �ꕔ��~
//
//public:
//	
//
//public:
//	//HRESULT CheckChunk(HANDLE hFile,						//���(�`�����N)�̊m�F
//	//	DWORD format,
//	//	DWORD *pChunkSize,
//	//	DWORD *pChunkDataPosition);
//
//
//	//HRESULT ReadChunkData(HANDLE hFile,						//���(�`�����N)�̓ǂݍ���
//	//	void *pBuffer,
//	//	DWORD dwBuffersize,
//	//	DWORD dwBufferoffset);
//
//private:
//	//IXAudio2SourceVoice *m_apSourceVoice[CSoundMp3::MP3_MAX];			// �\�[�X�{�C�X
//	//BYTE *m_apDataAudio[CSoundMp3::MP3_MAX];										// �I�[�f�B�I�f�[�^
//	//DWORD m_aSizeAudio[CSoundMp3::MP3_MAX];										// �I�[�f�B�I�f�[�^�T�C�Y
//	//bool m_aPlaySound[CSoundMp3::MP3_MAX];								// �T�E���h�Đ��t���O
//	IGraphBuilder* m_pCreatSound;	// 
//	IMediaControl* m_pPlaySound;	//
//	IMediaSeeking* m_pLoop;			//
//	IBaseFilter* m_pMpObject;		//
//	IPin* m_pOutputMp3;
//	NUM_MP3 m_type;
//};
//
//#endif // !_SOUNDMP3_H_
