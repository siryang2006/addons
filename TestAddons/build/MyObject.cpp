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

    NODE_SET_PROTOTYPE_METHOD(tpl, "InvokeCallBack", [](const FunctionCallbackInfo<Value>& info) {
        MyObject* pObj = node::ObjectWrap::Unwrap<MyObject>(info.Holder());
        pObj->InvokeCallBack(info);
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

    //add callback
    MyObject* pObj = node::ObjectWrap::Unwrap<MyObject>(args.Holder());
    pObj->AddHandleMessageCallBack(isolate, args.Holder());
}

    auto MyObject::AddHandleMessageCallBack(Isolate* isolate, Local<Object> result)->void {
        result->DefineOwnProperty(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "handleMessage").ToLocalChecked(),
            Local<Object>(), ReadOnly);
        result->SetAccessor(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "handleMessage").ToLocalChecked(), [](
            Local<Name> property,
            const PropertyCallbackInfo<Value>& info) {
            v8::Local<v8::Object> handle = info.Holder();
            assert(!handle.IsEmpty());
            assert(handle->InternalFieldCount() > 0);
            void* ptr = handle->GetAlignedPointerFromInternalField(0);
            info.GetReturnValue().Set(static_cast<MyObject*>(ptr)->m_onHandleMessage.Get(info.GetIsolate()));
        },
            [](
                Local<Name> property,
                Local<Value> value,
                const PropertyCallbackInfo<void>& info) {

            v8::Local<v8::Object> handle = info.Holder();
            assert(!handle.IsEmpty());
            assert(handle->InternalFieldCount() > 0);
            void* ptr = handle->GetAlignedPointerFromInternalField(0);
            static_cast<MyObject*>(ptr)->m_onHandleMessage.Reset(info.GetIsolate(), value.As<Function>());
        }
        );
}

    void MyObject::dispatchNotifyCallback(std::string text) {
        auto *isolate = Isolate::GetCurrent();

        Local<Value> onHandleMessage = m_onHandleMessage.Get(isolate);
        if (!onHandleMessage.IsEmpty()) {
            Local<Value> retval[] = {
                String::NewFromUtf8(isolate, text.c_str()).ToLocalChecked()
            };
            onHandleMessage.As<Object>()->CallAsFunction(isolate->GetCurrentContext(),
                this->handle(), sizeof(retval) / sizeof(retval[0]), retval);
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

void MyObject::InvokeCallBack(const v8::FunctionCallbackInfo<v8::Value>& args) {
    MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
    std::string strText = std::to_string(obj->value_);
    dispatchNotifyCallback(strText);
}