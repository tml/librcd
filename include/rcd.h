/* Copyright © 2014, Jumpstarter AB. This file is part of the librcd project.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
/* See the COPYING file distributed with this project for more information. */

#ifndef RCD_H
#define RCD_H

// Hard coded feature macro that librcd uses to enable all other feature macros.
// Feature macros is not used but librcd itself but used and defined by musl.h,
// the librcd libc compability layer.
#define _ALL_SOURCE

#define typeof(x) __typeof__(x)
#define offsetof(t, d) __builtin_offsetof(t, d)
#define unreachable() assert(false), __builtin_unreachable()
#define readcyclecounter() __builtin_readcyclecounter()
#define sync_synchronize() __sync_synchronize()
#define sync_bool_compare_and_swap(ptr, oldval, newval) __sync_bool_compare_and_swap(ptr, oldval, newval)
#define return_address(n) __builtin_return_address(n)
#define frame_address(n) __builtin_frame_address(n)

// Compilers are poor at understanding the true overhead of a function
// call when segmented stacks are used so force explicit inline
// declarations to have effect.
#define inline inline __attribute__((always_inline))
#define __inline inline
#define __inline__ inline

/// We reserve "noret" as a short readable syntax for the noreturn attribute.
/// Having noreturn declared functions can be important in application code as
/// well to suppress return type errors. Having a shorthand for this therefore
/// improves readability where readability is important.
#define noret __attribute__((noreturn))

#define bool _Bool
#define true ((bool)1)
#define false ((bool)0)

#define LENGTHOF(static_c_array) (sizeof(static_c_array) / sizeof(*static_c_array))
#define MIN(x, y) ({typeof(x) _x = (x), _y = (y); _x < _y ? _x : _y;})
#define MAX(x, y) ({typeof(x) _x = (x), _y = (y); _x > _y ? _x : _y;})
#define FLIP(x, y) ({typeof(x) _flip = x; x = y; y = _flip;;})

#define INT8_MIN   (-1-0x7f)
#define INT16_MIN  (-1-0x7fff)
#define INT32_MIN  (-1-0x7fffffff)
#define INT64_MIN  (-1-0x7fffffffffffffffLL)

#define INT8_MAX   (0x7f)
#define INT16_MAX  (0x7fff)
#define INT32_MAX  (0x7fffffff)
#define INT64_MAX  (0x7fffffffffffffffLL)

#define UINT8_MAX  (0xff)
#define UINT16_MAX (0xffff)
#define UINT32_MAX (0xffffffff)
#define UINT64_MAX (0xffffffffffffffffULL)

#define INT128_MAX (((int128_t) INT64_MAX) << 64 | ((int128_t) UINT64_MAX))
#define INT128_MIN  (((int128_t) -1) - INT128_MAX)
#define UINT128_MAX (((uint128_t) UINT64_MAX) << 64 | ((uint128_t) UINT64_MAX))

#define INT_LEAST8_MIN   INT8_MIN
#define INT_LEAST16_MIN  INT16_MIN
#define INT_LEAST32_MIN  INT32_MIN
#define INT_LEAST64_MIN  INT64_MIN

#define INT_LEAST8_MAX   INT8_MAX
#define INT_LEAST16_MAX  INT16_MAX
#define INT_LEAST32_MAX  INT32_MAX
#define INT_LEAST64_MAX  INT64_MAX

#define UINT_LEAST8_MAX  UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

#define INTMAX_MIN  INT64_MIN
#define INTMAX_MAX  INT64_MAX
#define UINTMAX_MAX UINT64_MAX

#define WINT_MIN INT32_MIN
#define WINT_MAX INT32_MAX

#define INT8_C(c)  c
#define INT16_C(c) c
#define INT32_C(c) c
#define INT64_C(c) c ## LL

#define UINT8_C(c)  c
#define UINT16_C(c) c
#define UINT32_C(c) c ## U
#define UINT64_C(c) c ## ULL

#define INTMAX_C(c)  c ## LL
#define UINTMAX_C(c) c ## ULL

#define INT_FAST8_MIN   INT8_MIN
#define INT_FAST16_MIN  INT32_MIN
#define INT_FAST32_MIN  INT32_MIN
#define INT_FAST64_MIN  INT64_MIN

#define INT_FAST8_MAX   INT8_MAX
#define INT_FAST16_MAX  INT32_MAX
#define INT_FAST32_MAX  INT32_MAX
#define INT_FAST64_MAX  INT64_MAX

#define UINT_FAST8_MAX  UINT8_MAX
#define UINT_FAST16_MAX UINT32_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define UINT_FAST64_MAX UINT64_MAX

#define INTPTR_MIN      INT64_MIN
#define INTPTR_MAX      INT64_MAX
#define UINTPTR_MAX     UINT64_MAX
#define PTRDIFF_MIN     INT64_MIN
#define PTRDIFF_MAX     INT64_MAX
#define SIG_ATOMIC_MIN  INT64_MIN
#define SIG_ATOMIC_MAX  INT64_MAX
#define SIZE_MAX        UINT64_MAX

#define MB_LEN_MAX 4

#define CHAR_MIN (-128)
#define CHAR_MAX 127

#define CHAR_BIT 8
#define SCHAR_MIN INT8_MIN
#define SCHAR_MAX INT8_MAX
#define UCHAR_MAX UINT8_MAX
#define SHRT_MIN  INT16_MIN
#define SHRT_MAX  INT16_MAX
#define USHRT_MAX UINT16_MAX
#define INT_MIN  INT32_MIN
#define INT_MAX  INT32_MAX
#define UINT_MAX UINT32_MAX
#define LONG_MIN INT64_MIN
#define LONG_MAX  INT64_MAX
#define ULONG_MAX UINT64_MAX
#define LLONG_MIN INT64_MIN
#define LLONG_MAX  INT64_MAX
#define ULLONG_MAX UINT64_MAX

