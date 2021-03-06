#ifndef NLOHMANN_JSON_DETAIL_MACRO_UNSCOPE_HPP
#define NLOHMANN_JSON_DETAIL_MACRO_UNSCOPE_HPP

// restore GCC/clang diagnostic settings
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
    #pragma GCC diagnostic pop
#endif
#if defined(__clang__)
    #pragma GCC diagnostic pop
#endif

// clean up
#undef JSON_CATCH
#undef JSON_THROW
#undef JSON_TRY
#undef JSON_LIKELY
#undef JSON_UNLIKELY
#undef JSON_DEPRECATED
#undef NLOHMANN_BASIC_JSON_TPL_DECLARATION
#undef NLOHMANN_BASIC_JSON_TPL
#undef NLOHMANN_JSON_HAS_HELPER
#undef JSON_HAS_CPP_17
#undef JSON_HAS_CPP_14

#endif
