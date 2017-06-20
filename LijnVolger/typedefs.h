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
    int v;
    struct NAV * next;
};
typedef struct NAV nav;

#endif // TYPEDEFS_H_INCLUDED