// Templating macros.
#define _FOR_EACH_ARG_0(F, ...) _ASSERT_EMPTY(__VA_ARGS__)
#define _FOR_EACH_ARG_1(F, a) F(a)
#define _FOR_EACH_ARG_2(F, a, ...) F(a) _FOR_EACH_ARG_1(F, __VA_ARGS__)
#define _FOR_EACH_ARG_3(F, a, ...) F(a) _FOR_EACH_ARG_2(F, __VA_ARGS__)
#define _FOR_EACH_ARG_4(F, a, ...) F(a) _FOR_EACH_ARG_3(F, __VA_ARGS__)
#define _FOR_EACH_ARG_5(F, a, ...) F(a) _FOR_EACH_ARG_4(F, __VA_ARGS__)
#define _FOR_EACH_ARG_6(F, a, ...) F(a) _FOR_EACH_ARG_5(F, __VA_ARGS__)
#define _FOR_EACH_ARG_7(F, a, ...) F(a) _FOR_EACH_ARG_6(F, __VA_ARGS__)
#define _FOR_EACH_ARG_8(F, a, ...) F(a) _FOR_EACH_ARG_7(F, __VA_ARGS__)
#define _FOR_EACH_ARG_9(F, a, ...) F(a) _FOR_EACH_ARG_8(F, __VA_ARGS__)
#define _FOR_EACH_ARG_10(F, a, ...) F(a) _FOR_EACH_ARG_9(F, __VA_ARGS__)
#define _FOR_EACH_ARG_11(F, a, ...) F(a) _FOR_EACH_ARG_10(F, __VA_ARGS__)
#define _FOR_EACH_ARG_12(F, a, ...) F(a) _FOR_EACH_ARG_11(F, __VA_ARGS__)
#define _FOR_EACH_ARG_13(F, a, ...) F(a) _FOR_EACH_ARG_12(F, __VA_ARGS__)
#define _FOR_EACH_ARG_14(F, a, ...) F(a) _FOR_EACH_ARG_13(F, __VA_ARGS__)
#define _FOR_EACH_ARG_15(F, a, ...) F(a) _FOR_EACH_ARG_14(F, __VA_ARGS__)
#define _FOR_EACH_ARG_16(F, a, ...) F(a) _FOR_EACH_ARG_15(F, __VA_ARGS__)
#define _FOR_EACH_ARG_17(F, a, ...) F(a) _FOR_EACH_ARG_16(F, __VA_ARGS__)
#define _FOR_EACH_ARG_18(F, a, ...) F(a) _FOR_EACH_ARG_17(F, __VA_ARGS__)
#define _FOR_EACH_ARG_19(F, a, ...) F(a) _FOR_EACH_ARG_18(F, __VA_ARGS__)
#define _FOR_EACH_ARG_20(F, a, ...) F(a) _FOR_EACH_ARG_19(F, __VA_ARGS__)
#define _FOR_EACH_ARG_21(F, a, ...) F(a) _FOR_EACH_ARG_20(F, __VA_ARGS__)
#define _FOR_EACH_ARG_22(F, a, ...) F(a) _FOR_EACH_ARG_21(F, __VA_ARGS__)
#define _FOR_EACH_ARG_23(F, a, ...) F(a) _FOR_EACH_ARG_22(F, __VA_ARGS__)
#define _FOR_EACH_ARG_24(F, a, ...) F(a) _FOR_EACH_ARG_23(F, __VA_ARGS__)
#define _FOR_EACH_ARG_25(F, a, ...) F(a) _FOR_EACH_ARG_24(F, __VA_ARGS__)
#define _FOR_EACH_ARG_26(F, a, ...) F(a) _FOR_EACH_ARG_25(F, __VA_ARGS__)
#define _FOR_EACH_ARG_27(F, a, ...) F(a) _FOR_EACH_ARG_26(F, __VA_ARGS__)
#define _FOR_EACH_ARG_28(F, a, ...) F(a) _FOR_EACH_ARG_27(F, __VA_ARGS__)
#define _FOR_EACH_ARG_29(F, a, ...) F(a) _FOR_EACH_ARG_28(F, __VA_ARGS__)
#define _FOR_EACH_ARG_30(F, a, ...) F(a) _FOR_EACH_ARG_29(F, __VA_ARGS__)
#define _FOR_EACH_ARG_31(F, a, ...) F(a) _FOR_EACH_ARG_30(F, __VA_ARGS__)
#define _FOR_EACH_ARG_32(F, a, ...) F(a) _FOR_EACH_ARG_31(F, __VA_ARGS__)

#define _SECOND_ARG(_, a, ...) a
#define _ASSERT_EMPTY_IMPL(_)
#define _ASSERT_EMPTY(...) _ASSERT_EMPTY_IMPL(_, ##__VA_ARGS__)
#define _GLUE_IMPL(a, b) a ## b
#define _VA_NARGS_IMPL(_, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, N, ...) N

/// Returns the number of arguments passed in.
#define VA_NARGS(...) _VA_NARGS_IMPL(_, ##__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

/// Expands two preprocessor tokens and glues them together.
#define GLUE(a, b) _GLUE_IMPL(a, b)

/// Repeats a macro once for each argument passed in.
#define FOR_EACH_ARG(F, ...) GLUE(_FOR_EACH_ARG_, VA_NARGS(__VA_ARGS__))(F, __VA_ARGS__)

