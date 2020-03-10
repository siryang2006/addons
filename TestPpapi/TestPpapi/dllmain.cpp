// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "ppapi/cpp/module.h"
#include "MyInstance.h"

// This object is the global object representing this plugin library as long
// as it is loaded.
class MyModule : public pp::Module {
public:
    MyModule() : pp::Module() {}
    virtual ~MyModule() {}

    // Override CreateInstance to create your customized Instance object.
    virtual pp::Instance* CreateInstance(PP_Instance instance) {
        return new MyInstance(instance);
    }
};

namespace pp {
    // Factory function for your specialization of the Module object.
    Module* CreateModule() {
        return new MyModule();
    }
}  // namespace pp


#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

/// The Instance class.  One of these exists for each instance of your NaCl
/// module on the web page.  The browser will ask the Module object to create
/// a new Instance for each occurrence of the <embed> tag that has these
/// attributes:
///     src="hello_tutorial.nmf"
///     type="application/x-pnacl"
/// To communicate with the browser, you must override HandleMessage() to
/// receive messages from the browser, and use PostMessage() to send messages
/// back to the browser.  Note that this interface is asynchronous.
/*class HelloTutorialInstance : public pp::Instance {
public:
    /// The constructor creates the plugin-side instance.
    /// @param[in] instance the handle to the browser-side plugin instance.
    explicit HelloTutorialInstance(PP_Instance instance) : pp::Instance(instance)
    {
        pp::Var var_reply = pp::Var("hello from Pepper Plugin");
        PostMessage(var_reply);
    }
    virtual ~HelloTutorialInstance() {}

    /// Handler for messages coming in from the browser via postMessage().  The
    /// @a var_message can contain be any pp:Var type; for example int, string
    /// Array or Dictinary. Please see the pp:Var documentation for more details.
    /// @param[in] var_message The message posted by the browser.
    virtual void HandleMessage(const pp::Var& var_message) {
        printf("HandleMessage\n");
        // TODO(sdk_user): 1. Make this function handle the incoming message.
    }
};

/// The Module class.  The browser calls the CreateInstance() method to create
/// an instance of your NaCl module on the web page.  The browser creates a new
/// instance for each <embed> tag with type="application/x-pnacl".
class HelloTutorialModule : public pp::Module {
public:
    HelloTutorialModule() : pp::Module() {}
    virtual ~HelloTutorialModule() {}

    /// Create and return a HelloTutorialInstance object.
    /// @param[in] instance The browser-side instance.
    /// @return the plugin-side instance.
    virtual pp::Instance* CreateInstance(PP_Instance instance) {
        return new HelloTutorialInstance(instance);
    }
};

namespace pp {
    /// Factory function called by the browser when the module is first loaded.
    /// The browser keeps a singleton of this module.  It calls the
    /// CreateInstance() method on the object you return to make instances.  There
    /// is one instance per <embed> tag on the page.  This is the main binding
    /// point for your NaCl module with the browser.
    Module* CreateModule() {
        return new HelloTutorialModule();
    }
}  // namespace pp*/