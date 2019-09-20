#include "../Headers/ServerFunctions.h"
#include <napi.h>

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    return serverFunctions::Init(env, exports);
}

NODE_API_MODULE(testaddon, InitAll)