/// Declare variable(s) within an inner scope.
#define LET(...) \
    /* (Implementation note: The empty condition + 'break' proves to clang that */ \
    /* the loop will run exactly once, avoiding warnings about missing returns */ \
    /* after the block when there are unconditional returns within it. The behavior */ \
    /* of "break" within the for loop's update expression that we rely upon is */ \
    /* clang-specific - gcc would rather try to break of an outer loop.) */ \
    for(__VA_ARGS__; ; ({break;}))

/// Hack for making clang not think a branch exists for the purpose of generating warnings.
#define _CLANG_HIDE_CONTROL_FLOW(stmts) { \
    enum __rcd_single_enum { __rcd_single_enum_value = 1 }; \
    switch((enum __rcd_single_enum)0) { \
        default: stmts; \
        case __rcd_single_enum_value: break; \
    } \
}

__attribute__((const, always_inline))
static inline float __get_nan_float() {
    return __builtin_nanf("");
}

#define NAN __get_nan_float()
#define INFINITY __builtin_inff()

// Some nice keywords for rapid c development.
#define new(type) ({type* p = lwt_alloc_new(sizeof(type)); *p = (type){0}; p;})
#define cln(ptr) ({typeof(*ptr)* p = 0; if (ptr != 0) {p = lwt_alloc_new(sizeof(*ptr)); *p = *ptr;} p;})
#define str(x) STR(x)
#define conc(...) FSTR_CONCAT_ANY(__VA_ARGS__)
#define concs(...) fss(conc(__VA_ARGS__))
#define sconc(...) ({fstr_t s; sub_heap{s = fss(escape(conc(__VA_ARGS__)));}; s;})
#define fss(fstr_mem_ptr) (fstr_str(fstr_mem_ptr))
#define fsc(fstr) fss(fstr_cpy(fstr))
#define i2fs(integer) fss(fstr_from_int(integer, 10))
#define ui2fs(unsigned_integer) fss(fstr_from_uint(unsigned_integer, 10))
#define fs2i(fstr) (fstr_to_int(fstr, 10))
#define fs2ui(fstr) (fstr_to_uint(fstr, 10))
#define sfid(sub_fiber) (lwt_get_sub_fiber_id(sub_fiber))
#define rcd_self (lwt_get_fiber_id())

typedef unsigned long size_t;
typedef long ssize_t;
typedef long ptrdiff_t;
typedef __builtin_va_list va_list;

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;
typedef int int128_t __attribute__((mode(TI), aligned(16)));
/*typedef int int256_t __attribute__((mode(OI)));*/

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef unsigned int uint128_t __attribute__((mode(TI), aligned(16)));
/*typedef unsigned int uint256_t __attribute__((mode(OI)));*/
typedef long intptr_t;
typedef unsigned long uintptr_t;

typedef float float_t;
typedef double double_t;

typedef long long intmax_t;
typedef unsigned long uintmax_t;

// Alloca is actually just normal heap allocation that gets free'd when unwinding the function.
void* alloca(size_t);
#define alloca __builtin_alloca

void* memcpy(void *__restrict, const void *__restrict, size_t);

/// Core stack helper adjusts the overflow_arg_area for split stacks support.
void __morestack_adjust_overflow_arg_area(va_list va_list);

/// Implementation of variadic function macros, with segm stack support.
#define va_start(v,l) ({ \
    __builtin_va_start(v,l); \
    __morestack_adjust_overflow_arg_area(v); \
})
#define va_end(v) __builtin_va_end(v)
#define va_arg(v,l) __builtin_va_arg(v,l)
#define va_copy(d,s) __builtin_va_copy(d,s)

/// Protection against null pointers at compile time.
#define NO_NULL_ARGS __attribute__((nonnull))
#define NOT_NULL_ARGS(...) __attribute__((nonnull(__VA_ARGS__)))

/// Basic list pseudo-type macro. Further defined in list.h.
#define list(type) \
    struct __rcd_list__##type

/// Basic dict pseudo-type macro. Further defined in list.h.
#define dict(type) \
    struct __rcd_dict__##type

/// Typed sub fiber.
#define sf(sf_t_name) struct sf_t_name##__rcd_sf_t

/// The typed variant of sfid().
/// Converts a typed sub fiber to a rcd_fid_t so it can be used for joins etc.
#define sf2id(sf_t_name, sf_ref) ({sf(sf_t_name)* __typed_sf_ref = (sf_ref); lwt_get_sub_fiber_id((rcd_sub_fiber_t*) __typed_sf_ref);})

/// Typed fiber id.
#define fid(sf_t_name) struct sf_t_name##__rcd_fid_t

/// Declares a typed fiber id based on a typed sub fiber.
#define decl_fid_t(sf_t_name) \
sf(sf_t_name); \
struct sf_t_name##__rcd_fid_t { \
    rcd_fid_t fid; \
}; \
static inline struct sf_t_name##__rcd_fid_t sf_t_name##_sf2id(sf(sf_t_name)* sf) { \
    return (struct sf_t_name##__rcd_fid_t) {.fid = sf2id(sf_t_name, sf)}; \
}

// *** Core libraries that declare core symbols required by rcd syntax. ****

#include "sys-limit.h"
#include "cassert.h"
#include "utlist.h"
#include "avl.h"
#include "rb.h"
#include "fstring.h"
#include "list.h"
#include "setjmp.h"
#include "vm.h"


// *** Built in lists of base types that can be used for rapidly creating public interfaces that accepts ordered lists of data. ***

// *** Fundamental rcd types and programming macros. ***

/// Unique ID for a fiber. Large enough to always be unique.
typedef uint128_t rcd_fid_t;

/// Handle for a sub fiber. Used to create attached fibers with mitosis that are cleaned up when free'd.
typedef struct rcd_sub_fiber rcd_sub_fiber_t;

