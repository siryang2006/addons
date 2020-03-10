#include "MyInstance.h"


MyInstance::MyInstance(PP_Instance instance) : pp::Instance(instance) {
    pp::Var var_reply = pp::Var("hello from Pepper Plugin");
    PostMessage(var_reply);
}

bool MyInstance::Init(uint32_t argc, const char* argn[], const char* argv[]) {
    printf("Init\n");
    return true;
}

void MyInstance::HandleMessage(const pp::Var& message) {
    if (message.is_string()) {
        printf("HandleMessage: %s\n", message.AsString().c_str());
    }

    if (message.is_dictionary()) {
        pp::VarDictionary json = (pp::VarDictionary)message;
        std::string strJson = json.AsString();
        printf("HandleMessage: %s\n", strJson.c_str());
    }
}

MyInstance::~MyInstance() {
}
