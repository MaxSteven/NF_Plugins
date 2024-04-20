#include "Skelton.h"


// **********************************************************
PF_Err Skelton::ParamsSetup(
	PF_InData* in_dataP,
	PF_OutData* out_dataP,
	PF_ParamDef* paramsP[],
	PF_LayerDef* outputP)
{
	PF_Err err = PF_Err_NONE;
	Init();
	m_cmd = PF_Cmd_PARAMS_SETUP;
	in_data = in_dataP;
	out_data = out_dataP;
	PF_ParamDef		def;
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_POPUP(
		"TargetMode",
		3,	//���j���[�̐�
		2,	//�f�t�H���g
		"FullScreen|AlphaOn|TargetColor|",
		ID_TARGET_MODE
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR("TargetColor",
		0xFF,
		0xFF,
		0xFF,
		ID_TARGET_COLOR
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_POPUP(
		"TargetMode",
		5,	//���j���[�̐�
		1,	//�f�t�H���g
		"Normal|Add|Multiply|Screen|Overlay",
		ID_BLEND_MODE
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR("BlendColor",
		0xFF,
		0x80,
		0x00,
		ID_BLEND_COLOR
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(
		"BlendOpacity",			//Name
		0,						//VALID_MIN
		100,					//VALID_MAX
		0,						//SLIDER_MIN
		100,					//SLIDER_MAX
		100,					//CURVE_TOLERANCE
		100,						//DFLT
		1,						//PREC
		0,						//DISP
		0,						//WANT_PHASE
		ID_BLEND_OPACITY
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_START_COLLAPSED;	//���������ƕ\�����ɊJ������ԂɂȂ�
	PF_ADD_TOPIC("Topic", ID_TOPIC);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//���������ƃL�[�t���[�������ĂȂ��Ȃ�
	PF_ADD_COLOR("Color",
		0xFF,
		0xFF,
		0xFF,
		ID_COLOR
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(
		"Int",			//�p�����[�^�̖��O
		-30000, 		//���l���͂���ꍇ�̍ŏ��l
		30000,			//���l���͂���ꍇ�̍ő�l
		0,				//�X���C�_�[�̍ŏ��l
		300,			//�X���C�_�[�̍ő�l
		10,				//�f�t�H���g�̒l
		ID_INT
	);		
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//���������ƃL�[�t���[�������ĂȂ��Ȃ�
	PF_ADD_FIXED(
		"Fiexed",		//�p�����[�^�̖��O
		0, 				//���l���͂���ꍇ�̍ŏ��l
		100,			//���l���͂���ꍇ�̍ő�l
		0,				//�X���C�_�[�̍ŏ��l
		100,			//�X���C�_�[�̍ő�l
		100,			//�f�t�H���g�̒l
		1,				//���l�\���Ɋւ���t���O
		0,
		0,
		ID_FIXED
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(
		"float",				//Name
		0,						//VALID_MIN
		400,					//VALID_MAX
		0,						//SLIDER_MIN
		200,					//SLIDER_MAX
		1,						//CURVE_TOLERANCE
		0,						//DFLT
		1,						//PREC
		0,						//DISP
		0,						//WANT_PHASE
		ID_FLOAT
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(
		"Check",
		"on",
		FALSE,
		0,
		ID_CHECK
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	def.flags = PF_ParamFlag_CANNOT_INTERP;	//�L�[�t���[���̎����ۊǂ��~����
	PF_ADD_ANGLE(
		"Angle", 
		45, 
		ID_ANGLE);
	//----------------------------------------------------------------
	//�|�b�v�A�b�v���j���[
	AEFX_CLR_STRUCT(def);
	def.flags = PF_ParamFlag_CANNOT_INTERP;	//�L�[�t���[���̎����ۊǂ��~����
	PF_ADD_POPUP(
		"Popup",
		5,	//���j���[�̐�
		1,	//�f�t�H���g
		"AAA|BBB|CCC|DDD|EEE",
		ID_POPUP
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_POINT(
		"Point",			//"New Center"
		50,	// X
		50,	// Y
		0,	// Flag
		ID_POINT
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_POINT_3D(
		"Point3D",			//"New Center"
		50,	// X
		50,	// Y
		50, // Z
		ID_POINT3D
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_END_TOPIC(ID_TOPICEND);
					
//----------------------------------------------------------------
	out_data->num_params = ID_NUM_PARAMS;
	return err;
};
// **********************************************************
PF_Err Skelton::GetParams(ParamInfo* infoP)
{
	PF_Err err = PF_Err_NONE;
	ERR(GetPOPUP(ID_TARGET_MODE, &infoP->targetMode));
	ERR(GetCOLOR(ID_TARGET_COLOR, &infoP->targetColor));
	ERR(GetPOPUP(ID_BLEND_MODE, &infoP->blendMode));
	ERR(GetCOLOR(ID_BLEND_COLOR, &infoP->blendColor));
	ERR(GetFLOAT(ID_BLEND_OPACITY, &infoP->blendOpacity));
	if (!err) infoP->blendOpacity /= 100;

	/*
	ERR(GetCOLOR(ID_COLOR, &infoP->color));
	ERR(GetADD(ID_INT, &infoP->intValue));
	ERR(GetFIXED(ID_FIXED, &infoP->fixedValue));
	ERR(GetFLOAT(ID_FLOAT, &infoP->floatvalue));
	ERR(GetFLOAT(ID_FLOAT, &infoP->floatvalue));
	ERR(GetCHECKBOX(ID_CHECK, &infoP->check));
	ERR(GetPOPUP(ID_POPUP, &infoP->popupValue));
	ERR(GetPOINT_FIXED(ID_POINT, &infoP->pointValue));
	ERR(GetPOINT3D(ID_POINT, &infoP->point3DValue));
	*/
	return err;
};
// **********************************************************
PF_Err Skelton::Exec(ParamInfo* infoP)
{
	PF_Err err = PF_Err_NONE;
	NFWorld* src = new NFWorld(input, in_data, pixelFormat());
	NFWorld* dst = new NFWorld(output, in_data, pixelFormat());
	if (infoP->blendOpacity != 0) {
		TargetExec(infoP, src, dst);
		BlendExec(infoP, src, dst);
	}
	else {
		dst->Copy(src);
	}


	delete src;
	delete dst;

	return err;

};
// **********************************************************
