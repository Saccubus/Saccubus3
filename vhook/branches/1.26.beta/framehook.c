/*�t���[���t�b�N�̑�������邽�ߐ�p*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include "common/framehook_ext.h"
#include "framehook.h"
#include "main.h"
#include "mydef.h"
#include "nicodef.h"
#include "util.h"

typedef struct ContextInfo{
	FILE* log;
	DATA data;
} ContextInfo;

/*
 * �K�v�Ȋ֐��ЂƂ߁B�ŏ��ɌĂ΂���I
 *
 */
int init_setting(FILE*log,const toolbox *tbox,SETTING* setting,int argc, char *argv[]);

__declspec(dllexport) int ExtConfigure(void **ctxp,const toolbox *tbox, int argc, char *argv[]){
	int i;
	//���O
	FILE* log = fopen("[log]vhext.txt", "w");
	if(log == NULL){
		puts("[framehook/init]failed to open logfile.\n");
		fflush(log);
		return -1;
	}else{
		fputs("[framehook/init]initializing..\n",log);
		fflush(log);
	}
	//�K�v�Ȑݒ肪���邩�̊m�F
	fprintf(log,"[framehook/init]called with argc = %d\n",argc);
	fflush(log);
	for(i=0;i<argc;i++){
		fprintf(log,"[framehook/init]arg[%2d] = %s\n",i,argv[i]);
		fflush(log);
	}
	//�Z�b�e�B���O�擾�B
	SETTING setting;
	if(init_setting(log,tbox,&setting,argc,argv)){
		fputs("[framehook/init]initialized settings.\n",log);
		fflush(log);
	}else{
		fputs("[framehook/init]failed to initialize settings.\n",log);
		fflush(log);
		return -2;
	}
	//���C�u�����Ȃǂ̏�����
	if(init(log)){
		fputs("[framehook/init]initialized libs.\n",log);
		fflush(log);
	}else{
		fputs("[framehook/init]failed to initialize libs.\n",log);
		fflush(log);
		return -3;
	}
	/*�R���e�L�X�g�̐ݒ�*/
	*ctxp = malloc(sizeof(ContextInfo));
	if(*ctxp == NULL){
		fputs("[framehook/init]failed to malloc for context.\n",log);
		fflush(log);
		return -5;
	}
	ContextInfo* ci = (ContextInfo*)*ctxp;
	memset(ci, (int)NULL, sizeof(ContextInfo));
	ci->log = log;
	fflush(log);
	if(initData(&ci->data,log,&setting)){
		fputs("[framehook/init]initialized context.\n",log);
		fputs("[framehook/init]initialized.\n",log);
		fflush(log);
		return 0;
	}else{
		fputs("[framehook/init]failed to initialize context.\n",log);
		fflush(log);
		return -4;
	}
}
/*
 * �����ł̂݌Ă΂��B
 */

/*
	FILE* log		:���O�t�@�C�� opened as "w"
	toolbox* tbox	:ffmpeg interface?
	SETTING* setting:�ݒ�f�[�^�\�� �o��
	int argc		: argv[] size
	argv[0]:�v���O����
	argv[1]:vhook
	argv[2]:�t�H���g
	argv[3]:�t�H���g�C���f�b�N�X
	argv[4]:����
	argv[5]:�e�̎��
	�ȍ~�I�v�V����
	--enable-show-video�F�`�撆�ɓ����������B
	--enable-fontsize-fix�F�t�H���g�T�C�Y�������Œ�������B
	--nico-width-wide : ���C�h�v���[���[16:9�Ή�
	--font-height-fix-ratio:%d �F �t�H���g���������ύX�̔{���i���j+ int
	--disable-original-resize : ������΂��Ǝ����T�C�Y�𖳌��ɂ���i�����I�j
*/

