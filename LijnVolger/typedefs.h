#ifndef TYPEDEFS_H_INCLUDED
#define TYPEDEFS_H_INCLUDED

typedef struct {
    int v;
    char name[8];
} cell;

typedef struct {
    int x, y;
} coords;

struct NAV
{
    char c;
    struct NAV * next;
};
typedef struct NAV nav;

struct BLOCK
{
    int x;
    int y;
    struct BLOCK * next;
};
typedef struct BLOCK block;

#endif // TYPEDEFS_H_INCLUDED