/// Declares thread static memory in an object file. This memory should not be
/// modified directly as it is only used as a original image for the thread
/// static memory of each physical thread. To actually reference the thread
/// local static memory the pointer inside the segment should be translated
/// through lwt_get_thread_static_ptr().
#define RCD_DEFINE_THREAD_STATIC_MEMORY(declaration) const declaration __attribute__((section("librcd_thread_static_memory")))

/// Thrown for invalid arguments, invalid precondition or other dynamic typing errors.
/// Examples: argument was null pointer, given list was empty.
#define exception_arg           (1 << 0)
/// Thrown for side effect and rpc errors or untyped data format errors.
/// Examples: unserialization failed, syscall failed, socket error.
#define exception_io            (1 << 1)
/// Triggered automatically when joining and the target server was canceled or
/// was never existing in the first place. Used to design race obliviousness
/// when doing ifc. Thrown both if the the server failed to accept the join
/// before shutting down or if the server was canceled while shutting down.
#define exception_join_race     (1 << 2)
/// When a fiber is executing non-interruptible the fiber gets this exception
/// instead of a join race in the case where the fiber never existed or quit
/// before the request was ever accepted. A join race on the other hand may
/// have executed fully, not at all or anything in between.
#define exception_no_such_fiber (1 << 3)
/// Triggered automatically when a fiber is canceled as soon as the fiber is deferred.
#define exception_canceled      (1 << 4)

/// When catching exceptions, specifies that we're interested in any catchable
/// exception. This mask is almost never required and if you want to use
/// it you are probably using some anti-pattern or are making a general
/// exception handler for logging/debugging purposes.
#define exception_any        (~(0xff << 5))
/// An special exception type that is only used as a forward exception when
/// throwing cancellation. It cannot be caught, generated or thrown by
/// the user space.
#define exception_cancel_source (1 << 13)
/// When catching exceptions, specifies that we're only interested in inner
/// join races and not outer join races. This is usually what we
/// actually want when catching join races and is just a shortcut for
/// catching a exception_join_race and immediately doing a
/// lwt_test_live_join_race(). It also catches exception_no_such_fiber so
/// a function is compatible with being called from a potentially
/// uninterruptable context.
#define exception_inner_join_fail ((1 << 14) | exception_join_race | exception_no_such_fiber)
/// Short for catching inner join fail and cancellation at the same time.
/// Is preferred because it creates more robust code. It's usually a
/// coincidence that only one or the other is needed and only catching
/// cancellations are dangerous as they can be converted to join races when
/// joining with fibers that are canceled.
#define exception_desync (exception_canceled | exception_inner_join_fail)
/// Uncatchable exception. Will terminate the program because it's uncatchable.
#define exception_fatal      (1 << 15)

typedef int rcd_exception_type_t;

typedef struct rcd_exception {
    rcd_exception_type_t type;
    fstr_t message;
    fstr_t file;
    size_t line;
    void* eio_class;
    void* eio_data;
    list(void*)* backtrace_calls;
    struct rcd_exception* fwd_exception;
    struct lwt_heap* exception_heap;
} rcd_exception_t;

typedef enum {
    /// The server fiber state may be shared between multiple fiber contexts.
    RCD_IFC_CALL_SHARED,
    /// The fiber has exclusive access to the server fiber state.
    RCD_IFC_CALL_LOCK_SERVER,
} rcd_ifc_call_type_t;

/// rcd-line-pp-marker: Should be the first parameter in the fiber main
/// parameter list. Evaluates to one or more mandatory parameters required
/// to start the new fiber.
#define fiber_main_attr fstr_t fiber_name

/// rcd-line-pp-marker: Defines a main function for a fiber. It cannot be
/// called directly and should only be used in combination with the
/// spawn_static_fiber() keyword.
#define fiber_main rcd_pp_marker__fiber_main; rcd_fid_t

/// rcd-line-pp-marker: Defines a main function for a fiber that is typed.
/// The spawn_static_fiber macro will generate a sf(sf_t_name)* type instead of
/// a rcd_sub_fiber_t* when the fiber main has this signature. This is
/// the recommended way to declare a fiber main since it enforces type safety.
/// The name itself is arbitrary and should be descriptive, short and unique.
#define fiber_main_t(sf_t_name) rcd_pp_marker__fiber_main sf_t_name; rcd_fid_t

extern int rcd_pp_marker__fiber_main;

/// rcd-line-pp-marker: Declaration of fiber_main.
#define fiber_main_declare rcd_pp_marker__fiber_main_declare; rcd_fid_t

/// rcd-line-pp-marker: Typed declaration of fiber_main.
#define fiber_main_declare_t(sf_t_name) rcd_pp_marker__fiber_main_declare sf_t_name; rcd_fid_t

extern int rcd_pp_marker__fiber_main_declare;

/// rcd-macro: Creates a sub heap and uses it in the following block.
#define sub_heap \
    LET(uint8_t __rcd_sh_cl __attribute__((cleanup(__lwt_fiber_stack_pop_sub_heap))) = (__lwt_fiber_stack_push_sub_heap(), 0))

/// rcd-macro: Let an allocation escape the sub heap, importing it into the
/// parent heap so it survives.
#define escape(alloc0) ({ \
    typeof(alloc0) __alloc0_ptr = alloc0; \
    lwt_alloc_escape(__alloc0_ptr); \
    __alloc0_ptr; \
})

/// rcd-macro: Let a complex struct with a direct "heap" member escape the sub
/// heap, importing it into the parent heap so it survives.
#define escape_complex(alloc0) ({ \
    typeof(alloc0) __alloc0_ptr = alloc0; \
    lwt_alloc_escape(__alloc0_ptr->heap); \
    __alloc0_ptr; \
})