int init_setting(FILE*log,const toolbox *tbox,SETTING* setting,int argc, char *argv[]){
	/* TOOLBOX�̃o�[�W�����`�F�b�N */
	if (tbox->version != TOOLBOX_VERSION){
		fprintf(log,"[framehook/init]TOOLBOX version(%d) is not %d.\n", tbox->version, TOOLBOX_VERSION);
		fflush(log);
		return FALSE;
	}
	/*video�̒��� VPOS_FACTOR�ŃX�P�[�� */
	setting->video_length = (tbox->video_length * VPOS_FACTOR);
	if (setting->video_length<=0){
		fprintf(log,"[framehook/init]video_length is less or equals 0.\n");
		fflush(log);
//		return FALSE;
	}
	/*�ȍ~�I�v�V����*/

	//�R�����g�������邩�ۂ��H
	setting->enable_user_comment = FALSE;
	setting->enable_owner_comment = FALSE;
	setting->enable_optional_comment = FALSE;
	setting->data_user_path = NULL;
	setting->data_owner_path = NULL;
	setting->data_optional_path = NULL;
	//��ʓI�Ȑݒ�
	setting->font_path = NULL;
	setting->font_index = 0;
	setting->user_slot_max = 30;	// 40 ?
	setting->optional_slot_max = 30;
	setting->owner_slot_max = 30;	// infinite ?
	setting->shadow_kind = 1;//�f�t�H���g�̓j�R�j�R���敗
	setting->show_video = FALSE;
	setting->fontsize_fix=FALSE;
	setting->opaque_comment=FALSE;
	setting->nico_width_now=NICO_WIDTH;	//�f�t�H���g�͋��v���C���[��
	setting->optional_trunslucent=FALSE;	//�f�t�H���g�͔������ɂ��Ȃ�
	setting->font_h_fix_r = 100;	//�f�t�H���g4:3�͏]���ʂ�i�ŏI�����ō��킹�邱�Ɓj
	setting->font_h_fix_r_wide = 100;	//�f�t�H���g16:9�͏]���ʂ�i�ŏI�����ō��킹�邱�Ɓj
	setting->original_resize = TRUE;	//�f�t�H���g�͗L���i�����I�ɖ����ɂ���I�����s���j
	setting->limitwidth_resize = TRUE;
	setting->linefeed_resize = TRUE;
	setting->double_resize = TRUE;
	setting->font_double_scale = TRUE;	// �t�H���g���`�̎����C�����L���i�f�t�H���g2�{�̎��`�j
	// �ՊE���͓��{���̓����512�`600px ���悪�A4:3 or 16:9�ɖ��֌W
	// �A���Afull�R�}���h�ł�640�`680px
	// �X�ɕ����T�C�Y�ɂ���Ă��قȂ�i�������Ȃ��j
	setting->nico_limit_width = NICO_WIDTH;
	setting->nico_limit_width_full = NICO_WIDTH_WIDE;
	setting->nico_limit_height = NICO_HEIGHT;
	setting->nico_limit_height_wide = NICO_HEIGHT;
	setting->fixed_font_size[CMD_FONT_DEF] = COMMENT_FONT_SIZE[CMD_FONT_DEF];
	setting->fixed_font_size[CMD_FONT_BIG] = COMMENT_FONT_SIZE[CMD_FONT_BIG];
	setting->fixed_font_size[CMD_FONT_SMALL] = COMMENT_FONT_SIZE[CMD_FONT_SMALL];
	setting->next_y_ratio = 1;	// 1%
	setting->target_width = 0;
	int i;
	char* arg;
	for(i=0;i<argc;i++){
		arg = argv[i];
		if(!setting->data_user_path && strncmp(FRAMEHOOK_OPT_DATA_USER,arg,FRAMEHOOK_OPT_DATA_USER_LEN) == 0){
			char* data_user = arg+FRAMEHOOK_OPT_DATA_USER_LEN;
			setting->data_user_path = data_user;
			setting->enable_user_comment = TRUE;
			fprintf(log,"[framehook/init]User Comment data path:%s\n",setting->data_user_path);
			fflush(log);
		}else if(!setting->data_owner_path && strncmp(FRAMEHOOK_OPT_DATA_OWNER,arg,FRAMEHOOK_OPT_DATA_OWNER_LEN) == 0){
			char* data_owner = arg+FRAMEHOOK_OPT_DATA_OWNER_LEN;
			setting->data_owner_path = data_owner;
			setting->enable_owner_comment = TRUE;
			fprintf(log,"[framehook/init]Owner Comment data path:%s\n",setting->data_owner_path);
			fflush(log);
		} else if(!setting->data_optional_path && strncmp(FRAMEHOOK_OPT_DATA_OPTIONAL,arg,FRAMEHOOK_OPT_DATA_OPTIONAL_LEN) == 0){
			char* data_optional = arg+FRAMEHOOK_OPT_DATA_OPTIONAL_LEN;
			setting->data_optional_path = data_optional;
			setting->enable_optional_comment = TRUE;
			fprintf(log,"[framehook/init]Optional Comment data path:%s\n",setting->data_optional_path);
			fflush(log);
		}else if(!setting->font_path && strncmp(FRAMEHOOK_OPT_FONT,arg,FRAMEHOOK_OPT_FONT_LEN) == 0){
			char* font = arg+FRAMEHOOK_OPT_FONT_LEN;
			setting->font_path = font;
			fprintf(log,"[framehook/init]Font path:%s\n",setting->font_path);
			fflush(log);
		}else if(strncmp(FRAMEHOOK_OPT_FONTINDEX,arg,FRAMEHOOK_OPT_FONTINDEX_LEN) == 0){
			setting->font_index = MAX(0,atoi(arg+FRAMEHOOK_OPT_FONTINDEX_LEN));
			fprintf(log,"[framehook/init]font index:%d\n",setting->font_index);
			fflush(log);
		}else if(strncmp(FRAMEHOOK_OPT_SHADOW,arg,FRAMEHOOK_OPT_SHADOW_LEN) == 0){
			setting->shadow_kind = MAX(0,atoi(arg+FRAMEHOOK_OPT_SHADOW_LEN));
			fprintf(log,"[framehook/init]shadow kind:%d\n",setting->shadow_kind);
			fflush(log);
		}else if(strncmp(FRAMEHOOK_OPT_SHOW_USER,arg,FRAMEHOOK_OPT_SHOW_USER_LEN) == 0){
			setting->user_slot_max = MAX(0,atoi(arg+FRAMEHOOK_OPT_SHOW_USER_LEN));
			fprintf(log,"[framehook/init]User Comments on screen:%d\n",setting->user_slot_max);
			fflush(log);
		}else if(strncmp(FRAMEHOOK_OPT_SHOW_OWNER,arg,FRAMEHOOK_OPT_SHOW_OWNER_LEN) == 0){
			setting->owner_slot_max = MAX(0,atoi(arg+FRAMEHOOK_OPT_SHOW_OWNER_LEN));
			fprintf(log,"[framehook/init]Owner Comments on screen:%d\n",setting->owner_slot_max);
			fflush(log);
		}else if(strncmp(FRAMEHOOK_OPT_SHOW_OPTIONAL,arg,FRAMEHOOK_OPT_SHOW_OPTIONAL_LEN) == 0) {
			setting->optional_slot_max = MAX(0,atoi(arg+FRAMEHOOK_OPT_SHOW_OPTIONAL_LEN));
			fprintf(log,"[framehook/init]Optional Comment on screen: %d\n", setting->optional_slot_max);
			fflush(log);
		} else if(!setting->show_video && strcmp(arg,"--enable-show-video") == 0){
			fputs("[framehook/init]show video while converting.\n",log);
			fflush(log);
			setting->show_video=TRUE;
		}else if(!setting->fontsize_fix && strcmp(arg,"--enable-fix-font-size") == 0){
			fputs("[framehook/init]fix font size automatically.\n",log);
			fflush(log);
			setting->fontsize_fix=TRUE;
		}else if(!setting->opaque_comment && strcmp(arg,"--enable-opaque-comment") == 0){
			fputs("[framehook/init]enable opaque comment.\n",log);
			fflush(log);
			setting->opaque_comment=TRUE;
		}else if (!setting->optional_trunslucent && strcmp(arg,"--optional-translucent")==0) {
			fputs("[framehook/init]optonal comment translucent.\n", log);
			fflush(log);
			setting->optional_trunslucent=TRUE;
		}else if(strcmp(arg,"--nico-width-wide")==0){
			fputs("[framehook/init]use wide player.\n",log);
			fflush(log);
			setting->nico_width_now = NICO_WIDTH_WIDE;
		}else if(setting->video_length <= 0 && strncmp(FRAMEHOOK_OPT_VIDEO_LENGTH,arg,FRAMEHOOK_OPT_VIDEO_LENGTH_LEN) == 0){
			setting->video_length = MAX(0,atoi(arg+FRAMEHOOK_OPT_VIDEO_LENGTH_LEN)) * VPOS_FACTOR;
			fprintf(log,"[framehook/init]video length (to assist ffmpeg):%d\n",setting->video_length);
			fflush(log);
		} else if (strncmp(FRAMEHOOK_OPT_FONT_HEIGHT_FIX,arg,FRAMEHOOK_OPT_FONT_HEIGHT_FIX_LEN) == 0){
			int font_h_fix[3];
			int n_font = sscanf(arg + FRAMEHOOK_OPT_FONT_HEIGHT_FIX_LEN, "%d%d%d", font_h_fix, font_h_fix + 1, font_h_fix + 2);
			if(n_font > 2){
				setting->next_y_ratio = font_h_fix[2];
			}
			if(n_font > 1){
				setting->font_h_fix_r_wide = font_h_fix[1];
			}
			if(n_font > 0){ 
				setting->font_h_fix_r = font_h_fix[0];
			}
			fprintf(log, "[framehook/init]font height fix ratio:%d%% %d%%, y_diff %d%% (experimental)\n", setting->font_h_fix_r, setting->font_h_fix_r_wide, setting->next_y_ratio);
			fflush(log);
		} else if (strncmp(FRAMEHOOK_OPT_ASPECT_MODE, arg, FRAMEHOOK_OPT_ASPECT_MODE_LEN) == 0) {
			int aspect_mode = MAX(0, atoi(arg + FRAMEHOOK_OPT_ASPECT_MODE_LEN));
			/**
			 * �A�X�y�N�g��̎w��. �R�����g�̃t�H���g�T�C�Y�⑬�x�ɉe������.�i���񂫂�΂��݊��j
			 * 0 -  4:3  �� 512
			 * 1 - 16:9  �� 640
			 */
			fprintf(log, "[framehook/init]aspect mode:%d\n", aspect_mode);
			fflush(log);
			if (aspect_mode){
				fputs("[framehook/init]use wide player.\n",log);
				fflush(log);
				setting->nico_width_now = NICO_WIDTH_WIDE;
			} else {
				fputs("[framehook/init]use normal player.\n",log);
				fflush(log);
				setting->nico_width_now = NICO_WIDTH;
			}
		} else if (strcmp("--disable-original-resize",arg) == 0){
			setting->original_resize = FALSE;
			fprintf(log,"[framehook/init]disable original resize (experimental)\n");
			fflush(log);
		} else if (strcmp("--disable-limitwidth-resize",arg) == 0){
			setting->limitwidth_resize = FALSE;
			fprintf(log,"[framehook/init]disable limit-width resize (experimental)\n");
			fflush(log);
		} else if (strncmp(FRAMEHOOK_OPT_LIMIT_WIDTH, arg, FRAMEHOOK_OPT_LIMIT_WIDTH_LEN) == 0) {
			int limit_width[2];
			int n_limit = sscanf(arg + FRAMEHOOK_OPT_LIMIT_WIDTH_LEN,"%d%d", limit_width, limit_width + 1);
			if (n_limit > 1){
				setting->nico_limit_width_full = limit_width[1];
				setting->nico_limit_width = limit_width[0];
			} else if (n_limit > 0){
				setting->nico_limit_width = 
				setting->nico_limit_width_full = limit_width[0];
			}
			fprintf(log, "[framehook/init]limit width:%d %d (experimental)\n",
				setting->nico_limit_width, setting->nico_limit_width_full);
			fflush(log);
		} else if (strncmp(FRAMEHOOK_OPT_LIMIT_HEIGHT, arg, FRAMEHOOK_OPT_LIMIT_HEIGHT_LEN) == 0) {
			int limit_height[2];
			int n_limith = sscanf(arg + FRAMEHOOK_OPT_LIMIT_HEIGHT_LEN,"%d%d", limit_height, limit_height + 1);
			if (n_limith > 1){
				setting->nico_limit_height = limit_height[0];
				setting->nico_limit_height_wide = limit_height[1];
			} else if (n_limith > 0){
				setting->nico_limit_height = 
				setting->nico_limit_height_wide = limit_height[0];
			}
			fprintf(log, "[framehook/init]limit height:%d %d (experimental)\n",setting->nico_limit_height,setting->nico_limit_height_wide);
			fflush(log);
		} else if (strcmp("--disable-linefeed-resize",arg) == 0){
			setting->linefeed_resize = FALSE;
			fprintf(log,"[framehook/init]disable llinefeed resize (experimental)\n");
			fflush(log);
		} else if (strcmp("--disable-double-resize",arg) == 0){
			setting->double_resize = FALSE;
			fprintf(log,"[framehook/init]disable double resize (experimental)\n");
			fflush(log);
		} else if (strcmp("--disable-font-doublescale-fix",arg) == 0){
			setting->font_double_scale = FALSE;
			fprintf(log,"[framehook/init]disable font doublescaled (experimental)\n");
			fflush(log);
		} else if (strncmp(FRAMEHOOK_OPT_FIXED_FONT_SIZE, arg, FRAMEHOOK_OPT_FIXED_FONT_SIZE_LEN) == 0) {
			int fixed_font[CMD_FONT_MAX];
			int n_font = sscanf(arg + FRAMEHOOK_OPT_FIXED_FONT_SIZE_LEN,"%d%d%d",fixed_font,fixed_font+1,fixed_font+2);
			if (n_font > CMD_FONT_DEF){
				setting->fixed_font_size[CMD_FONT_DEF] = fixed_font[CMD_FONT_DEF];
			}
			if (n_font > CMD_FONT_BIG){
				setting->fixed_font_size[CMD_FONT_BIG] = fixed_font[CMD_FONT_BIG];
			}
			if (n_font > CMD_FONT_SMALL){
				setting->fixed_font_size[CMD_FONT_SMALL] = fixed_font[CMD_FONT_SMALL];
			}
			fprintf(log, "[framehook/init]fixed font size: DEFAULT=%d BIG=%d SMALL=%d (experimental)\n",
					setting->fixed_font_size[CMD_FONT_DEF],
					setting->fixed_font_size[CMD_FONT_BIG],
					setting->fixed_font_size[CMD_FONT_SMALL]);
			fflush(log);
		} else if (strncmp(FRAMEHOOK_OPT_TARGET_SIZE, arg, FRAMEHOOK_OPT_TARGET_SIZE_LEN) == 0) {
			setting->target_width = MAX(0,atoi(arg + FRAMEHOOK_OPT_TARGET_SIZE_LEN));
			fprintf(log, "[framehook/init]target width: %d (experimaental)\n",setting->target_width);
			fflush(log);
		}
	}
	//�����𐳂������͂������ۂ��̃`�F�b�N
	//�����Ń`�F�b�N���Ă���̈ȊO�́A�f�t�H���g�ݒ�œ�����B
	if(!setting->font_path){
		fputs("[framehook/init]please set FONT PATH.\n",log);
		fflush(log);
		return FALSE;
	}
	return TRUE;
}

