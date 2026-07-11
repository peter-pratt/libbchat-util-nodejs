#pragma once

#include <napi.h>

#include <algorithm>
#include <vector>

#include "../meta/meta_base_wrapper.hpp"
#include "../utilities.hpp"
#include "oxenc/hex.h"
#include "bchat/blinding.hpp"
#include "bchat/config/user_profile.hpp"
#include "bchat/platform.hpp"
#include "bchat/random.hpp"

namespace bchat::nodeapi {

class BlindingWrapper : public Napi::ObjectWrap<BlindingWrapper> {

  public:
    BlindingWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<BlindingWrapper>{info} {
        throw std::invalid_argument("BlindingWrapper is static and doesn't need to be constructed");
    }

    static void Init(Napi::Env env, Napi::Object exports) {
        MetaBaseWrapper::NoBaseClassInitHelper<BlindingWrapper>(
                env,
                exports,
                "BlindingWrapperNode",
                {
                        StaticMethod<&BlindingWrapper::blindVersionPubkey>(
                                "blindVersionPubkey",
                                static_cast<napi_property_attributes>(
                                        napi_writable | napi_configurable)),
                        StaticMethod<&BlindingWrapper::blindVersionSignRequest>(
                                "blindVersionSignRequest",
                                static_cast<napi_property_attributes>(
                                        napi_writable | napi_configurable)),
                });
    }

  private:
    static Napi::Value blindVersionPubkey(const Napi::CallbackInfo& info) {
        return wrapResult(info, [&] {
            assertInfoLength(info, 1);
            assertIsObject(info[0]);
            auto obj = info[0].As<Napi::Object>();

            if (obj.IsEmpty())
                throw std::invalid_argument("blindVersionPubkey received empty");

            assertIsUInt8Array(obj.Get("ed25519SecretKey"), "BlindingWrapper::blindVersionPubkey");
            auto ed25519_secret_key =
                    toCppBuffer(obj.Get("ed25519SecretKey"), "blindVersionPubkey.ed25519SecretKey");

            auto keypair = bchat::blind_version_key_pair(ed25519_secret_key);
            bchat::uc32 pk_arr = std::get<0>(keypair);
            std::vector<unsigned char> blinded_pk = bchat::to_vector(pk_arr);
            std::string blinded_pk_hex;
            blinded_pk_hex.reserve(66);
            blinded_pk_hex += "07";
            oxenc::to_hex(blinded_pk.begin(), blinded_pk.end(), std::back_inserter(blinded_pk_hex));

            return blinded_pk_hex;
        });
    };

    static Napi::Value blindVersionSignRequest(const Napi::CallbackInfo& info) {
        return wrapResult(info, [&] {
            assertInfoLength(info, 1);
            assertIsObject(info[0]);
            auto obj = info[0].As<Napi::Object>();

            if (obj.IsEmpty())
                throw std::invalid_argument("blindVersionSignRequest received empty");

            assertIsUInt8Array(
                    obj.Get("ed25519SecretKey"), "blindVersionSignRequest.ed25519SecretKey");
            auto ed25519_secret_key = toCppBuffer(
                    obj.Get("ed25519SecretKey"), "blindVersionSignRequest.ed25519SecretKey");

            assertIsNumber(
                    obj.Get("sigTimestampSeconds"), "blindVersionSignRequest.sigTimestampSeconds");
            auto sig_timestamp = toCppInteger(
                    obj.Get("sigTimestampSeconds"),
                    "blindVersionSignRequest.sigTimestampSeconds",
                    false);

            assertIsString(obj.Get("sigMethod"));
            auto sig_method =
                    toCppString(obj.Get("sigMethod"), "blindVersionSignRequest.sigMethod");

            assertIsString(obj.Get("sigPath"));
            auto sig_path = toCppString(obj.Get("sigPath"), "blindVersionSignRequest.sigPath");

            assertIsUInt8ArrayOrNull(obj.Get("sigBody"));
            auto sig_body =
                    maybeNonemptyBuffer(obj.Get("sigBody"), "blindVersionSignRequest.sigBody");

            return bchat::blind_version_sign_request(
                    ed25519_secret_key, sig_timestamp, sig_method, sig_path, sig_body);
        });
    };
};
}  // namespace bchat::nodeapi