/// rcd-macro: Let one or more allocations escape the sub heap, importing them
/// into the parent heap so they survive.
#define escape_list(...) ({ \
    void* __allocs[] = {__VA_ARGS__}; \
    size_t __allocs_n = LENGTHOF(__allocs); \
    for (size_t __rcd_e_i = 0; __rcd_e_i < __allocs_n; __rcd_e_i++) \
        lwt_alloc_escape(__allocs[__rcd_e_i]); \
})

/// rcd-macro: Imports an allocation to the current sub heap from the remote
/// heap we are joined with.
#define import(alloc0) ({ \
    typeof(alloc0) __alloc0_ptr = alloc0; \
    lwt_alloc_import(__alloc0_ptr); \
    __alloc0_ptr; \
})

/// rcd-macro: Imports a complex struct allocation with a direct "heap" member
/// to the current sub heap from the remote heap we are joined with.
#define import_complex(alloc0) ({ \
    typeof(alloc0) __alloc0_ptr = alloc0; \
    lwt_alloc_escape(__alloc0_ptr->heap); \
    __alloc0_ptr; \
})

/// rcd-macro: Let one or more allocations be imported to the current sub
/// heap from the remote heap we are joined with.
#define import_list(...) ({ \
    void* __allocs[] = {__VA_ARGS__}; \
    size_t __allocs_n = LENGTHOF(__allocs); \
    for (size_t __rcd_e_i = 0; __rcd_e_i < __allocs_n; __rcd_e_i++) \
        lwt_alloc_import(__allocs[__rcd_e_i]); \
})

/// rcd-macro: Creates a sub heap that wraps a single statement.
#define sub_heap_e(expr) ({sub_heap { expr; }})

/// rcd-macro: Creates a sub heap which can only return data through the new
/// alternative heap. The alternative heap is not entered automatically,
/// the only way to have allocations survive is to first switch to it.
/// The alternative heap is only preserved if the sub heap
/// is exited orderly. The alternative heap is merged with the current sub
/// heap as it is thrown away.
#define sub_heap_txn(heap_name) \
    sub_heap \
    LET(lwt_heap_t* heap_name __attribute__((cleanup(__rcd_escape_sh_txn))) = lwt_alloc_heap())

/// rcd-macro: Switches to an alternative heap and uses it in the following block.
#define switch_heap(heap_name) \
    LET(uint8_t _rcd_switch_heap_cl __attribute__((cleanup(__lwt_fiber_stack_pop_switch_heap))) = (__lwt_fiber_stack_push_switch_heap(heap_name), 0))

/// rcd-macro: Creates a new heap and switches to it.
#define switch_new_heap(heap_name) \
    LET(lwt_heap_t* heap_name = lwt_alloc_heap()) \
        switch_heap(heap_name)

/// rcd-macro: Equivalent to sub_heap_txn(heap_name) switch_heap(heap_name)
#define switch_txn(heap_name) sub_heap_txn(heap_name) switch_heap(heap_name)

/// rcd-macro: Creates a new heap and switches to it.
/// When the statement is exited orderly the heap is atomically appended to the
/// global heap, ensuring that the memory is never freed.
/// This is useful when initializing global state.
/// The reason why this statement is transactional is that it would be unsafe
/// to expose even a thread static heap as the fiber could jump between threads
/// as it is scheduled.
#define global_heap \
    sub_heap \
    LET(lwt_heap_t* __rcd_global_heap_tail __attribute__((cleanup(__rcd_escape_gh_txn))) = lwt_alloc_heap()) \
    switch_heap(__rcd_global_heap_tail)

/// Internal librcd structure that contains try block properties.
typedef struct __rcd_try_prop {
    jmp_buf try_jbuf;
    rcd_exception_t* volatile caught_exception;
    bool has_finally;
} __rcd_try_prop_t;

/// rcd-macro: Runs a try block and catches the exceptions specified in
/// the catch block after the try statement.
#define try _try_labeled(GLUE(__rcd_try_exit_, __COUNTER__))
#define _try_labeled(exit_label) \
    LET(__rcd_try_prop_t __rcd_try_prop = {.caught_exception = 0, .has_finally = false}) \
    for (rcd_exception_type_t __rcd_etype_catch = 0, __rcd_etype_final = 0;; ({exit_label: break;})) \
    /* enter the try addil (anti duff device infinite loop) */ \
    for (uint8_t __rcd_try_i = 0;; __rcd_try_i++) \
    if (__rcd_try_i == 2) { \
        if (setjmp(__rcd_try_prop.try_jbuf) != 0) { \
            __rcd_try_i = 4; \
        } \
    } else if (__rcd_try_i == 3) { \
        __lwt_fiber_stack_push_try_catch(&__rcd_try_prop.try_jbuf, __rcd_etype_final, &__rcd_try_prop.caught_exception); \
    } else if (__rcd_try_i == 7) { \
        /* rethrow exceptions without matching catch block */ \
        lwt_throw_exception(__rcd_try_prop.caught_exception); \
    } else if (__rcd_try_i == 4) \
        for (;; ({ \
            /* leaving try block normally without exception */ \
            if (!__rcd_try_prop.has_finally) { \
                /* no finally, exit the try/catch */ \
                goto exit_label; \
            } else { \
                /* continue to finally block */ \
                break; \
            } \
        })) \
        for (__rcd_try_prop_t* __rcd_try_scope __attribute__((cleanup(__rcd_escape_try))) = &__rcd_try_prop;; ({__rcd_try_scope = 0; break;})) \
        LET() /* handle break in try */