/*
 * �K�v�Ȋ֐���߁B�t���[�����ƂɌĂ΂���I
 *
 */
__declspec(dllexport) void ExtProcess(void *ctx,const toolbox *tbox,vhext_frame *pict){
		ContextInfo *ci = (ContextInfo *) ctx;
		FILE* log = ci->log;

	// �O��̌Ăяo���ŃC�x���g������Α҂�
	if(ci->data.process_first_called && !ci->data.original_resize){
		SDL_Event event;
		while(SDL_PollEvent(&event)){}
	}

	/* Note:
	 * Saccubus 1.22�ȍ~�̊g��vhook�t�B���^�ł́ARGB24�t�H�[�}�b�g�ł̂�
	 * �摜���񋟂���܂��B
	 */

		//SDL�̃T�[�t�F�C�X�ɕϊ�
		SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(pict->data,
												pict->w,pict->h,24,pict->linesize,
											#if SDL_BYTEORDER == SDL_BIG_ENDIAN
												0xff000000,
												0x00ff0000,
												0x0000ff00,
											#else
												0x000000ff,
												0x0000ff00,
												0x00ff0000,
											#endif
												0x00000000
												);
	//�t�B���^
	int now_vpos = (pict->pts * VPOS_FACTOR);
	if(!main_process(&ci->data,surf,now_vpos)){
		fputs("[framehook/process]failed to process.\n",log);
		fflush(log);
		exit(1);
	}
	//�T�[�t�F�C�X�J��
	SDL_FreeSurface(surf);
	fflush(log);
}

/*
 * �K�v�Ȋ֐��Ō�B�I�������Ă΂���I
 *
 */

__declspec(dllexport) void ExtRelease(void *ctx,const toolbox *tbox){
		ContextInfo *ci;
		ci = (ContextInfo *) ctx;
		FILE* log = ci->log;
		fputs("[framehook/close]closing...\n",log);
		if (ctx) {
				closeData(&ci->data);
			fputs("[framehook/close]closed.\n",log);
				fclose(log);
			//�R���e�L�X�g�S��
				free(ctx);
		}
		//���C�u�����̏I��
		close();
}
