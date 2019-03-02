/****************************************
 * @Author Irvin Pang @ XXTeam
 * @Repo   https://github.com/xxzhushou
 ****************************************/

#ifndef __XMOD_API_STUB_H__
#define __XMOD_API_STUB_H__

#include <string>

#include "XModMacros.h"
#include "XModStruct.h"

#define XMOD_PLATFORM_IOS       "iOS"
#define XMOD_PLATFORM_ANDROID   "Android"

#define XMOD_PRODUCT_DEV        "DEV"
#define XMOD_PRODUCT_XXZS       "XXZS"
#define XMOD_PRODUCT_IPA        "IPA"
#define XMOD_PRODUCT_KUWAN      "KUWAN"
#define XMOD_PRODUCT_SPIRIT     "SPIRIT"

XMOD_C_API_BEGIN

enum XModLogPriority
{
    kLogPriorityDebug = 0,
    kLogPriorityInfo,
    kLogPriorityWarn,
    kLogPriorityError
};

enum XModProductCode
{
    kProductDev = 1,            // 开发助手
    kProductXXZS,               // 叉叉助手
    kProductIPA,                // IPA精灵
    kProductKuwan,              // 酷玩
    kProductSpirit              // 叉叉小精灵
};

enum XModProcessMode
{
    kProcessEmbedded = 1,       // 集成运行模式
    kProcessStandalone = 3      // 独立运行模式
};

enum XModRotation
{
    kRotationNone,
    kRotationClockwise90,
    kRotationClockwise180,
    kRotationClockwise270
};

enum XModPixelFormat
{
    kPixelFormatBGRA8888 = 1,   // 32-bit texture: BGRA8888
    kPixelFormatRGBA8888,       // 32-bit texture: RGBA8888
    kPixelFormatRGB888,         // 24-bit texture: RGB888
    kPixelFormatA8,             // 8-bit textures: A8
    kPixelFormatI8,             // 8-bit textures used as masks
    kPixelFormatAI88,           // 16-bit textures used as masks
};

enum XModMockMode
{
    kMockModeInputFixed = 0x1000,
    kMockModeInputRelative = 0x3000,
    kMockModeOutput = 0x10000
};

/***************************
 * general
 ***************************/
XMOD_API void xmod_log(XModLogPriority priority, const char* fmt, ...);
XMOD_API void xmod_get_platform(char** platform);
XMOD_API void xmod_get_version_code(int* code);
XMOD_API void xmod_get_version_name(char** name);
XMOD_API void xmod_get_product_code(XModProductCode* code);
XMOD_API void xmod_get_process_mode(XModProcessMode* mode);
XMOD_API void xmod_get_product_name(char** name);
XMOD_API void xmod_get_public_path(char** path);
XMOD_API void xmod_get_private_path(char** path);
XMOD_API void xmod_get_resolved_path(const char* path, char** outpath);
XMOD_API void xmod_get_host_root_path(char** path);

/***************************
 * scrip
 ***************************/
XMOD_API bool xmod_script_get_id(int* id);
XMOD_API bool xmod_script_get_user_info(char** uid, int* membership, int* expiredTime);

/***************************
 * screen
 ***************************/
XMOD_API void xmod_screen_get_size(xmod_size* size);
XMOD_API void xmod_screen_mock_transform_rect(XModMockMode mode, const xmod_rect& in, xmod_rect* out);
XMOD_API void xmod_screen_mock_transform_point(XModMockMode mode, const xmod_point& in, xmod_point* out);

/***************************
 * xsp
 ***************************/
XMOD_API bool xmod_xsp_get_res(const char* subpath, unsigned char** buff, size_t* size);
XMOD_API bool xmod_xsp_extract_res(const char* subpath, const char* destpath);

/***************************
 * image
 ***************************/
XMOD_API const xmod_image* xmod_cached_image_from_screen();
XMOD_API xmod_image* xmod_image_from_screen();
XMOD_API xmod_image* xmod_image_from_screen_clip(const xmod_rect& rect);
XMOD_API xmod_image* xmod_image_from_file(const char* path);
XMOD_API xmod_image* xmod_image_from_stream(const unsigned char* buff, ssize_t len);
XMOD_API xmod_image* xmod_image_from_format(XModPixelFormat format, const xmod_size& size, const unsigned char* buff, ssize_t len);
XMOD_API void xmod_image_release(xmod_image* image);
XMOD_API bool xmod_image_get_size(const xmod_image* image, xmod_size* size);
XMOD_API void xmod_image_get_format(const xmod_image* image, XModPixelFormat* format);
XMOD_API bool xmod_image_get_rgb(const xmod_image* image, const xmod_point& point, xmod_color3b* c3b);
XMOD_API bool xmod_image_get_pixel(const xmod_image* image, const xmod_point& point, uint32_t* pixel);
XMOD_API bool xmod_image_get_pixels(const xmod_image* image, uint32_t** pixel);
XMOD_API void xmod_image_set_rotation(xmod_image* image, XModRotation rotation);
XMOD_API void xmod_image_clip_with_rect(xmod_image* image, const xmod_rect& rect);
XMOD_API bool xmod_image_save_to_file(const xmod_image* image, const char* path, int quality);

XMOD_C_API_END

#endif // __XMOD_API_STUB_H__
