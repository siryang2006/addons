#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

class HelloPPAPIInstance : public pp::Instance {
public:
    explicit HelloPPAPIInstance(PP_Instance instance) : pp::Instance(instance) {
        pp::Var var_reply = pp::Var("hello from Pepper Plugin");
        PostMessage(var_reply);
        printf("HelloPPAPIInstance\n");
    }

    virtual ~HelloPPAPIInstance() {}

    virtual void HandleMessage(const pp::Var& var_message) {
        printf("HandleMessage  ");
        if (var_message.is_string()) {
            printf("HandleMessage: %s\n", var_message.AsString().c_str());
        }
    }
};

class HelloPPAPIModule : public pp::Module {
public:
    HelloPPAPIModule() : pp::Module() {}
    virtual ~HelloPPAPIModule() {}

    virtual pp::Instance* CreateInstance(PP_Instance instance) {
        printf("CreateInstance\n");
        return new HelloPPAPIInstance(instance);
    }
};

namespace pp {
    Module* CreateModule() {
        return new HelloPPAPIModule();
    }
}  // namespace pp