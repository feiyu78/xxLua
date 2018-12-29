/****************************************
 * @Author jinqian @ XXTeam
 * @Repo   https://github.com/xxzhushou
 ****************************************/

#ifdef __cplusplus
#define XMOD_C_API_BEGIN             extern "C" {
#define XMOD_C_API_END               }
#else
#define XMOD_C_API_BEGIN
#define XMOD_C_API_END
#endif

#define XMOD_API                     extern
#define XMOD_INLINE                  inline __attribute__((always_inline))
#define XMOD_HIDDEN                  __attribute__((visibility("hidden")))

#define XMOD_ARG_RSEQ_N()            8, 7, 6, 5, 4, 3, 2, 1, 0
#define XMOD_ARG_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, N, ...) N

#define XMOD_COUNT_ARGS(...)         XMOD_ARG_N(__VA_ARGS__)
#define XMOD_GET_ARG_CNT(...)        XMOD_COUNT_ARGS(0, ##__VA_ARGS__, XMOD_ARG_RSEQ_N())

#define XMOD_CALL_FUNC_A0(_func)     _func()
#define XMOD_CALL_FUNC_A1(_func)     _func(a)
#define XMOD_CALL_FUNC_A2(_func)     _func(a, b)
#define XMOD_CALL_FUNC_A3(_func)     _func(a, b, c)
#define XMOD_CALL_FUNC_A4(_func)     _func(a, b, c, d)
#define XMOD_CALL_FUNC_A5(_func)     _func(a, b, c, d, e)
#define XMOD_CALL_FUNC_A6(_func)     _func(a, b, c, d, e, f)
#define XMOD_CALL_FUNC_A7(_func)     _func(a, b, c, d, e, f, g)
#define XMOD_CALL_FUNC_A8(_func)     _func(a, b, c, d, e, f, g, h)
#define XMOD_CALL_FUNC_A9(_func)     _func(a, b, c, d, e, f, g, h, i)

#define XMOD_CONCAT(A, B)            A##B
#define XMOD_CALL_FUNC_AX(F, N)      XMOD_CONCAT(XMOD_CALL_FUNC_A, N)(F)
#define XMOD_CALL_FUNC(func, ...)    XMOD_CALL_FUNC_AX(func, XMOD_GET_ARG_CNT(__VA_ARGS__))
