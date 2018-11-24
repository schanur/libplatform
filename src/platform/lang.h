#ifndef PLTF_LANG_H
#define PLTF_LANG_H

/**
 * Macros to handle things the same way under C and C++.
 */

#define PLTF_C   1
#define PLTF_CPP 2

#ifdef __cplusplus
  #define PLTF_LANG PLTF_CPP
#else
  #define PLTF_LANG PLTF_C
#endif


#if PLTF_LANG == PLTF_C
  #define PLTF_LANG_TYPE_CAST(type, value) (type)(value)
#else
  #define PLTF_LANG_TYPE_CAST(type, value) static_cast<char>(value)
#endif

#endif /* PLTF_LANG_H */
