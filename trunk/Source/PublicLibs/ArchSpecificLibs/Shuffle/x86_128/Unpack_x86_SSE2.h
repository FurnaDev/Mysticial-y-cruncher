/* Unpack_x86_SSE2.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 08/30/2015
 * Last Modified    : 08/30/2015
 * 
 */

#pragma once
#ifndef ymp_Unpack_x86_SSE2_H
#define ymp_Unpack_x86_SSE2_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <emmintrin.h>
#include "PublicLibs/CompilerSettings.h"
#include "Unpack_x86_SSE.h"
namespace ymp{
namespace SIMD{
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
YM_FORCE_INLINE __m128d load2_m64d_SSE2(const void* L, const void* H){
    return _mm_loadh_pd(_mm_load_sd((const double*)(L)), (const double*)(H));
}
YM_FORCE_INLINE void store2_m64d_SSE2(void* L, void* H, __m128d x){
    _mm_storel_pd((double*)(L), x);
    _mm_storeh_pd((double*)(H), x);
}
YM_FORCE_INLINE __m128i load2_m64i_SSE2(const void* L, const void* H){
    return _mm_castpd_si128(load2_m64d_SSE2(L, H));
}
YM_FORCE_INLINE void store2_m64i_SSE2(void* L, void* H, __m128i x){
    store2_m64d_SSE2(L, H, _mm_castsi128_pd(x));
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Integer
template <int bits> YM_FORCE_INLINE __m128i unpacklo_SSE2(__m128i a, __m128i b);
template <int bits> YM_FORCE_INLINE __m128i unpackhi_SSE2(__m128i a, __m128i b);
////////////////////////////////////////////////////////////////////////////////
template <> YM_FORCE_INLINE __m128i unpacklo_SSE2<32>(__m128i a, __m128i b){
    return _mm_castps_si128(unpacklo_f32_SSE<1>(_mm_castsi128_ps(a), _mm_castsi128_ps(b)));
}
template <> YM_FORCE_INLINE __m128i unpackhi_SSE2<32>(__m128i a, __m128i b){
    return _mm_castps_si128(unpackhi_f32_SSE<1>(_mm_castsi128_ps(a), _mm_castsi128_ps(b)));
}
////////////////////////////////////////////////////////////////////////////////
template <> YM_FORCE_INLINE __m128i unpacklo_SSE2<64>(__m128i a, __m128i b){
    return _mm_unpacklo_epi64(a, b);
}
template <> YM_FORCE_INLINE __m128i unpackhi_SSE2<64>(__m128i a, __m128i b){
    return _mm_unpackhi_epi64(a, b);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
}
}
#endif