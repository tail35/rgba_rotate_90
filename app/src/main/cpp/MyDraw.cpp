#include "MyDraw.h"
#include <unistd.h>
#include <arpa/inet.h>



MyDraw::MyDraw(){

}
MyDraw::~MyDraw(){
}

void MyDraw::Init()
{
}

void* MyDraw::Run(void *data){
    MyDraw* pThis = (MyDraw*)data;
    pThis->Init();
    while (1) {
        usleep(1000);
    }
    return 0;
}

void MyDraw::StartDraw(){
    pthread_create(&pthread, NULL, MyDraw::Run, (void*) this);
}

void MyDraw::StopDraw(){
}