/// rcd-macro: Specifies a finally block. Must follow a try or catch block.
#define finally _finally_labeled(GLUE(__rcd_finally_exit_, __COUNTER__))
#define _finally_labeled(exit_label) \
    else if (__rcd_try_i == 0) { \
        __rcd_try_prop.has_finally = true; \
        __rcd_etype_final |= exception_any; \
        continue; \
        exit_label: \
        break; \
    } else if (__rcd_try_i == 5) \
        for (;; ({ \
            if (__rcd_try_prop.caught_exception == 0) { \
                /* no exception, exit the try/catch normally */ \
                /* semantically, this branch exists only if the one out of try does, so hide it to generate more sensible */ \
                /* warnings (in particular, we may get warnings about missing return statements without this). */ \
                _CLANG_HIDE_CONTROL_FLOW(goto exit_label;) \
            } \
            break; \
        })) \
        LET() /* handle break in finally */

/// rcd-macro: Specifies a catch block. Must follow a try, catch or finally block.
#define catch(catch_exception_mask, exception_name) \
    _catch_labeled(catch_exception_mask, exception_name, GLUE(__rcd_catch_exit_, __COUNTER__), )
#define _catch_labeled(catch_exception_mask, exception_name, exit_label, extra_cond) \
    else if (__rcd_try_i == 1 && (__rcd_etype_final |= (catch_exception_mask), __rcd_etype_catch |= (catch_exception_mask), false)) { \
        exit_label: \
        break; \
    } else if (__rcd_try_i == 6 && (__rcd_try_prop.caught_exception->type & (catch_exception_mask)) != 0 extra_cond) \
        for (;; ({goto exit_label;})) \
        LET(rcd_exception_t* exception_name = __rcd_try_prop.caught_exception)

