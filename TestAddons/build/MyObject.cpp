// myobject.cc
#include <node.h>
#include "myobject.h"

Persistent<Function> MyObject::m_clsPrototype;
MyObject::MyObject(double value) : value_(value) {
}

MyObject::~MyObject() {
}

void MyObject::Init(Isolate* isolate) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(
        isolate, "MyObject", NewStringType::kNormal).ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "PlusOne", [](const FunctionCallbackInfo<Value>& info) {
        MyObject* pObj = node::ObjectWrap::Unwrap<MyObject>(info.Holder());
        pObj->PlusOne(info);
    });

    Local<Context> context = isolate->GetCurrentContext();
    m_clsPrototype.Reset(isolate, tpl->GetFunction(context).ToLocalChecked());

    /*AddEnvironmentCleanupHook(isolate, [](void*) {
    constructor.Reset();
    }, nullptr);*/
}

void MyObject::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    if (args.IsConstructCall()) {
        // Invoked as constructor: `new MyObject(...)`
        double value = args[0]->IsUndefined() ?
            0 : args[0]->NumberValue(context).FromMaybe(0);
        MyObject* obj = new MyObject(value);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } else {
        // Invoked as plain function `MyObject(...)`, turn into construct call.
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        Local<Function> cons = Local<Function>::New(isolate, m_clsPrototype);
        Local<Object> instance =
            cons->NewInstance(context, argc, argv).ToLocalChecked();
        args.GetReturnValue().Set(instance);
    }
}

Local<Object> MyObject::NewInstance(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    const unsigned argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Function> cons = Local<Function>::New(isolate, m_clsPrototype);
    Local<Context> context = isolate->GetCurrentContext();
    return cons->NewInstance(context, argc, argv).ToLocalChecked();

    //args.GetReturnValue().Set(instance);
}

void MyObject::PlusOne(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
    obj->value_ += 1;

    args.GetReturnValue().Set(Number::New(isolate, obj->value_));
}