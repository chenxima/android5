#include "HelloWorldService.h"
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

namespace android {

    static struct sigaction oldact;
    static pthread_key_t sigbuskey;
    
    int HelloWorldService::instantiate(){
        ALOGE("HelloWorldService instantiate");
        int r = defaultServiceManager()->addService(String16("HelloWorldService"), new HelloWorldService());
        ALOGE("HelloWorldService r = %d/n", r);
        return r;
    }

    HelloWorldService::HelloWorldService(){ 
        ALOGV("HelloWorldService created");
        mNextConnId = 1;
        pthread_key_create(&sigbuskey, NULL);
    }

    HelloWorldService::~HelloWorldService(){
        pthread_key_delete(sigbuskey);
        ALOGV("HelloWorldService destroyed");
    }

    status_t HelloWorldService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags){
        switch(code){
            case 0: {
                pid_t pid = data.readInt32();
				String8 word = data.readString8();
                reply->writeString8(String8("Hello ") + word + "!\n");
                return NO_ERROR;
            }
            break;
            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
    }
};

