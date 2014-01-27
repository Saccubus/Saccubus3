#ifndef FRAMEHOOK_H_
#define FRAMEHOOK_H_

void exitExtProcess();

/*Framehookに渡されるオプション用の定義*/

#define FRAMEHOOK_OPT_DATA_USER		"--data-user:"
#define FRAMEHOOK_OPT_DATA_USER_LEN	strlen(FRAMEHOOK_OPT_DATA_USER)

#define FRAMEHOOK_OPT_DATA_OWNER		"--data-owner:"
#define FRAMEHOOK_OPT_DATA_OWNER_LEN	strlen(FRAMEHOOK_OPT_DATA_OWNER)

#define FRAMEHOOK_OPT_DATA_OPTIONAL	"--data-optional:"
#define FRAMEHOOK_OPT_DATA_OPTIONAL_LEN	strlen(FRAMEHOOK_OPT_DATA_OPTIONAL)

#define FRAMEHOOK_OPT_FONT		"--font:"
#define FRAMEHOOK_OPT_FONT_LEN	strlen(FRAMEHOOK_OPT_FONT)

#define FRAMEHOOK_OPT_FONTINDEX		"--font-index:"
#define FRAMEHOOK_OPT_FONTINDEX_LEN	strlen(FRAMEHOOK_OPT_FONTINDEX)

#define FRAMEHOOK_OPT_FONTSIZE		"--enable-fix-font-size"
#define FRAMEHOOK_OPT_FONTSIZE_LEN	strlen(FRAMEHOOK_OPT_FONTSIZE)

#define FRAMEHOOK_OPT_SHADOW		"--shadow:"
#define FRAMEHOOK_OPT_SHADOW_LEN	strlen(FRAMEHOOK_OPT_SHADOW)

#define FRAMEHOOK_OPT_SHOW_USER		"--show-user:"
#define FRAMEHOOK_OPT_SHOW_USER_LEN	strlen(FRAMEHOOK_OPT_SHOW_USER)

#define FRAMEHOOK_OPT_SHOW_OWNER		"--show-owner:"
#define FRAMEHOOK_OPT_SHOW_OWNER_LEN	strlen(FRAMEHOOK_OPT_SHOW_OWNER)

#define FRAMEHOOK_OPT_SHOW_OPTIONAL 	"--show-optional:"
#define FRAMEHOOK_OPT_SHOW_OPTIONAL_LEN	strlen(FRAMEHOOK_OPT_SHOW_OPTIONAL)

#define FRAMEHOOK_OPT_SHOW_VIDEO		"--enable-show-video"
#define FRAMEHOOK_OPT_SHOW_VIDEO_LEN	strlen(FRAMEHOOK_OPT_SHOW_VIDEO)

#define FRAMEHOOK_OPT_OPAQUE_COMMENT		"--enable-opaque-comment"
#define FRAMEHOOK_OPT_OPAQUE_COMMENT_LEN	strlen(FRAMEHOOK_OPT_OPAQUE_COMMENT)

#define FRAMEHOOK_OPT_OPTIONAL_TRANSLUCENT	"--optional-translucent"
#define FRAMEHOOK_OPT_OPTIONAL_TRANSLUCENT_LEN	strlen(FRAMEHOOK_OPT_OPTIONAL_TRANSLUCENT)

#define FRAMEHOOK_OPT_VIDEO_LENGTH	"--video-length:"
#define FRAMEHOOK_OPT_VIDEO_LENGTH_LEN	strlen(FRAMEHOOK_OPT_VIDEO_LENGTH)

#define FRAMEHOOK_OPT_FONT_WIDTH_FIX "--font-width-fix-ratio:"
#define FRAMEHOOK_OPT_FONT_WIDTH_FIX_LEN strlen(FRAMEHOOK_OPT_FONT_WIDTH_FIX)

#define FRAMEHOOK_OPT_FONT_HEIGHT_FIX "--font-height-fix-ratio:"
#define FRAMEHOOK_OPT_FONT_HEIGHT_FIX_LEN strlen(FRAMEHOOK_OPT_FONT_HEIGHT_FIX)

#define FRAMEHOOK_OPT_ASPECT_MODE		"--aspect-mode:"
#define FRAMEHOOK_OPT_ASPECT_MODE_LEN	strlen(FRAMEHOOK_OPT_ASPECT_MODE)

#define FRAMEHOOK_OPT_COMMENT_SPEED		"--comment-speed:"
#define FRAMEHOOK_OPT_COMMENT_SPEED_LEN	strlen(FRAMEHOOK_OPT_COMMENT_SPEED)

#define FRAMEHOOK_OPT_GOTHIC_FONT		"--gothic-font:"
#define FRAMEHOOK_OPT_GOTHIC_FONT_LEN	strlen(FRAMEHOOK_OPT_GOTHIC_FONT)

#define FRAMEHOOK_OPT_SIMSUN_FONT		"--simsun-font:"
#define FRAMEHOOK_OPT_SIMSUN_FONT_LEN	strlen(FRAMEHOOK_OPT_SIMSUN_FONT)

#define FRAMEHOOK_OPT_GULIM_FONT		"--gulim-font:"
#define FRAMEHOOK_OPT_GULIM_FONT_LEN	strlen(FRAMEHOOK_OPT_GULIM_FONT)

#define FRAMEHOOK_OPT_ARIAL_FONT		"--arial-font:"
#define FRAMEHOOK_OPT_ARIAL_FONT_LEN	strlen(FRAMEHOOK_OPT_ARIAL_FONT)

#define FRAMEHOOK_OPT_ARIALUNI_FONT		"--arial-unicode-font:"
#define FRAMEHOOK_OPT_ARIALUNI_FONT_LEN	strlen(FRAMEHOOK_OPT_ARIALUNI_FONT)

