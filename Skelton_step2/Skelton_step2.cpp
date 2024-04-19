#include "Skelton_step2.h"
// **********************************************************

static PF_Err
Shift8(
	void* refcon,
	A_long		xL,
	A_long		yL,
	PF_Pixel8* inP,
	PF_Pixel8* outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo* infoP = reinterpret_cast<ParamInfo*>(refcon);

	A_long w = infoP->inWld->width();
	A_long h = infoP->inWld->height();
	A_long nx = (xL - infoP->shiftXPx) % w;
	if (nx < 0) nx += w;
	A_long ny = (yL - infoP->shiftYPx) % h;
	if (ny < 0) ny += h;
	*outP = infoP->inWld->GetPix8(nx, ny);
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
Shift16(
	void* refcon,
	A_long		xL,
	A_long		yL,
	PF_Pixel16* inP,
	PF_Pixel16* outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo* infoP = reinterpret_cast<ParamInfo*>(refcon);

	A_long w = infoP->inWld->width();
	A_long h = infoP->inWld->height();
	A_long nx = (xL - infoP->shiftXPx) % w;
	if (nx < 0) nx += w;
	A_long ny = (yL - infoP->shiftYPx) % h;
	if (ny < 0) ny += h;
	*outP = infoP->inWld->GetPix16(nx, ny);

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
Shift32(
	void* refcon,
	A_long		xL,
	A_long		yL,
	PF_PixelFloat* inP,
	PF_PixelFloat* outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo* infoP = reinterpret_cast<ParamInfo*>(refcon);

	A_long w = infoP->inWld->width();
	A_long h = infoP->inWld->height();
	A_long nx = (xL - infoP->shiftXPx) % w;
	if (nx < 0) nx += w;
	A_long ny = (yL - infoP->shiftYPx) % h;
	if (ny < 0) ny += h;
	*outP = infoP->inWld->GetPix32(nx, ny);
	return err;
}
// **********************************************************
PF_Err Skelton_step2::ParamsSetup(
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
	PF_ADD_FLOAT_SLIDER(
		"shiftX(%)",				//Name
		-30000,					//VALID_MIN
		30000,					//VALID_MAX
		-200,						//SLIDER_MIN
		200,				//SLIDER_MAX
		1,						//CURVE_TOLERANCE
		0,						//DFLT
		1,						//PREC
		0,						//DISP
		0,						//WANT_PHASE
		ID_SHIFTX
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(
		"shiftY(%)",				//Name
		-30000,					//VALID_MIN
		30000,					//VALID_MAX
		-200,						//SLIDER_MIN
		200,				//SLIDER_MAX
		1,						//CURVE_TOLERANCE
		0,						//DFLT
		1,						//PREC
		0,						//DISP
		0,						//WANT_PHASE
		ID_SHIFTY
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
PF_Err Skelton_step2::GetParams(ParamInfo* infoP)
{
	PF_Err err = PF_Err_NONE;
	ERR(GetFLOAT(ID_SHIFTX, &infoP->shiftX));
	if (!err){infoP->shiftX /= 100;}
	ERR(GetFLOAT(ID_SHIFTY, &infoP->shiftY));
	if (!err) { infoP->shiftY /= 100; }

	ERR(GetCOLOR(ID_COLOR, &infoP->color));
	ERR(GetADD(ID_INT, &infoP->intValue));
	ERR(GetFIXED(ID_FIXED, &infoP->fixedValue));
	ERR(GetFLOAT(ID_FLOAT, &infoP->floatvalue));
	ERR(GetFLOAT(ID_FLOAT, &infoP->floatvalue));
	ERR(GetCHECKBOX(ID_CHECK, &infoP->check));
	ERR(GetPOPUP(ID_POPUP, &infoP->popupValue));
	ERR(GetPOINT_FIXED(ID_POINT, &infoP->pointValue));
	ERR(GetPOINT3D(ID_POINT, &infoP->point3DValue));

	return err;
};
// **********************************************************
PF_Err Skelton_step2::Exec(ParamInfo* infoP)
{
	PF_Err err = PF_Err_NONE;
	NFWorld* src = new NFWorld(input, in_data, pixelFormat());
	NFWorld* dst = new NFWorld(output, in_data, pixelFormat());
	dst->Copy(src);
	if ((infoP->shiftX != 0)|| (infoP->shiftY != 0)) {
		//init_xorShift(frame()); // �����̏�����
		//���ۂɓ������s�N�Z�������v�Z
		infoP->shiftXPx = (A_long)(infoP->shiftX * (PF_FpLong)(src->width()) + 0.5);
		infoP->shiftYPx = (A_long)(infoP->shiftY * (PF_FpLong)(src->height()) + 0.5);
		//�摜��o�^
		infoP->inWld = src;
		infoP->outWld = dst;

		switch (pixelFormat())
		{
		case PF_PixelFormat_ARGB128:
			iterate32(src->world, (void*)infoP, Shift32, dst->world);
			break;
		case PF_PixelFormat_ARGB64:
			iterate16(src->world, (void*)infoP, Shift16, dst->world);
			break;
		case PF_PixelFormat_ARGB32:
			iterate8(src->world, (void*)infoP, Shift8, dst->world);
			break;
		default:
			break;
		}
	}


	delete src;
	delete dst;

	return err;

};
// **********************************************************
