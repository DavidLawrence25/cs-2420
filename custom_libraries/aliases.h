#include <concepts>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#ifndef CS2420_CUSTOMLIBRARIES_ALIASES_H_
#define CS2420_CUSTOMLIBRARIES_ALIASES_H_

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

static const u8 kU8Max = UINT8_MAX;
static const u16 kU16Max = UINT16_MAX;
static const u32 kU32Max = UINT32_MAX;
static const u64 kU64Max = UINT64_MAX;

using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

static const s8 kS8Min = INT8_MIN;
static const s8 kS8Max = INT8_MAX;
static const s16 kS16Min = INT16_MIN;
static const s16 kS16Max = INT16_MAX;
static const s32 kS32Min = INT32_MIN;
static const s32 kS32Max = INT32_MAX;
static const s64 kS64Min = INT64_MIN;
static const s64 kS64Max = INT64_MAX;

using f32 = float;
using f64 = double;

using uindex_t = size_t;
using index_t = s64;

template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T>
using sptr = std::shared_ptr<T>;

template <typename T>
using opt = std::optional<T>;

using std::vector;

template <typename T>
concept Arithmetic = std::convertible_to<T, u64>;

#endif  // CS2420_CUSTOMLIBRARIES_ALIASES_H_
