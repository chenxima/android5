#include <binder/IServiceManager.h>  
#include <binder/IPCThreadState.h>  
#include "HelloWorld.h"  
  
namespace android{  
    sp<IBinder> binder;  
    void HelloWorld::printResult(String8 name){  
        getHelloWorldService();  
        Parcel data, reply;  
        String8 answer;  
          
        data.writeInt32(getpid());
	data.writeString8(name);
        ALOGE("BpExampleService::create remote()->transact()/n");  
        binder->transact(0, data, &reply);  
        answer = reply.readString8();  
        printf("%s", answer.string());      
        return;  
    }  
  
    const void HelloWorld::getHelloWorldService(){  
        sp<IServiceManager> sm = defaultServiceManager();  
        binder = sm->getService(String16("HelloWorldService"));  
        ALOGE("Example::getExampleService %p/n",sm.get());  
        if (binder == 0) {  
            ALOGW("ExampleService not published, waiting...");  
        return;  
        }  
    }  
};
  
using namespace android;  
  
int main(int argc, char** argv)  {  
    HelloWorld* p = new HelloWorld(); 
    String8 name = String8("World");
    if(argc > 1){
	name = String8(argv[1]);
    } 
    p->printResult(name);  
    return 0;  
}  
