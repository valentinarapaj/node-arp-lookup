#include <napi.h>
#include "networkscanner.h"

Napi::String GetMACAddressFromIP(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string ipAddress = info[0].ToString();
    std::string macAddress = getMACAddressFromIP(ipAddress);
    return Napi::String::New(env, macAddress);
}

Napi::String GetIPFromMACAddress(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string macAddress = info[0].ToString();
    std::string ipAddress = getIPFromMACAddress(macAddress);
    return Napi::String::New(env, ipAddress);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "getMACAddressFromIP"), Napi::Function::New(env, GetMACAddressFromIP));
    exports.Set(Napi::String::New(env, "getIPFromMACAddress"), Napi::Function::New(env, GetIPFromMACAddress));
    return exports;
}

NODE_API_MODULE(arp_lookup, Init)
