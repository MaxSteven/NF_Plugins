
#pragma once
#ifndef NF_TARGET_H
#define NF_TARGET_H

#include "../_NFLib/NFLibVersion.h"
#include "../_NFLib/NF_CATEGORY.h"


//-----------------------------------------------------------------------------------
//�v���O�C���̎��ʂɎg���閼�O
#define NF_NAME			"NF-SpatteringRect"
#define NF_MATCHNAME	"NF-SpatteringRect"


//-----------------------------------------------------------------------------------
//�v���O�C���̐����Ɏg���镶��
#define NF_DESCRIPTION	"NF_Plugins SpatteringRect"

	//-----------------------------------------------------------------------------------
	//�v���O�C�����\������郁�j���[��

/*
#define NFP_CATEGORY_CHANNLE "NFP-Avior_Channel"
#define NFP_CATEGORY_BETA "NFP-Avior(Beta)"
*/
//#define NF_CATEGORY NFP_CATEGORY_CHANNLE
#define NF_CATEGORY NFP_CATEGORY_BETA


//�o�[�W�����𔃂���AlphaFixPiPL.r��AE_Effect_Version���ς��邱��
#define	MAJOR_VERSION		1
#define	MINOR_VERSION		0
#define	BUG_VERSION			0
#define	STAGE_VERSION		PF_Stage_DEVELOP
//#define	STAGE_VERSION		PF_Stage_ALPHA
//#define	STAGE_VERSION		PF_Stage_BETA
//#define	STAGE_VERSION		PF_Stage_RELEASE
#define	BUILD_VERSION		0

//��̒l���v�Z��������
#define NF_VERSION	524288


//-----------------------------------------------------------

#define SUPPORT_SMARTFX			//�����L���ɂ����SmartFX+Float_Color�ɑΉ�����


//-----------------------------------------------------------------------------------
//out_flags
/*
out_data->out_flags
	PF_OutFlag_PIX_INDEPENDENT		1024
	PF_OutFlag_NON_PARAM_VARY			4
	PF_OutFlag_DEEP_COLOR_AWARE		33554432
	PF_OutFlag_USE_OUTPUT_EXTENT	64
	PF_OutFlag_I_EXPAND_BUFFER		512
	PF_OutFlag_I_DO_DIALOG				32
	PF_OutFlag_WIDE_TIME_INPUT |
	//PF_OutFlag_I_DO_DIALOG;
*/

#define NF_OUT_FLAGS	33556034	//�ʏ�͂�����
//#define NF_OUT_FLAGS	33556038	//��������L���ɂ���Ɩ��t���[�����Ƃɕ`�悷��BNON_PARAM_VARY�𓮍쒆�ɐ؂�ւ���Ƃ����������
//#define NF_OUT_FLAGS	1604		//8bit�̂�
//#define NF_OUT_FLAGS	1606		//8bit�̂� 

//-----------------------------------------------------------------------------------
/*
out_data->out_flags2
	PF_OutFlag2_FLOAT_COLOR_AWARE
	PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG
	PF_OutFlag2_SUPPORTS_SMART_RENDER
	PF_OutFlag2_SUPPORTS_QUERY_DYNAMIC_FLAGS
	PF_OutFlag2_DOESNT_NEED_EMPTY_PIXELS;
	PF_OutFlag2_SUPPORTS_THREADED_RENDERING
*/
#if defined(SUPPORT_SMARTFX)
#define NF_OUT_FLAGS2 134222921
#else
#define NF_OUT_FLAGS2 134217801
#endif

//-----------------------------------------------------------------------------------
#endif
