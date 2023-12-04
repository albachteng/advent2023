#define sizeof(x) (size)sizeof(x)

#define alignof(x) (size) _Alignof(x)
#define countof(a) (sizeof(a) / sizeof(*(a)))
#define lengthof(s) (countof(s) - 1)

// #define assert(c)                                                              \
//   while (!(c))                                                                 \
//   __builtin_unreachable()

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define clamp(a, x, b) (((x) < (a)) ? (a) : ((b) < (x)) ? (b) : (x))

#define global static
#define local_persist static
#define function static
