
#include "AEConfig.h"
#include "AE_EffectVers.h"

#ifndef AE_OS_WIN
	#include "AE_General.r"
#endif

#include "NF_Target.h"

resource 'PiPL' (16000) {
	{	/* array properties: 12 elements */
		/* [1] */
		Kind {
			AEEffect
		},
		/* [2] */
		Name {
			/*AE�̃��j���[�Ɏg���� */
			NF_NAME
		},
		/* [3] */
		Category {
			/*AE�̃��j���[�Ɏg���� */
			NF_CATEGORY
		},
		
#ifdef AE_OS_WIN
	#ifdef AE_PROC_INTELx64
		CodeWin64X86 {"EffectMain"},
	#endif	
#else
	#ifdef AE_OS_MAC
		CodeMacIntel64 {"EffectMain"},
	#endif
#endif
		/* [6] */
		AE_PiPL_Version {
			2,
			0
		},
		/* [7] */
		AE_Effect_Spec_Version {
			PF_PLUG_IN_VERSION,
			PF_PLUG_IN_SUBVERS
		},
		/* [8] */
		AE_Effect_Version {
			/* v1.00 */
			NF_VERSION 
		},
		/* [9] */
		AE_Effect_Info_Flags {
			0
		},
		/* [10] */
		AE_Effect_Global_OutFlags {
			NF_OUT_FLAGS
		},
		AE_Effect_Global_OutFlags_2 {
			NF_OUT_FLAGS2
		},

		/* [11] */
		AE_Effect_Match_Name {
			/*�v���O�C���̎��ʂɎg���� */
			NF_MATCHNAME
		},
		/* [12] */
		AE_Reserved_Info {
			0
		}
	}
};

