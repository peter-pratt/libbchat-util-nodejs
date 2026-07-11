#include <napi.h>

#include <oxen/log.hpp>

#include "blinding/blinding.hpp"
#include "constants.hpp"
#include "contacts_config.hpp"
#include "convo_info_volatile_config.hpp"
#include "encrypt_decrypt/encrypt_decrypt.hpp"
#include "groups/meta_group_wrapper.hpp"
#include "pro/pro.hpp"
#include "user_config.hpp"
#include "user_groups_config.hpp"

Napi::ThreadSafeFunction tsfn;

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {

    tsfn = Napi::ThreadSafeFunction::New(
            env,
            Napi::Function::New(env, [](const Napi::CallbackInfo& info) {}),
            "LoggerCallback",
            0,
            1);

    bchat::add_logger([](std::string_view msg) {
        tsfn.BlockingCall(
                new std::string(msg),
                [](Napi::Env env, Napi::Function jsCallback, std::string* msg) {
                    Napi::HandleScope scope(env);
                    Napi::Function consoleLog = env.Global()
                                                        .Get("console")
                                                        .As<Napi::Object>()
                                                        .Get("log")
                                                        .As<Napi::Function>();
                    Napi::String jsStr = Napi::String::New(env, "libbchat: " + *msg);
                    consoleLog.Call({jsStr});
                    delete msg;
                });
    });
    oxen::log::set_level_default(oxen::log::Level::info);

    bchat::nodeapi::ConstantsWrapper::Init(env, exports);

    // Group wrappers init
    bchat::nodeapi::MetaGroupWrapper::Init(env, exports);

    // User wrappers init
    bchat::nodeapi::UserConfigWrapper::Init(env, exports);
    bchat::nodeapi::ContactsConfigWrapper::Init(env, exports);
    bchat::nodeapi::UserGroupsWrapper::Init(env, exports);
    bchat::nodeapi::ConvoInfoVolatileWrapper::Init(env, exports);

    // Fully static wrappers init
    bchat::nodeapi::MultiEncryptWrapper::Init(env, exports);
    bchat::nodeapi::ProWrapper::Init(env, exports);
    bchat::nodeapi::BlindingWrapper::Init(env, exports);

    return exports;
}

NODE_API_MODULE(libbchat_util_nodejs, InitAll);
