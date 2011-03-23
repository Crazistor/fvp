#ifndef FVP_MMAP_H
#define FVP_MMAP_H

#include "fvp_common.h"

#ifdef __cplusplus
extern "C"{
#endif 


struct _FvpMmap;
typedef struct _FvpMmap FvpMmap;

FvpMmap *fvp_mmap_create(const char* filename, size_t offset, size_t size);
void* fvp_mmap_data(FvpMmap* thiz);
size_t fvp_mmap_length(FvpMmap* thiz);
void fvp_mmap_destroy(FvpMmap* thiz);
int      fvp_mmap_exist(const char* filename);

#ifdef __cplusplus
}
#endif 

#endif/*FVP_MMAP_H*/
