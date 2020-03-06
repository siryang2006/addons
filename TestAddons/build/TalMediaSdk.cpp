#include "TalMediaSdk.h"
#include "MyObject.h"
#include <v8.h>
#include <node.h>
#include <uv.h>


void TalMediaSdk::Init(Local<Object> target) {
    //auto isolate = target->GetIsolate();

    // object
    MyObject::Init(target->GetIsolate());
    NODE_SET_METHOD(target, "createObject", [](const v8::FunctionCallbackInfo<v8::Value>& args) {
        args.GetReturnValue().Set(MyObject::NewInstance(args));
    });

    AtExit([](void *arg) {
    }, NULL);
}

TalMediaSdk::TalMediaSdk() {
}

TalMediaSdk::~TalMediaSdk() {

}