/* AdjacentLanePermute_x86_128.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 08/30/2015
 * Last Modified    : 06/22/2019
 * 
 */

#pragma once
#ifndef ymp_AdjacentLanePermute_x86_128_H
#define ymp_AdjacentLanePermute_x86_128_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <emmintrin.h>
#include "PublicLibs/CompilerSettings.h"
#include "PublicLibs/SystemLibs/ProcessorCapability/ProcessorCapability_x86.h"
#ifdef YMP_Arch_2007_x64_Penryn
#include <smmintrin.h>
#endif
namespace ymp{
namespace SIMD{
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Double
YM_FORCE_INLINE __m128d mm_splitload_pd(const void* L, const void* H){
    return _mm_loadh_pd(_mm_load_sd((const double*)(L)), (const double*)(H));
}
YM_FORCE_INLINE void mm_splitstore_pd(void* L, void* H, __m128d x){
    _mm_storel_pd((double*)(L), x);
    _mm_storeh_pd((double*)(H), x);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Float
YM_FORCE_INLINE __m128 mm_permuteaj32_00(__m128 a, __m128 b){
    a = _mm_shuffle_ps(a, b, 136);
    return _mm_shuffle_ps(a, a, 216);
}
YM_FORCE_INLINE __m128 mm_permuteaj32_11(__m128 a, __m128 b){
    a = _mm_shuffle_ps(a, b, 221);
    return _mm_shuffle_ps(a, a, 216);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Integer
YM_FORCE_INLINE __m128i mm_permuteaj32_00(__m128i a, __m128i b){
#ifdef YMP_Arch_2007_x64_Penryn
    b = _mm_shuffle_epi32(b, 177);
    return _mm_blend_epi16(a, b, 0xcc);
#else
    return _mm_castps_si128(mm_permuteaj32_00(_mm_castsi128_ps(a), _mm_castsi128_ps(b)));
#endif
}
YM_FORCE_INLINE __m128i mm_permuteaj32_11(__m128i a, __m128i b){
#ifdef YMP_Arch_2007_x64_Penryn
    a = _mm_shuffle_epi32(a, 177);
    return _mm_blend_epi16(a, b, 0xcc);
#else
    return _mm_castps_si128(mm_permuteaj32_11(_mm_castsi128_ps(a), _mm_castsi128_ps(b)));
#endif
}
////////////////////////////////////////////////////////////////////////////////
YM_FORCE_INLINE __m128i mm_permuteaj64_00(__m128i a, __m128i b){
    return _mm_unpacklo_epi64(a, b);
}
YM_FORCE_INLINE __m128i mm_permuteaj64_11(__m128i a, __m128i b){
    return _mm_unpackhi_epi64(a, b);
}
////////////////////////////////////////////////////////////////////////////////
YM_FORCE_INLINE __m128i mm_splitload_si128(const void* L, const void* H){
    return _mm_castpd_si128(mm_splitload_pd(L, H));
}
YM_FORCE_INLINE void mm_splitstore_si128(void* L, void* H, __m128i x){
    mm_splitstore_pd(L, H, _mm_castsi128_pd(x));
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
}
}
#endif
