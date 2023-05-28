//
//  main.c
//  InteractiveAudioLibTests
//
//  Created by a.vaysberg on 5/28/23.
//

#include <stdio.h>
#include "InteractiveAudioLib.h"

int main(int argc, const char * argv[]) {
    clip_buffer bufferOne = {
        "asdf",
        4
    };
    clip_buffer bufferTwo = {
        "qwer",
        4
    };
    
    clip_buffer buffers[] = { bufferOne, bufferTwo };
    array_clip_buffer arrayOfClipBuffers = {
        buffers,
        2
    };
    interaudio_state_machine stateMachine;
    stateMachine.clip_buffers = arrayOfClipBuffers;
    
    int out_buffer_length = 11;
    char out_buffer[out_buffer_length];
    memset(out_buffer, 'V', out_buffer_length);
    
    printf("%.*s\n", out_buffer_length, out_buffer);
    
    get_buffer(&stateMachine, out_buffer, out_buffer_length);
    
    printf("%.*s\n", out_buffer_length, out_buffer);
    get_buffer(&stateMachine, out_buffer, out_buffer_length);
    
    printf("%.*s\n", out_buffer_length, out_buffer);
    get_buffer(&stateMachine, out_buffer, out_buffer_length);
    
    stateMachine.state.nextClipIndex = 1;
    
    printf("%.*s\n", out_buffer_length, out_buffer);
    get_buffer(&stateMachine, out_buffer, out_buffer_length);
    
    printf("%.*s\n", out_buffer_length, out_buffer);
    get_buffer(&stateMachine, out_buffer, out_buffer_length);
    
    printf("%.*s\n", out_buffer_length, out_buffer);
    get_buffer(&stateMachine, out_buffer, out_buffer_length);
    
    printf("%.*s\n", out_buffer_length, out_buffer);
    return 0;
}
