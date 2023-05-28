
#ifndef InteractiveAudioLib_h
#define InteractiveAudioLib_h
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"
#include "assert.h"

#define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define DECL_ARRAY(type) \
typedef struct { \
    type* array;\
    int arrayLength; \
} array_##type; \

DECL_ARRAY(char)

typedef array_char clip_buffer;

DECL_ARRAY(clip_buffer)

clip_buffer* array_saferead_clip_buffer(array_clip_buffer* array, int index);

typedef struct {
    array_clip_buffer clip_buffers;
    
    struct {
        int clipIndex;
        int clipOffset;
        int nextClipIndex;
    } state;
} interaudio_state_machine;


void get_buffer(interaudio_state_machine* stateMachine,
                char* out_buffer,
                int out_buffer_length);

#endif /* InteractiveAudioLib_h */
