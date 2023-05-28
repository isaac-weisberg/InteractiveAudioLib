#include "InteractiveAudioLib.h"

clip_buffer* array_saferead_clip_buffer(array_clip_buffer* array, int index) {
    if (index < array->arrayLength) {
        return &array->array[index];
    }
    return NULL;
}

void get_buffer(interaudio_state_machine* stateMachine,
                char* buffer,
                int out_buffer_length) {

    int writeHeadInOutBuffer = 0;
    
    while (writeHeadInOutBuffer < out_buffer_length) {
        int remainingOutBufferSpace = out_buffer_length - writeHeadInOutBuffer;
        
        clip_buffer* clipBuffer = array_saferead_clip_buffer(&stateMachine->clip_buffers,
                                                             stateMachine->state.clipIndex);
        
        int remainingClipLength;
        if (clipBuffer != NULL) {
            int clipLength = clipBuffer->arrayLength;
            remainingClipLength = clipLength - stateMachine->state.clipOffset;
        } else {
            assert(false);
            return;
        }
        
        int clipLengthThatCanBeWritten = MIN(remainingClipLength, remainingOutBufferSpace);
        int clipLengthToBeWritten = clipLengthThatCanBeWritten;
        
        memcpy(&buffer[writeHeadInOutBuffer],
               &clipBuffer->array[stateMachine->state.clipOffset],
               clipLengthToBeWritten * sizeof(char));
        
        bool wholeClipWasWritten = remainingClipLength <= remainingOutBufferSpace;
        
        if (wholeClipWasWritten) {
            stateMachine->state.clipIndex = stateMachine->state.nextClipIndex;
            stateMachine->state.clipOffset = 0;
        } else {
            stateMachine->state.clipIndex = stateMachine->state.clipIndex;
            stateMachine->state.clipOffset = stateMachine->state.clipOffset + clipLengthToBeWritten;
        }
        
        writeHeadInOutBuffer += clipLengthToBeWritten;
    }
}