/// rcd-macro: Specifies a catch block for a specific eio class. Must follow a try, catch or finally block.
#define catch_eio(class, exception_name, ... /* optional: data_name */) \
    _catch_labeled(exception_io, exception_name, GLUE(__rcd_catch_exit_, __COUNTER__), && (__rcd_try_prop.caught_exception->eio_class == class##_eio)) \
        LET(class##_eio_t _SECOND_ARG(_, ##__VA_ARGS__, __rcd_eio) = *(class##_eio_t*)(exception_name)->eio_data)

/// rcd-macro: Specifies an uninterruptible block. In this block join races
/// and cancellations are suppressed and never thrown.
/// Can be used for critical I/O and side effects garbage collection where
/// full execution is critical before the program can continue.
#define uninterruptible \
    LET(uint8_t __rcd_ui_cl __attribute__((cleanup(__lwt_fiber_stack_pop_uninterruptible))) = (__lwt_fiber_stack_push_uninterruptible(), 0))

/// rcd-macro: Throws a new exception.
#define throw(message, exception_type) \
    lwt_throw_new_exception(message, fstr(__FILE__), __LINE__, exception_type, 0, 0, 0, 0)

/// rcd-macro: Throws a new exception and forwards another existing exception.
#define throw_fwd(message, exception_type, fwd_exception) \
    lwt_throw_new_exception(message, fstr(__FILE__), __LINE__, exception_type, 0, 0, 0, fwd_exception)

#define throw_fwd_same(message, fwd_exception) ({ \
    rcd_exception_t* _fwd_e = (fwd_exception); \
    lwt_throw_new_exception(message, fstr(__FILE__), __LINE__, _fwd_e->type, _fwd_e->eio_class, _fwd_e->eio_data, 0, _fwd_e); \
})

/// rcd-macro: Throws an io exception of a custom class with no data fields.
#define throw_eio(message, name) \
    throw_eio_##name(message, fstr(__FILE__), __LINE__, 0)

/// rcd-macro: Throws an io exception of a custom class with no data fields, and
/// forwards another exception.
#define throw_eio_fwd(message, name, fwd_exception) \
    throw_eio_##name(message, fstr(__FILE__), __LINE__, fwd_exception)

/// rcd-macro: Creates a custom (complex) io exception object and a new heap, and
/// switches to it for the duration of the following block. The block must throw
/// an exception (generally with throw_em or throw_em_fwd), or else will assert.
#define emitosis(class, data) _emitosis_internal(data, class##_eio, class##_eio_t)
#define _emitosis_internal(data, name, eio_t) \
    for (void* __rcd_eio_type = name;; assert(false)) \
    LET(lwt_heap_t* __rcd_eio_heap = lwt_alloc_heap()) \
    switch_heap(__rcd_eio_heap) \
    LET(eio_t data = {0})

/// rcd-macro: Throws a new exception from a emitosis block.
#define throw_em(message, data) \
    lwt_throw_new_exception(message, fstr(__FILE__), __LINE__, exception_io, __rcd_eio_type, cln(&data), __rcd_eio_heap, 0)

/// rcd-macro: Throws a new exception from a emitosis block and forwards another
/// existing exception.
#define throw_em_fwd(message, data, fwd_exception) \
    lwt_throw_new_exception(message, fstr(__FILE__), __LINE__, exception_io, __rcd_eio_type, cln(&data), __rcd_eio_heap, fwd_exception)

/// rcd-macro: Defines a complex io exception class "<name>_eio". Example usage:
///
/// typedef struct { size_t line, col; fstr_t token; } json_eio_t;
/// define_eio_complex(json, line, col, token);
#define define_eio_complex(name, ...) \
    _define_eio_complex_internal(name##_eio, name##_eio_t, __VA_ARGS__)
#define _eio_mem_describe(x) , fstr("; " #x "="), data->x
#define _define_eio_complex_internal(name, eio_t, ...) \
    __attribute__((weak)) fstr_mem_t* _describe_##name(void* e) { \
        eio_t* data = e; \
        return conc(fstr(#name) FOR_EACH_ARG(_eio_mem_describe, __VA_ARGS__)); \
    } \
    static void* const name = (void*)&_describe_##name

/// rcd-macro: Defines a simple io exception class "<name>_eio". Example usage:
///
/// define_eio(json);
#define define_eio(class) _define_eio_internal(class, class##_eio, class##_eio_t)
#define _define_eio_internal(class, name, eio_t) \
    __attribute__((weak)) fstr_mem_t* _describe_##name(void* e) { \
        return fstr_cpy(fstr(#name)); \
    } \
    static void* const name = (void*)&_describe_##name; \
    noret static inline void throw_eio_##class \
            (fstr_t message, fstr_t file, uint64_t line, rcd_exception_t* fwd_exception) { \
        lwt_throw_new_exception(message, file, line, exception_io, name, 0, 0, fwd_exception); \
    } \
    typedef struct {} eio_t

/// rcd-macro: Starts a fiber mitosis, creating a new fiber in a block
/// where it switch to its initial heap. The allocated fiber id can be accessed
/// by reading the declared "new_fid" variable. The fiber exists as soon
/// as the block is entered but does not start running until it's spawned.
/// If the block is exited without spawning a fiber the fiber becomes a zombie
/// and will terminate asynchronously.
#define fmitosis \
    LET(rcd_fid_t new_fid = __lwt_fiber_stack_push_mitosis()) \
    LET(uint8_t _rcd_mitosis_used __attribute__((cleanup(__lwt_fiber_stack_pop_mitosis_and_abort))) = 0)

/// rcd-line-pp-marker: Starts a new static fiber. A call to the main function
/// of the new fiber defined with rcd_fiber should immediately follow on the
/// same line. Must be used in a new heap statement. Transfers the new heap to
/// the new fiber and switch back to the original heap context. It is bad code
/// practice to not immediately exit the rcd_new_heap statement after using
/// this macro. Returns a fiber id that must be used to send calls to the new
/// fiber. The fiber name should be allocated on the new fiber heap or be static.
#define spawn_static_fiber(main_fn_call) (_rcd_mitosis_used = 1, __librcd_fiber_mitosis__##main_fn_call)

/// rcd-line-pp-marker: Like spawn_static_fiber() but returns a rcd_sub_fiber_t*
/// instead which is an anonymous struct which has a destructor that
/// automatically cancels the fiber. If the fiber main is typed this macro
/// will return a sf(sf_t_name)* instead. This is the recommended way to
/// start new fibers although fibers are free to ignore any cancellation
/// requests and fibers can be manually canceled anyway.
#define spawn_fiber(main_fn_call) (_rcd_mitosis_used = 1, __librcd_fiber_sf_mitosis__##main_fn_call)

/// rcd-line-pp-marker: Converts a fiber to a server that accepts requests
/// to the functions initially specified in the variable argument list.
/// The list shall initially contain a list of join_xxx declared functions
/// that the server accepts on and afterwards there shall be a list of keys
/// and values (syntaxed key = value) that specify the server state to "call"
/// the functions with. The functions must specify the same list of parameters.
/// Blocks until accepted a request of one locked or many shared clients. When
/// the number of executing clients reaches zero again the call returns.
#define accept_join(...) rcd_pp_marker__accept(__VA_ARGS__),rcd_pp_marker__accept_end;

extern int rcd_pp_marker__accept;
extern int rcd_pp_marker__accept_end;

/// rcd-line-pp-marker: Like accept_join() but instead of handling a single request
/// the function blocks endlessly and never stops accepting clients until the
/// fiber is canceled. This is more optimized than having a loop around the
/// accept_join() in user space.
#define auto_accept_join(...) rcd_pp_marker__auto_accept(__VA_ARGS__),rcd_pp_marker__accept_end;

/// rcd-line-pp-marker: Like accept_join() but accepts on the joined servers
/// fiber instead of the clients. This is exactly like a normal accept
/// (e.g. server heap context) except that clients accepts on the servers fid.
/// It is undefined behavior to use this in a non-joined context.
#define server_accept_join(...) rcd_pp_marker__server_accept(__VA_ARGS__),rcd_pp_marker__accept_end;

/// rcd-line-pp-marker: Combined server_accept_join() and auto_accept_join().
#define server_auto_accept_join(...) rcd_pp_marker__server_auto_accept(__VA_ARGS__),rcd_pp_marker__accept_end;

extern int rcd_pp_marker__auto_accept;
extern int rcd_pp_marker__accept_end;

/// rcd-line-pp-marker: Declares a function that joins a server and a client
/// state for "communication". The function parameter list shall be declared
/// with a join_server_params statement that separate the client and server
/// arguments. A client that calls this function blocks until a server can
/// accept the call. After the call is accepted they execute "together"
/// although in the client heap context. This can be changed by flipping to
/// to the server heap using server_heap_flip. During the execution the
/// server is locked and cannot be used by other clients. If the server is
/// canceled during execution the client is also canceled and the server
/// cancellation is deferred until all clients have exited.
#define join_locked(ret_type) rcd_pp_marker__join_locked; ret_type

extern int rcd_pp_marker__join_locked;

/// rcd-line-pp-marker: Declaration of join_locked.
#define join_locked_declare(ret_type) rcd_pp_marker__join_locked_declare; ret_type

extern int rcd_pp_marker__join_locked_declare;

/// rcd-line-pp-marker: Like join_locked but multiple clients are allowed
/// to use the same server in parallel. Useful optimization for functions that
/// does not change the server state.
#define join_shared(ret_type) rcd_pp_marker__join_shared; ret_type

extern int rcd_pp_marker__join_shared;

/// rcd-line-pp-marker: Declaration of join_shared.
#define join_shared_declare(ret_type) rcd_pp_marker__join_shared_declare; ret_type

extern int rcd_pp_marker__join_shared_declare;

/// rcd-macro: Separates the client parameters from the server
/// parameters in a fiber join function list and also serves to specify
/// the server fiber id for the client calling the function.
#define join_server_params rcd_fid_t server_fiber_id

/// rcd-macro: Switches to the server heap context when executing in a join
/// or back to the client heap if nested.
#define server_heap_flip \
    LET(uint8_t _rcd_shf_cl __attribute__((cleanup(__lwt_fiber_stack_pop_flip_server_heap))) = (__lwt_fiber_stack_push_flip_server_heap(), 0))

// *** Core libraries with declarations that depend on rcd syntax. ***

#include "reflect.h"
#include "arithmetic.h"
#include "prng.h"
#include "lwthreads.h"
#include "rio.h"
#include "sort.h"

/// Main function for the program. Defined by the application.
void rcd_main(list(fstr_t)* main_args, list(fstr_t)* main_env);

// *** Debug related definitions. ***

/// Asserted test which asserts that an explicit test is not false unlike
/// assert which is more like documentation that is not necessarily executed.
/// It is bad practice to use this macro instead of assert unless you are
/// writing a program which has the actual purpose of testing things
/// (e.g. a unit test batch).
#define atest(x) ((x) || (__assert_fail(fstr(#x), fstr(__FILE__), __LINE__, fstr(__func__)),0))

#ifdef DEBUG
#define _DEBUG_ONLY(x) x
#else
#define _DEBUG_ONLY(x) ((void)0)
#endif

/// In debug mode, aborts if the given expression evaluates to false. In release
/// mode, this evaluates to nothing - the given expression is not evaluated.
#define assert(x) _DEBUG_ONLY(atest(x))

#define BREAKPT { __asm__ __volatile__("int $3"::: "memory"); }

/// Prints a message involving numbers/pointers to stderr. Arguments are evaluated
/// within a sub heap, and automatically converted to strings using 'STR'. Usage:
///
/// DPRINT("str ", num, ptr);
#define DPRINT(...) ({ sub_heap { \
    void* _dbg_str_mem_ptr = 0; \
    rio_debug(concs(__VA_ARGS__, "\n")); \
}})

/// Prints a message involving numbers/pointers to stderr, without allocating
/// heap memory during string conversions. Useful in low-level code. Usage:
///
/// DPRINT_RAW("str ", DBG_INT(num), " ", DBG_PTR(ptr));
#define DPRINT_RAW(...) ({ \
    uint8_t _dbg_str_mem[PAGE_SIZE]; \
    uint8_t* _dbg_str_mem_ptr = _dbg_str_mem; \
    fstr_t _dbg_tokens[] = {__VA_ARGS__, "\n"}; \
    rio_debug_chunks(_dbg_tokens, LENGTHOF(_dbg_tokens)); \
})

