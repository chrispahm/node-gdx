/*
 * gcdllinit.h
 *
 * insert code for DLL initialization routines.  For this to work,
 * there are a number of prerequisites:
 *   1. The symbols GC_DLL_INIT_FUNC and GC_DLL_FINI_FUNC
 *      must be #defined with the names of your init/fini funcs
 *   2. On some systems (e.g. Solaris) the linking command for the .so
 *      must contain the names of these routines.
 *   3. On some systems it may be necessary to specify the build code,
 *      but probably this is already required for any GCLIB use.
 */

#if ! defined(_GCDLLINIT_H_)
#define       _GCDLLINIT_H_

#if ! defined(GC_DLL_INIT_FUNC)
# error "symbol GC_DLL_INIT_FUNC must be defined!"
#endif
#if ! defined(GC_DLL_FINI_FUNC)
# error "symbol GC_DLL_FINI_FUNC must be defined!"
#endif

#if ! defined(GC_EXTERN_C)
# if defined(__cplusplus)
#   define GC_EXTERN_C extern "C"
# else
#   define GC_EXTERN_C
# endif
#endif

GC_EXTERN_C void GC_DLL_INIT_FUNC(void);
GC_EXTERN_C void GC_DLL_FINI_FUNC(void);

#if defined(_WIN32)
/* DllMain: return indicates what? */
BOOL WINAPI
DllMain (HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
  switch (reason) {
  case DLL_PROCESS_ATTACH:
    GC_DLL_INIT_FUNC();
    break;
  case DLL_PROCESS_DETACH:
    GC_DLL_FINI_FUNC();
    break;
  case DLL_THREAD_ATTACH:
    /* ignored */
    break;
  case DLL_THREAD_DETACH:
    /* ignored */
    break;
  }
  return TRUE;
} /* DllMain */

#elif defined(__linux__) || defined(AIX) || defined(BGP)
GC_EXTERN_C void _init (void);  /* shut up warnings */
GC_EXTERN_C void _fini (void);  /* shut up warnings */

GC_EXTERN_C void _init (void)
{
  GC_DLL_INIT_FUNC();
} /* _init */
GC_EXTERN_C void _fini (void)
{
  GC_DLL_FINI_FUNC();
} /* _fini */

#elif defined(__APPLE__)
GC_EXTERN_C void init (void);  /* shut up warnings */
GC_EXTERN_C void fini (void);  /* shut up warnings */

__attribute__((constructor))
GC_EXTERN_C void init (void)
{
  GC_DLL_INIT_FUNC();
} /* init */
__attribute__((destructor))
GC_EXTERN_C void fini (void)
{
  GC_DLL_FINI_FUNC();
} /* fini */

#elif defined(__sparc)
GC_EXTERN_C void GC_sol_initFunc (void);  /* shut up warnings */
GC_EXTERN_C void GC_sol_finiFunc (void);  /* shut up warnings */

GC_EXTERN_C void GC_sol_initFunc (void)
{
  GC_DLL_INIT_FUNC();
} /* GC_sol_initFunc */

GC_EXTERN_C void GC_sol_finiFunc (void)
{
  GC_DLL_FINI_FUNC();
}

#else
# error "No shared library init/fini defined for this build"
#endif

#endif /* defined(_GCDLLINIT_H_) */
