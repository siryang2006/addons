#pragma once
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/var.h"
#include "ppapi/cpp/var_dictionary.h"

class MyInstance : public pp::Instance
{
public:
    explicit MyInstance(PP_Instance instance);
    virtual ~MyInstance();
    virtual void HandleMessage(const pp::Var& message);

    virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]);
};
