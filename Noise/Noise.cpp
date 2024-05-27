#include "Noise.h"

static PF_Err
LineSwap8(ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;
	if (infoP->swapValue <= 0) return err;

	F_SRAND(infoP->swapline_seed);
	int cnt = infoP->swapValue;

	PF_Pixel* data = infoP->nfworld->data8();
	int w = infoP->nfworld->width();
	int h = infoP->nfworld->height();
	int he = F_RANDR(1, infoP->swapHeight);
	for (int i = 0; i < cnt; i++)
	{

		A_long y0 = (h-he) * F_RAND() / F_RAND_MAX;
		A_long y1 = (h-he) * F_RAND() / F_RAND_MAX;
		if (y0 == y1) continue;
		for (int y = 0; y < he; y++)
		{
			PF_Pixel* adrY0 = data + infoP->nfworld->yAdr(y + y0);
			PF_Pixel* adrY1 = data + infoP->nfworld->yAdr(y + y1);
			for (int x = 0; x < w; x++)
			{
				*adrY0 = *adrY1;
				adrY0++;
				adrY1++;
			}

		}

	}
	return err;
}


static PF_Err
Noise8(ParamInfo* infoP)
{
	PF_Err			err = PF_Err_NONE;
	if ((infoP->noisevalue <= 0) || (infoP->noiseStrong<=0)|| (infoP->noiseLength<= 0)) return err;

	int w = infoP->nfworld->width();
	int h = infoP->nfworld->height();
	int cnt = w*h;
	cnt = (int)((double)cnt * infoP->noisevalue * F_RAND_D()+0.5);
	if (cnt <= 0) return err;
	F_SRAND(infoP->noise_seed);

	PF_Pixel* data = infoP->nfworld->data8();
	for (int i = 0; i < cnt; i++)
	{
		int nl = F_RANDR(1, infoP->noiseLength);

		int x = (w - nl) * F_RAND() / F_RAND_MAX;
		int y = (h-1) * F_RAND() / F_RAND_MAX;

		double ad = PF_MAX_CHAN8 * infoP->noiseStrong;
		ad = F_RAND_D2(-ad, ad);
		if (ad != 0) {
			PF_Pixel* adr = data + infoP->nfworld->yAdr(y) + x;
			for (int x = 0; x < nl; x++)
			{
				PF_Pixel p = *adr;
				p.red = RoundByteDouble((double)p.red + ad);
				p.green = RoundByteDouble((double)p.green + ad);
				p.blue = RoundByteDouble((double)p.blue + ad);
				*adr = p;
				adr++;
			}
		}
	}
	return err;
}
static PF_Err
RGBShift8(
	void* refcon,
	A_long		xL,
	A_long		yL,
	PF_Pixel8* inP,
	PF_Pixel8* outP)
{
	PF_Err			err = PF_Err_NONE;
	RGBShiftInfo* infoP = reinterpret_cast<RGBShiftInfo*>(refcon);

	PF_Pixel rp = { 0,0,0,0 };
	PF_Pixel gp = { 0,0,0,0 };
	PF_Pixel bp = { 0,0,0,0 };

	A_u_char r = 0;
	A_u_char g = 0;
	A_u_char b = 0;
	PF_FpLong a = 0;
	rp = infoP->nfworld->GetPix8(xL - infoP->RShift, yL);
	r = rp.red;
	a = a + rp.red - a * (double)rp.red / PF_MAX_CHAN8;
	gp = infoP->nfworld->GetPix8(xL - infoP->GShift, yL);
	g = gp.green;
	a = a + gp.green - a * (double)gp.green / PF_MAX_CHAN8;
	bp = infoP->nfworld->GetPix8(xL - infoP->BShift, yL);
	b = bp.blue;
	a = a + bp.blue - a * (double)bp.blue / PF_MAX_CHAN8;

	outP->red = r;
	outP->green = g;
	outP->blue = b;
	outP->alpha = RoundByteFpLong(a);

	return err;
}
PF_Err Noise::RGBShiftExec(ParamInfo* infoP, NFWorld* src, NFWorld* dst)
{
	PF_Err err = PF_Err_NONE;
	RGBShiftInfo rgbsInfo;
	rgbsInfo.seed = infoP->rgbs.seed;
	F_SRAND(rgbsInfo.seed);
	rgbsInfo.RShift = F_RANDR(-infoP->rgbs.RShift, infoP->rgbs.RShift);
	rgbsInfo.GShift = F_RANDR(-infoP->rgbs.GShift, infoP->rgbs.GShift);
	rgbsInfo.BShift = F_RANDR(-infoP->rgbs.BShift, infoP->rgbs.BShift);
	rgbsInfo.nfworld = infoP->rgbs.nfworld;
	switch (pixelFormat())
	{
	case PF_PixelFormat_ARGB128:
		//iterate32(src->world, (void*)infoP, Blend32, dst->world);
		break;
	case PF_PixelFormat_ARGB64:
		//iterate16(src->world, (void*)infoP, Blend16, dst->world);
		break;
	case PF_PixelFormat_ARGB32:
		iterate8(src->world, (void*)&rgbsInfo, RGBShift8, dst->world);
		break;
	default:
		break;
	}
	return err;
}
// **********************************************************
PF_Err Noise::ParamsSetup(
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
	AEFX_CLR_STRUCT(def);
	//----------------------------------------------------------------
	PF_ADD_FLOAT_SLIDER(
		"globalValue",			//Name
		0,						//VALID_MIN
		1000,					//VALID_MAX
		0,						//SLIDER_MIN
		100,					//SLIDER_MAX
		100,					//CURVE_TOLERANCE
		100,					//DFLT
		1,						//PREC
		0,						//DISP
		0,						//WANT_PHASE
		ID_GLOBAL_VALUE
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_TOPIC("RGBShift", ID_TOPIC_RGBS);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(
		"rgbs_seed",	//�p�����[�^�̖��O
		-30000, 		//���l���͂���ꍇ�̍ŏ��l
		30000,			//���l���͂���ꍇ�̍ő�l
		-200,			//�X���C�_�[�̍ŏ��l
		200,			//�X���C�_�[�̍ő�l
		0,				//�f�t�H���g�̒l
		ID_RGBS_SEED
	);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(
		"RedShift",	//�p�����[�^�̖��O
		0, 		//���l���͂���ꍇ�̍ŏ��l
		30000,			//���l���͂���ꍇ�̍ő�l
		0,			//�X���C�_�[�̍ŏ��l
		200,			//�X���C�_�[�̍ő�l
		0,				//�f�t�H���g�̒l
		ID_RGBS_R
	);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(
		"GreenShift",	//�p�����[�^�̖��O
		0, 		//���l���͂���ꍇ�̍ŏ��l
		30000,			//���l���͂���ꍇ�̍ő�l
		-200,			//�X���C�_�[�̍ŏ��l
		200,			//�X���C�_�[�̍ő�l
		0,				//�f�t�H���g�̒l
		ID_RGBS_G
	);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(
		"BlueShift",	//�p�����[�^�̖��O
		-0, 		//���l���͂���ꍇ�̍ŏ��l
		30000,			//���l���͂���ꍇ�̍ő�l
		-200,			//�X���C�_�[�̍ŏ��l
		200,			//�X���C�_�[�̍ő�l
		0,				//�f�t�H���g�̒l
		ID_RGBS_B
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_END_TOPIC(ID_TOPIC_RGBS_END);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_TOPIC("swapLine", ID_TOPIC_SWAPLINE);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(
		"sw_seed",	//�p�����[�^�̖��O
		-30000, 		//���l���͂���ꍇ�̍ŏ��l
		30000,			//���l���͂���ꍇ�̍ő�l
		-200,			//�X���C�_�[�̍ŏ��l
		200,			//�X���C�_�[�̍ő�l
		0,				//�f�t�H���g�̒l
		ID_SWAPLINE_SEED
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(
		"swapValue",	//�p�����[�^�̖��O
		0, 		//���l���͂���ꍇ�̍ŏ��l
		1000,			//���l���͂���ꍇ�̍ő�l
		0,			//�X���C�_�[�̍ŏ��l
		100,			//�X���C�_�[�̍ő�l
		3,				//�f�t�H���g�̒l
		ID_SWAPVALUE
	);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(
		"swapHeight",	//�p�����[�^�̖��O
		1, 				//���l���͂���ꍇ�̍ŏ��l
		200,			//���l���͂���ꍇ�̍ő�l
		1,				//�X���C�_�[�̍ŏ��l
		100,			//�X���C�_�[�̍ő�l
		30,				//�f�t�H���g�̒l
		ID_SWAPVALUE
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_END_TOPIC(ID_TOPIC_SWAPLINE_END);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_TOPIC("noise", ID_TOPIC_NOISE);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(
		"n_seed",	//�p�����[�^�̖��O
		-30000, 		//���l���͂���ꍇ�̍ŏ��l
		30000,			//���l���͂���ꍇ�̍ő�l
		-200,			//�X���C�_�[�̍ŏ��l
		200,			//�X���C�_�[�̍ő�l
		0,				//�f�t�H���g�̒l
		ID_NOISE_SEED
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(
		"noiseValue",			//Name
		0,						//VALID_MIN
		200,					//VALID_MAX
		0,						//SLIDER_MIN
		100,					//SLIDER_MAX
		100,					//CURVE_TOLERANCE
		10,						//DFLT
		1,						//PREC
		0,						//DISP
		0,						//WANT_PHASE
		ID_NOISEVALUE
	);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(
		"noiseLength",	//�p�����[�^�̖��O
		1, 				//���l���͂���ꍇ�̍ŏ��l
		2000,			//���l���͂���ꍇ�̍ő�l
		1,				//�X���C�_�[�̍ŏ��l
		100,			//�X���C�_�[�̍ő�l
		30,				//�f�t�H���g�̒l
		ID_NOISELENGTH
	);	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(
		"noiseStrong",			//Name
		0,						//VALID_MIN
		100,					//VALID_MAX
		0,						//SLIDER_MIN
		100,					//SLIDER_MAX
		100,					//CURVE_TOLERANCE
		15,						//DFLT
		1,						//PREC
		0,						//DISP
		0,						//WANT_PHASE
		ID_NOISESTRONG
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_END_TOPIC(ID_TOPIC_NOISE_END);

//----------------------------------------------------------------
	out_data->num_params = ID_NUM_PARAMS;
	return err;
};
// **********************************************************
PF_Err	 Noise::UserChangedParam(
	PF_InData* in_dataP,
	PF_OutData* out_dataP,
	PF_ParamDef* paramsP[],
	PF_LayerDef* outputP,
	PF_UserChangedParamExtra* extraP,
	A_long pc)
{
	PF_Err err = PF_Err_NONE;
	Init(in_dataP, out_dataP, paramsP, outputP,ID_NUM_PARAMS);
	m_cmd = PF_Cmd_USER_CHANGED_PARAM;
	return err;
}

// **********************************************************
PF_Err Noise::GetParams(ParamInfo* infoP)
{
	PF_Err err = PF_Err_NONE;
	PF_FpLong gv=1;
	ERR(GetFLOAT(ID_GLOBAL_VALUE, &gv));
	if (!err) gv /= 100;

	ERR(GetADD(ID_RGBS_SEED, &infoP->rgbs.seed));
	ERR(GetADD(ID_RGBS_R, &infoP->rgbs.RShift));
	if (!err)
	{
		infoP->rgbs.RShift = (A_long)((double)infoP->rgbs.RShift * gv + 0.5);
	}
	ERR(GetADD(ID_RGBS_G, &infoP->rgbs.GShift));
	if (!err)
	{
		infoP->rgbs.GShift = (A_long)((double)infoP->rgbs.GShift * gv + 0.5);
	}
	ERR(GetADD(ID_RGBS_B, &infoP->rgbs.BShift));
	if (!err)
	{
		infoP->rgbs.BShift = (A_long)((double)infoP->rgbs.BShift * gv + 0.5);
	}

	ERR(GetADD(ID_SWAPLINE_SEED, &infoP->swapline_seed));
	ERR(GetADD(ID_SWAPVALUE, &infoP->swapValue));
	if (!err)
	{
		infoP->swapValue = (A_long)((double)infoP->swapValue * gv + 0.5);
	}
	ERR(GetADD(ID_SWAPHEIGHT, &infoP->swapHeight));


	ERR(GetADD(ID_NOISE_SEED, &infoP->noise_seed));
	ERR(GetFLOAT(ID_NOISEVALUE, &infoP->noisevalue));
	if (!err)
	{
		infoP->noisevalue /= 100;
		infoP->noisevalue *= gv;
	}
	ERR(GetADD(ID_NOISELENGTH, &infoP->noiseLength));
	ERR(GetFLOAT(ID_NOISESTRONG, &infoP->noiseStrong));
	if (!err) infoP->noiseStrong /= 100;
	return err;
};
// **********************************************************
PF_Err Noise::Exec(ParamInfo* infoP)
{
	PF_Err err = PF_Err_NONE;
	PF_Err err2 = PF_Err_NONE;
	NFWorld* src = new NFWorld(input, in_data, pixelFormat());
	NFWorld* dst = new NFWorld(output, in_data, pixelFormat());
	dst->Copy(src);
	infoP->nfworld = dst;
	infoP->rgbs.nfworld = src;
	switch (pixelFormat())
	{
	case PF_PixelFormat_ARGB128:
		//iterate32(src->world, (void*)infoP, Blend32, dst->world);
		break;
	case PF_PixelFormat_ARGB64:
		//iterate16(src->world, (void*)infoP, Blend16, dst->world);
		break;
	case PF_PixelFormat_ARGB32:
		//iterate8(src->world, (void*)infoP, Noise8, dst->world);
		RGBShiftExec(infoP, src, dst);
		LineSwap8(infoP);
		Noise8(infoP);
		break;
	default:
		break;
	}
	/*
	PF_ParamDef			checkout;
	PF_ChannelDesc		desc;
	PF_ChannelRef		ref;
	PF_ChannelChunk		chunk;
	PF_Boolean			found_depthPB;
	int32_t				num_channelsL = 0;
	PF_Rect				rect = { 0,0,100,100 };
	PF_Rect				rect2 = { 0,0,100,100 };
	
	ERR(PF_CHECKOUT_PARAM(in_data,
		ID_LAYER,
		(in_data->current_time),
		in_data->time_step,
		in_data->time_scale,
		&checkout));
	if (checkout.u.ld.data) {
		rect.left = 0;
		rect.top = 0;
		rect.right = rect.left + checkout.u.ld.width;
		rect.bottom = rect.top + checkout.u.ld.height;

		rect2.left = infoP->pointValue.x / 66636;
		rect2.top = infoP->pointValue.y / 66636;
		rect2.right = rect2.left + checkout.u.ld.width;
		rect2.bottom= rect2.top + checkout.u.ld.height;
		ERR(PF_COPY(&checkout.u.ld,
			dst->world,
			&rect,
			&rect2));
	}
	ERR2(PF_CHECKIN_PARAM(in_data, &checkout));		// ALWAYS check in,
	*/
	delete src;
	delete dst;

	return err;

};
// **********************************************************
