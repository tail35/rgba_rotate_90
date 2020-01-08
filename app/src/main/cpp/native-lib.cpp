#include <jni.h>
#include <string>
#include <android/native_window_jni.h>
#include <android/native_window.h>
#include "MyDraw.h"


extern "C"
{
#include "libavutil/imgutils.h"
#include "libavutil/log.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavutil/imgutils.h"
#include "libavcodec/jni.h"
}


int readData(unsigned char* buff, unsigned int size){
    FILE* fd = fopen("/sdcard/data/cn.blackboxsoftware.weya/1.rgba", "rb+");
    if (!fd) {
        return -1;
    }
    int res = fread(buff, 1, size, fd);
    if(res!= size){
        return -1;
    }
    fclose(fd);
    return  0;
}

void mycopy(unsigned char* dst,int dstStride,unsigned char* src,int w,int h){

    for(int i=0;i<h;i++){
        memcpy(dst+i*dstStride*4,src+i*w*4,w*4);
    }
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_tech_testnativewindow_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */,jobject surface) {

        //获取目标surface
        ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
        if (NULL == window) {
            //ThrowException(env, "java/lang/RuntimeException", "unable to get native window");
            return NULL;
        }
//        int w=1280;
//        int h=720;
        int w=720;
        int h=1280;
        int32_t result = ANativeWindow_setBuffersGeometry(window, w, h, WINDOW_FORMAT_RGBA_8888);
        if (result < 0) {
            //ThrowException(env, "java/lang/RuntimeException", "unable to set buffers geometry");
            //释放窗口
            ANativeWindow_release(window);
            window = NULL;
            return NULL;
        }
        ANativeWindow_acquire(window);

        ANativeWindow_Buffer buffer;

        if (ANativeWindow_lock(window, &buffer, NULL) < 0) {
            //ThrowException(env, "java/lang/RuntimeException", "unable to lock native window");
            //释放窗口
            ANativeWindow_release(window);
            window = NULL;
            return NULL;
        }
        unsigned  int size = w*4*h;
        unsigned char* src = new unsigned char[size];
        readData(src,size);
        unsigned char* dst =  (unsigned char*)buffer.bits;
        memset(dst,0,buffer.height*4*buffer.stride);
        //myav_image_copy_plane(dst, buffer.stride*4, src, size, w, h);
        mycopy(dst,buffer.stride,src,w,h);
        if (ANativeWindow_unlockAndPost(window) < 0) {
            //ThrowException(env, "java/lang/RuntimeException","unable to unlock and post to native window");
        }

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