#define FRAMEHOOK_OPT_GEORGIA_FONT		"--georgia-font:"
#define FRAMEHOOK_OPT_GEORGIA_FONT_LEN	strlen(FRAMEHOOK_OPT_GEORGIA_FONT)

#define FRAMEHOOK_OPT_MSUI_GOTHIC_FONT		"--msui-font:"
#define FRAMEHOOK_OPT_MSUI_GOTHIC_FONT_LEN	strlen(FRAMEHOOK_OPT_MSUI_GOTHIC_FONT)

#define FRAMEHOOK_OPT_DEVANAGARI_FONT		"--devanagari-font:"
#define FRAMEHOOK_OPT_DEVANAGARI_FONT_LEN	strlen(FRAMEHOOK_OPT_DEVANAGARI_FONT)

#define FRAMEHOOK_OPT_TAHOMA_FONT		"--tahoma-font:"
#define FRAMEHOOK_OPT_TAHOMA_FONT_LEN	strlen(FRAMEHOOK_OPT_TAHOMA_FONT)

#define FRAMEHOOK_OPT_MINGLIU_FONT		"--mingliu-font:"
#define FRAMEHOOK_OPT_MINGLIU_FONT_LEN	strlen(FRAMEHOOK_OPT_MINGLIU_FONT)

#define FRAMEHOOK_OPT_NMINCHO_FONT		"--new-mincho-font:"
#define FRAMEHOOK_OPT_NMINCHO_FONT_LEN	strlen(FRAMEHOOK_OPT_NMINCHO_FONT)

#define FRAMEHOOK_OPT_ESTRANGELO_FONT		"--estrangelo-edessa-font:"
#define FRAMEHOOK_OPT_ESTRANGELO_FONT_LEN	strlen(FRAMEHOOK_OPT_ESTRANGELO_FONT)

#define FRAMEHOOK_OPT_GUJARATI_FONT		"--gujarati-font:"
#define FRAMEHOOK_OPT_GUJARATI_FONT_LEN	strlen(FRAMEHOOK_OPT_GUJARATI_FONT)

#define FRAMEHOOK_OPT_BENGAL_FONT		"--bengal-font:"
#define FRAMEHOOK_OPT_BENGAL_FONT_LEN	strlen(FRAMEHOOK_OPT_BENGAL_FONT)

#define FRAMEHOOK_OPT_TAMIL_FONT		"--tamil-font:"
#define FRAMEHOOK_OPT_TAMIL_FONT_LEN	strlen(FRAMEHOOK_OPT_TAMIL_FONT)

#define FRAMEHOOK_OPT_LAOO_FONT		"--laoo-font:"
#define FRAMEHOOK_OPT_LAOO_FONT_LEN	strlen(FRAMEHOOK_OPT_LAOO_FONT)

#define FRAMEHOOK_OPT_GURMUKHI_FONT		"--gurmukhi-font:"
#define FRAMEHOOK_OPT_GURMUKHI_FONT_LEN	strlen(FRAMEHOOK_OPT_GURMUKHI_FONT)

#define FRAMEHOOK_OPT_EXTRA_FONT		"--extra-font:"
#define FRAMEHOOK_OPT_EXTRA_FONT_LEN	strlen(FRAMEHOOK_OPT_EXTRA_FONT)

#define FRAMEHOOK_OPT_FONT_LIST		"--font-list:"
#define FRAMEHOOK_OPT_FONT_LIST_LEN	strlen(FRAMEHOOK_OPT_FONT_LIST)

#define FRAMEHOOK_OPT_DEBUG	"--extra-mode:"
#define FRAMEHOOK_OPT_DEBUG_LEN	strlen(FRAMEHOOK_OPT_DEBUG)

#define FRAMEHOOK_OPT_FONT_DIR	"--font-dir:"
#define FRAMEHOOK_OPT_FONT_DIR_LEN	strlen(FRAMEHOOK_OPT_FONT_DIR)

#define FRAMEHOOK_OPT_INPUT_SIZE	"--input-size:"
#define FRAMEHOOK_OPT_INPUT_SIZE_LEN	strlen(FRAMEHOOK_OPT_INPUT_SIZE)

#define FRAMEHOOK_OPT_SET_SIZE	"--set-size:"
#define FRAMEHOOK_OPT_SET_SIZE_LEN	strlen(FRAMEHOOK_OPT_SET_SIZE)

#define FRAMEHOOK_OPT_PAD_OPTION	"--pad-option:"
#define FRAMEHOOK_OPT_PAD_OPTION_LEN	strlen(FRAMEHOOK_OPT_PAD_OPTION)

#define FRAMEHOOK_OPT_OUT_SIZE	"--out-size:"
#define FRAMEHOOK_OPT_OUT_SIZE_LEN	strlen(FRAMEHOOK_OPT_OUT_SIZE)

#define FRAMEHOOK_OPT_APRIL_FOOL	"--april-fool:"
#define FRAMEHOOK_OPT_APRIL_FOOL_LEN	strlen(FRAMEHOOK_OPT_APRIL_FOOL)

#define FRAMEHOOK_OPT_WAKUIRO	"--wakuiro:"
#define FRAMEHOOK_OPT_WAKUIRO_LEN	strlen(FRAMEHOOK_OPT_WAKUIRO)

#define FRAMEHOOK_OPT_FRAMERATE	"--fr:"
#define FRAMEHOOK_OPT_FRAMERATE_LEN	strlen(FRAMEHOOK_OPT_WAKUIRO)

#define FRAMEHOOK_OPT_OPAQUE	"--opaque:"
#define FRAMEHOOK_OPT_OPAQUE_LEN	strlen(FRAMEHOOK_OPT_OPAQUE)

#endif /*FRAMEHOOK_H_*/
