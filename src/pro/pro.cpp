#include "pro/pro.hpp"

namespace bchat::nodeapi {

std::string_view ProBackendEnumToString(BCHAT_PRO_BACKEND_PAYMENT_PROVIDER v) {
    switch (v) {
        case BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_NIL: return "NIL";
        case BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_GOOGLE_PLAY_STORE: return "GOOGLE_PLAY_STORE";
        case BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_IOS_APP_STORE: return "IOS_APP_STORE";
        case BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_RANGEPROOF: return "RANGEPROOF";
        case BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_COUNT:
            throw std::invalid_argument("BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_COUNT");
    }
    UNREACHABLE();
}

std::string_view ProBackendEnumToString(BCHAT_PRO_BACKEND_PAYMENT_STATUS v) {
    switch (v) {
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_NIL: return "NIL";
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_UNREDEEMED: return "UNREDEEMED";
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_REDEEMED: return "REDEEMED";
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_EXPIRED: return "EXPIRED";
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_REFUNDED: return "REFUNDED";
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_COUNT:
            throw std::invalid_argument("BCHAT_PRO_BACKEND_PAYMENT_STATUS_COUNT");
    }
    UNREACHABLE();
}

std::string_view proBackendEnumToString(BCHAT_PRO_BACKEND_PLAN v) {
    switch (v) {
        case BCHAT_PRO_BACKEND_PLAN_NIL: return "NIL";
        case BCHAT_PRO_BACKEND_PLAN_ONE_MONTH: return "ONE_MONTH";
        case BCHAT_PRO_BACKEND_PLAN_THREE_MONTHS: return "THREE_MONTHS";
        case BCHAT_PRO_BACKEND_PLAN_TWELVE_MONTHS: return "TWELVE_MONTHS";
        case BCHAT_PRO_BACKEND_PLAN_COUNT:
            throw std::invalid_argument("BCHAT_PRO_BACKEND_PLAN_COUNT");
    }
    UNREACHABLE();
}

std::string_view proBackendEnumToString(BCHAT_PRO_BACKEND_USER_PRO_STATUS v) {
    switch (v) {
        case BCHAT_PRO_BACKEND_USER_PRO_STATUS_NEVER_BEEN_PRO: return "NEVER_BEEN_PRO";
        case BCHAT_PRO_BACKEND_USER_PRO_STATUS_ACTIVE: return "ACTIVE";
        case BCHAT_PRO_BACKEND_USER_PRO_STATUS_EXPIRED: return "EXPIRED";
        case BCHAT_PRO_BACKEND_USER_PRO_STATUS_COUNT:
            throw std::invalid_argument("BCHAT_PRO_BACKEND_USER_PRO_STATUS_COUNT");
    }
    UNREACHABLE();
}

std::string_view ProBackendEnumToString(BCHAT_PRO_BACKEND_GET_PRO_DETAILS_ERROR_REPORT v) {
    switch (v) {
        case BCHAT_PRO_BACKEND_GET_PRO_DETAILS_ERROR_REPORT_SUCCESS: return "SUCCESS";
        case BCHAT_PRO_BACKEND_GET_PRO_DETAILS_ERROR_REPORT_GENERIC_ERROR: return "GENERIC_ERROR";
        case BCHAT_PRO_BACKEND_GET_PRO_DETAILS_ERROR_REPORT_COUNT:
            throw std::invalid_argument("BCHAT_PRO_BACKEND_GET_PRO_DETAILS_ERROR_REPORT");
    }
    UNREACHABLE();
}

std::string_view proBackendEnumPlanToString(BCHAT_PRO_BACKEND_PLAN v) {
    switch (v) {
        case BCHAT_PRO_BACKEND_PLAN_NIL: return "NIL";
        case BCHAT_PRO_BACKEND_PLAN_ONE_MONTH: return "ONE_MONTH";
        case BCHAT_PRO_BACKEND_PLAN_THREE_MONTHS: return "THREE_MONTHS";
        case BCHAT_PRO_BACKEND_PLAN_TWELVE_MONTHS: return "TWELVE_MONTHS";
        case BCHAT_PRO_BACKEND_PLAN_COUNT:
            throw std::invalid_argument("BCHAT_PRO_BACKEND_PLAN_COUNT");
    }
    UNREACHABLE();
}

std::string_view proBackendEnumPaymentProviderToString(BCHAT_PRO_BACKEND_PAYMENT_PROVIDER v) {
    switch (v) {
        // Note: we want those to map ProOriginatingPlatform keys
        case BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_NIL: return "Nil";
        case BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_GOOGLE_PLAY_STORE: return "GooglePlayStore";
        case BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_IOS_APP_STORE: return "iOSAppStore";
        case BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_RANGEPROOF: return "Rangeproof";
        case BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_COUNT:
            throw std::invalid_argument("BCHAT_PRO_BACKEND_PAYMENT_PROVIDER_COUNT");
    }
    UNREACHABLE();
}

std::string_view proBackendEnumPaymentStatusToString(BCHAT_PRO_BACKEND_PAYMENT_STATUS v) {
    switch (v) {
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_NIL: return "NIL";
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_UNREDEEMED: return "UNREDEEMED";
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_REDEEMED: return "REDEEMED";
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_EXPIRED: return "EXPIRED";
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_REFUNDED: return "REFUNDED";
        case BCHAT_PRO_BACKEND_PAYMENT_STATUS_COUNT:
            throw std::invalid_argument("BCHAT_PRO_BACKEND_PAYMENT_STATUS_COUNT");
    }
    UNREACHABLE();
}

std::string_view proBackendEnumToString(bchat::ProFeaturesForMsgStatus v) {
    switch (v) {
        case bchat::ProFeaturesForMsgStatus::Success: return "SUCCESS";
        case bchat::ProFeaturesForMsgStatus::UTFDecodingError: return "UTF_DECODING_ERROR";
        case bchat::ProFeaturesForMsgStatus::ExceedsCharacterLimit:
            return "EXCEEDS_CHARACTER_LIMIT";
    }
    UNREACHABLE();
}

}  // namespace bchat::nodeapi
