#pragma once

#include <napi.h>

#include <vector>

#include "bchat/config/groups/info.hpp"
#include "bchat/config/groups/keys.hpp"
#include "bchat/config/groups/members.hpp"

namespace bchat::nodeapi {

using config::groups::Info;
using config::groups::Keys;
using config::groups::Members;
using bchat::config::profile_pic;
using std::pair;
using std::string;
using std::tuple;
using std::vector;

using std::make_shared;
using std::shared_ptr;

class MetaGroup {
  public:
    shared_ptr<config::groups::Info> info;
    shared_ptr<config::groups::Members> members;
    shared_ptr<config::groups::Keys> keys;
    string edGroupPubKey;
    std::optional<string> edGroupSecKey;

    MetaGroup(
            shared_ptr<config::groups::Info> info,
            shared_ptr<config::groups::Members> members,
            shared_ptr<config::groups::Keys> keys,
            std::vector<unsigned char> edGroupPubKey,
            std::optional<std::vector<unsigned char>> edGroupSecKey) :
            info{info},
            members{members},
            keys{keys},
            edGroupPubKey{oxenc::to_hex(edGroupPubKey.begin(), edGroupPubKey.end())} {

        if (edGroupSecKey.has_value()) {
            this->edGroupSecKey = oxenc::to_hex(edGroupSecKey->begin(), edGroupSecKey->end());
        } else {
            this->edGroupSecKey = std::nullopt;
        }
    }
};
}  // namespace bchat::nodeapi