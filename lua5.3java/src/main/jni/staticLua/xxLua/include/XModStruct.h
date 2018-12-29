/****************************************
 * @Author Irvin Pang @ XXTeam
 * @Repo   https://github.com/xxzhushou
 ****************************************/

#ifndef __XMOD_STRUCT_H__
#define __XMOD_STRUCT_H__

#include <stdint.h>

typedef uint8_t ubyte;

typedef struct
{
    int x;
    int y;
} xmod_point;

typedef struct
{
    int width;
    int height;
} xmod_size;

typedef struct
{
    int x;
    int y;
    int width;
    int height;
} xmod_rect;

typedef struct
{
    ubyte r;
    ubyte g;
    ubyte b;
} xmod_color3b;

typedef struct
{
    float r;
    float g;
    float b;
} xmod_color3f;

typedef struct
{
    ubyte r;
    ubyte g;
    ubyte b;
    ubyte a;
} xmod_color4b;

typedef struct
{
    float r;
    float g;
    float b;
    float a;
} xmod_color4f;

typedef void xmod_image;

#endif // __XMOD_STRUCT_H__
