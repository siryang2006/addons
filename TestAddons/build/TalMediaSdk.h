#pragma once

#if (defined HELLONODE_EXPORTS) || (defined BUILDING_NODE_EXTENSION)
#define  NODE_MEDIA_API   __declspec(dllexport)
#else
#define NODE_MEDIA_API
#endif

#include <uv.h>
#include <node.h>
#include <v8.h>

using namespace v8;
using namespace node;

class TalMediaSdk {
public:
    static void Init(Local<Object> target);

    TalMediaSdk();
    ~TalMediaSdk();
};
