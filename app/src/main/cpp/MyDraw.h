#ifndef AUDIO_RECORD_H
#define  AUDIO_RECORD_H

#include <string>
#include <assert.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <android/log.h>
#include  <endian.h>
#include  <stdio.h>


class MyDraw
{
public:
    MyDraw();
    ~MyDraw();
    void Init();
    void StartDraw();
    void StopDraw();
    static void* Run(void *data);
private:
    pthread_t pthread;
};
#endif