#pragma once

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>
using namespace v8;
using namespace node;

class MyObject : public ObjectWrap {
public:
    static void Init(v8::Isolate* isolate);
    static Local<Object> NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);
    inline double value() const { return value_; }

private:
    explicit MyObject(double value = 0);
    ~MyObject();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    void PlusOne(const v8::FunctionCallbackInfo<v8::Value>& args);
    void InvokeCallBack(const v8::FunctionCallbackInfo<v8::Value>& args);

    auto AddHandleMessageCallBack(Isolate* isolate, Local<Object> obj)->void;
    void dispatchNotifyCallback(std::string text);

protected:
    static Persistent<Function> m_clsPrototype;
    double value_;

    Persistent<Function> m_onHandleMessage;
};


