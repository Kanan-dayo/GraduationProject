//*************************************************************************************************************
//
// �^�u���b�g���� [tablet.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _TABLET_H_
#define _TABLET_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "sceneX.h"
#include "Mylibrary.h"

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CTabletButton;
class CTablet : public CSceneX
{
public:
	/* �񋓌^��` */
	typedef enum
	{
		MODE_NONE = -1,
		MODE_NORMAL,
		MODE_MOVEING,
		MODE_MAX
	} MODE;
	enum
	{
		POS_NONE = -1,	
		POS_TABLET,
		POS_PEN,
		POS_ERASER,
		POS_SEND,
		POS_MAX,
	};

	/* �����o�֐� */
	CTablet();																								// �R���X�g���N�^
	~CTablet();																								// �f�X�g���N�^

	static HRESULT       Load(void);																		// �ǂݍ���
	static HRESULT          LoadError(void);																				// �G���[�̌��o

	HRESULT              Init();																			// ������
	void                 Update();																			// �X�V
	void                 Draw();																			// �`��
	inline void          ShowDebugInfo() {};																// �f�o�b�O���\�L

	bool                 ItIsPressingButtons(void);															// �{�^���������Ă��邩

	void                 InitMemberVariables(void);															// �����o�ϐ��̏�����
	void                 NormalProc(void);																	// �ʏ폈��
	void                 MoveingProc(void);																	// �ړ�����
	void                 ConstantVelocityProc(void);														// ��������
	void                 NonConstantVelocityProc(void);														// �s��������

	// ����
	static std::shared_ptr<CTablet> Create(void);											// ����

	// �ݒ�֐�
	inline void          SetMoveCoeff(const float fMoveCoeff) { m_fMoveCoeff = fMoveCoeff; }				// �ړ��W���̐ݒ�
	inline void          SetPosDest(CONST D3DXVECTOR3 &posDest) { m_posDest = posDest; }					// �ړI�n�̐ݒ�
	inline void          SetMode(CONST MODE mode) { m_mode = mode; }										// ���[�h�̐ݒ�
	inline void          SetConstVelocity(const bool bConstVelocity) { m_bConstVelocity = bConstVelocity; }	// �����t���O�̐ݒ�
	inline void          SetMove(CONST D3DXVECTOR3& move) { m_move = move; }								// �ړ��ʂ̐ݒ�
	inline void          SetDestFrame(const int nDestFrame) { m_nDestFrame = nDestFrame; }					// �ړI�n�܂ł̃t���[���̐ݒ�

	void                 SetConstVelocityProc(const bool bConstVelocity, const int nDestFrame);				// ���������̐ݒ�i�ړI�n��ݒ肷��O�j
	void                 SetDestinationProc(CONST D3DXVECTOR3 &posDest);									// �ړI�n��ݒ肷�鏈��

	// �擾�֐�
	inline float &       GetMoveCoeff(void) { return m_fMoveCoeff; }										// �ړ��W���̎擾
	inline D3DXVECTOR3 & GetPosDest(void) { return m_posDest; }												// �ړI�n�̎擾
	inline MODE &        GetMode(void) { return m_mode; }													// ���[�h�̎擾
	inline bool &        GetConstVelocity(void) { return m_bConstVelocity; }								// �����t���O�̎擾
	inline VEC3 &        GetMove(void) { return m_move; }													// ���[�h�̎擾
	inline int &         GetDestFrame(void) { return m_nDestFrame; }										// �ړI�n�܂ł̃t���[���̎擾

private:
	/* �����o�֐� */
	static void          ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData);
	static void          SetFromString(CONST_STRING str);


	/* �����o�ϐ� */
	MyVector<std::shared_ptr<CTabletButton>> m_Button;														// �{�^���̃|�C���^
	static D3DXVECTOR3                       m_aSetingPos[POS_MAX];											// �ݒ�p�̈ʒu
	static float                             m_fMoveCoeff;													// �ړ��W��
	D3DXVECTOR3                              m_posDest;														// �ړI�n
	MODE                                     m_mode;														// ���[�h
	bool                                     m_bConstVelocity;												// �����t���O
	VEC3                                     m_move;														// �ړ���
	int                                      m_nDestFrame;													// �ړI�n�܂ł̃t���[��
	int                                      m_nCntFrame;													// �t���[�����̃J�E���g
};

#endif