// Conversion to UTF8
// Copyright (c) 2023 KMX Systems. All rights reserved.
#pragma once
#ifndef PCH
    #include <cstdint>
#endif

namespace kmx::to_utf8
{
    /// @param[in] code_point Code point
    /// @param[in] dest Pointer or iterator as destination
    /// @returns Incremented pointer or iterator if conversion succeeded.
    template <typename T>
    T from_utf32(const char32_t code_point, T dest) noexcept
    {
        auto index = code_point < 0x7FF ? (code_point < 0x7F ? 0u : 1u) : (code_point < 0xFFFF ? 2u : code_point < 0x1FFFFF ? 3u : 4u);
        switch (index)
        {
            case 0: // 1 byte
            {
                *dest++ = static_cast<uint8_t>(code_point & 0xFF);
                break;
            }
            case 1: // 2 bytes
            {
                const auto trunc1 = code_point >> 6u;
                const auto trunc2 = code_point % 64u;
                *dest++ = 192u | (trunc1 & 0b111111);
                *dest++ = 128u | (trunc2 & 0b111111);
                break;
            }
            case 2: // 3 bytes
            {
                const auto trunc1 = code_point >> 12u;
                const auto trunc2 = code_point >> 6u;
                const auto trunc3 = code_point % 64u;
                *dest++ = 224u | (trunc1 & 0b1111);
                *dest++ = 128u | (trunc2 & 0b111111);
                *dest++ = 128u | (trunc3 & 0b111111);
                break;
            }
            case 3: // 4 bytes
            {
                const auto trunc4 = code_point % 64u;
                const auto trunc3 = code_point >> 6u;
                const auto trunc2 = code_point >> 12u;
                const auto trunc1 = code_point >> 18u;
                *dest++ = 240u | (trunc1 & 0b1111);
                *dest++ = 128u | (trunc2 & 0b111111);
                *dest++ = 128u | (trunc3 & 0b111111);
                *dest++ = 128u | (trunc4 & 0b111111);
                break;
            }
            default:;
        }

        return dest;
    }
}