/// In debug mode, prints the given arguments to stderr using DPRINT. Otherwise,
/// this expands to nothing; the given arguments are not evaluated.
#define DBG(...) _DEBUG_ONLY(DPRINT(__VA_ARGS__))

/// Like DBG, but with DPRINT_RAW.
#define DBG_RAW(...) _DEBUG_ONLY(DPRINT_RAW(__VA_ARGS__))

/// Like DBG, but with the current function name prepended.
#define DBGFN(...) DBG("[", fstr(__func__), "] ", ##__VA_ARGS__)

/// Dumps message, data and stack trace of an exception using DBG.
#define DBGE(e, ...) DBG(fss(lwt_get_exception_dump(e)), ##__VA_ARGS__)

/// Include a pointer as part of DPRINT_RAW output.
#define DBG_PTR(ptr) ({ \
    fstr_t out; \
    if (_dbg_str_mem_ptr == 0) { \
        out = fss(fstr_from_uint((uintptr_t) ptr, 16)); \
    } else { \
        fstr_t _ptr_str = {.str = _dbg_str_mem_ptr, .len = 32}; \
        _dbg_str_mem_ptr += 32; \
        out = fstr_serial_uint(_ptr_str, (uintptr_t) ptr, 16); \
    } \
    out; \
})

/// Include an integer as part of DPRINT_RAW output.
#define DBG_INT(integer) ({ \
    fstr_t out; \
    if (_dbg_str_mem_ptr == 0) { \
        out = fss(fstr_from_int(integer, 10)); \
    } else { \
        fstr_t _ptr_str = {.str = _dbg_str_mem_ptr, .len = 32}; \
        _dbg_str_mem_ptr += 32; \
        out = fstr_serial_int(_ptr_str, integer, 10); \
    } \
    out; \
})

/// Include a boolean as part of DPRINT or DPRINT_RAW output,
#define DBG_BOOL(val) (val? "true": "false")

/// Like atest() but tests something that could happen but is improbable.
/// If the condition x is false we print a warning to stderr and continue.
/// This is for testing stuff that indicates that something is broken if they
/// happen repeatedly but we don't want to crash on.
#define improb_atest(x, ...) ({ if (!(x)) { DPRINT("!!! [improb_atest/warning]: improbable condition occurred: [", __VA_ARGS__, "] (disclaimer: this does not indicate a fatal problem unless it happens repeatedly in which case something might be broken) !!!"); }})

// Assert that GNU extensions are enabled, so we have support for empty argument
// lists for variadic macros.
CASSERT(VA_NARGS() == 0);

// *** Application level bundled useful libraries. ***
#include "acid.h"
#include "ifc.h"
#include "polar.h"
#include "rest.h"
#include "json.h"

#endif  /* RCD_H */
