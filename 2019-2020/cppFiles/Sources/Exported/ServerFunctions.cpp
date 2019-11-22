#include "../../Headers/Exported/ServerFunctions.h"

std::string serverFunctions::helloWorld() {
    return "Hello World!";
}

int serverFunctions::add(int a, int b) {
    return a+b;
}

Point serverFunctions::getPoint() {
    return Point(1.0f,2.0f,3.0f);
}

Napi::String serverFunctions::HelloWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::String returnValue = Napi::String::New(env, serverFunctions::helloWorld());

    return returnValue;
}

Napi::Number serverFunctions::AddWrapped(const Napi::CallbackInfo &info){
    Napi::Env env = info.Env();

    if(info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Number Expected").ThrowAsJavaScriptException();
    }

    Napi::Number first = info[0].As<Napi::Number>();
    Napi::Number second = info[1].As<Napi::Number>();

    int returnVal = serverFunctions::add(first.Int32Value(), second.Int32Value());

    return Napi::Number::New(env, returnVal);
}

//currently still working on this
/*
Napi::Object serverFunctions::GetPointWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if(info.Length() != 0) {
        Napi::TypeError::New(env, "No Arguments Expected").ThrowAsJavaScriptException();
    }

    Point *p = new Point();
    Point get = getPoint();
    p->set(get.X(), get.Y(), get.Z());

    Napi::ObjectWrap<PointWrapper> pt = PointWrapper(p, info);
    Napi::Object res = Napi::Object::New(env);

    res.Set("Point", pt);
    return res;
}
*/

Napi::Object serverFunctions::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("helloWorld", Napi::Function::New(env, serverFunctions::HelloWrapped));
    exports.Set("add", Napi::Function::New(env, serverFunctions::AddWrapped));
    //exports.Set("getPoint", Napi::Function::New(env, serverFunctions::GetPointWrapped));
    return exports;
}