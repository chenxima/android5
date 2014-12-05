#ifndef ANDROID_HELLOWORLD_SERVICE_H  
#define ANDROID_HELLOWORLD_SERVICE_H  

#include <utils/threads.h>  
#include <utils/RefBase.h>  
#include <binder/IInterface.h>  
#include <binder/BpBinder.h>  
#include <binder/Parcel.h>  
  
namespace android {  
    class HelloWorldService : public BBinder {  
        mutable Mutex mLock;  
        int32_t mNextConnId;  
        public:  
            static int instantiate();  
            HelloWorldService();  
            virtual ~HelloWorldService();  
            virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);  
    };  
}; 
#endif  
