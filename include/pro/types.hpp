#pragma once

#include <napi.h>
#include <oxenc/base64.h>
#include <oxenc/hex.h>

#include "bchat/config/pro.hpp"
#include "bchat/bchat_protocol.hpp"
#include "utilities.hpp"

namespace bchat::nodeapi {

template <>
struct toJs_impl<bchat::ProProof> {
    Napi::Object operator()(const Napi::Env& env, const bchat::ProProof pro_proof) {
        auto obj = Napi::Object::New(env);

        obj["version"] = toJs(env, pro_proof.version);
        obj["genIndexHashB64"] = toJs(env, oxenc::to_base64(pro_proof.gen_index_hash));
        obj["rotatingPubkeyHex"] = toJs(env, oxenc::to_hex(pro_proof.rotating_pubkey));
        obj["expiryMs"] = toJs(env, pro_proof.expiry_unix_ts.time_since_epoch().count());
        obj["signatureHex"] = toJs(env, oxenc::to_hex(pro_proof.sig));

        return obj;
    }
};

template <>
struct toJs_impl<bchat::config::ProConfig> {
    Napi::Value operator()(const Napi::Env& env, const bchat::config::ProConfig pro_config) {
        auto obj = Napi::Object::New(env);

        obj["rotatingPrivKeyHex"] = toJs(env, oxenc::to_hex(pro_config.rotating_privkey));
        obj["proProof"] = toJs(env, pro_config.proof);

        return obj;
    }
};

template <>
struct toJs_impl<bchat::Envelope> {
    Napi::Object operator()(const Napi::Env& env, const bchat::Envelope envelope) {
        auto obj = Napi::Object::New(env);

        obj["timestampMs"] = toJs(env, envelope.timestamp.count());
        obj["source"] = envelope.source.size() ? toJs(env, envelope.source) : env.Null();

        return obj;
    }
};

template <>
struct toJs_impl<bchat::DecodedEnvelope> {
    Napi::Object operator()(const Napi::Env& env, const bchat::DecodedEnvelope decoded_envelope) {
        auto obj = Napi::Object::New(env);

        obj.Set("envelope", toJs(env, decoded_envelope.envelope));
        obj.Set("contentPlaintextUnpadded", toJs(env, decoded_envelope.content_plaintext));
        obj.Set("sessionId",
                toJs(env, "05" + oxenc::to_hex(decoded_envelope.sender_x25519_pubkey)));
        obj.Set("decodedPro", decoded_envelope.pro ? toJs(env, decoded_envelope.pro) : env.Null());

        return obj;
    }
};

template <>
struct toJs_impl<bchat::DecodedPro> {
    Napi::Object operator()(const Napi::Env& env, const bchat::DecodedPro decoded_pro) {
        auto obj = Napi::Object::New(env);

        obj["proStatus"] = toJs(
                env,
                decoded_pro.status == ProStatus::Valid || decoded_pro.status == ProStatus::Expired
                        ? "ValidOrExpired"
                : decoded_pro.status == ProStatus::InvalidProBackendSig ? "InvalidProBackendSig"
                                                                        : "InvalidUserSig");
        obj["proProof"] = toJs(env, decoded_pro.proof);
        obj["proProfileBitset"] = proProfileBitsetToJS(env, decoded_pro.profile_bitset);
        obj["proMessageBitset"] = proMessageBitsetToJS(env, decoded_pro.msg_bitset);

        return obj;
    }
};

};  // namespace bchat::nodeapi