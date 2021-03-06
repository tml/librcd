#ifndef JSON_H
#define JSON_H

#include "rcd.h"

#define json_null_v ((json_value_t){.type = JSON_NULL})
#define json_bool_v(x)   ((json_value_t){.type = JSON_BOOL,   .bool_value   = x})
#define json_number_v(x) ((json_value_t){.type = JSON_NUMBER, .number_value = x})
#define json_string_v(x) ((json_value_t){.type = JSON_STRING, .string_value = x})
#define json_array_v(x)  ((json_value_t){.type = JSON_ARRAY,  .array_value  = x})
#define json_object_v(x) ((json_value_t){.type = JSON_OBJECT, .object_value = x})

#define jnull json_null_v
#define jbool(x) json_bool_v(x)
#define jnum(x) json_number_v(x)
#define jstr(x) json_string_v(x)
#define jarr(x) json_array_v(x)
#define jobj(x) json_object_v(x)

#define jarr_new(...) jarr(new_list(json_value_t, __VA_ARGS__))
#define jobj_new(...) jobj(new_dict(json_value_t, __VA_ARGS__))

/// Enter a scope with 'this' assigned to a particular JSON value. This can be
/// helpful in making creation of JSON structures feel more natural.
#define json_for(obj) \
    LET(json_value_t this = obj)

#define json_for_obj(obj) json_for(obj)

/// Create a new object as a member of the object 'this', and enter a scope with it set as 'this'.
/// Example usage:
///
/// json_value_t val = json_new_object();
/// json_for_obj(val) {
///     json_for_new_obj("property") {
///         JSON_SET(this, "leaf", json_string_v("value"));
///     }
/// }
#define json_for_new_oobj(key) \
    LET(json_value_t new_obj = json_new_obj_in_obj(this, (key))) \
    LET(json_value_t this = new_obj)

#define json_for_new_obj(key) json_for_new_oobj(key)

/// Create a new array as a member of the object 'this', and enter a scope with it set as 'this'.
#define json_for_new_oarr(key) \
    LET(json_value_t new_obj = json_new_arr_in_obj(this, (key))) \
    LET(json_value_t this = new_obj)

/// Create a new object as a member of the array 'this', and enter a scope with it set as 'this'.
#define json_for_new_aobj \
    LET(json_value_t new_obj = json_new_obj_in_arr(this)) \
    LET(json_value_t this = new_obj)

/// Create a new array as a member of the array 'this', and enter a scope with it set as 'this'.
#define json_for_new_aarr \
    LET(json_value_t new_obj = json_new_arr_in_arr(this)) \
    LET(json_value_t this = new_obj)

/// Traverse a chain of JSON properties in a lenient manner, returning a null JSON value
/// if any link in the chain does not exist. Example usage:
///
/// json_tree_t* tree = json_parse("{\"a\": {\"b\": 1}}");
/// json_value_t val = JSON_LREF(tree->value, "a", "b");
/// if (!json_is_null(val)) {
///     do_something(json_get_number(val));
/// }
#define JSON_LREF(value, ...) ({ \
    json_value_t __value = value; \
    fstr_t __path[] = {__VA_ARGS__}; \
    for (int64_t __i = 0; __i < LENGTHOF(__path); __i++) { \
        json_value_t* __next_value = (__value.type == JSON_OBJECT? \
            dict_read(__value.object_value, json_value_t, __path[__i]): 0); \
        __value = (__next_value == 0? json_null_v: *__next_value); \
    } \
    __value; \
})

/// Traverse a chain of JSON properties in a strict manner, throwing an exception if some
/// property traversed does not exist or is null.
#define JSON_REF(value, ...) ({ \
    json_value_t __value = value; \
    fstr_t __path[] = {__VA_ARGS__}; \
    for (int64_t __i = 0; __i < LENGTHOF(__path); __i++) { \
        json_value_t* __next_value = (__value.type == JSON_OBJECT? \
            dict_read(__value.object_value, json_value_t, __path[__i]): 0); \
        __value = (__next_value == 0? json_null_v: *__next_value); \
        if (json_is_null(__value)) \
            _json_fail_missing_property(__path[__i]); \
    } \
    __value; \
})

/// Set a property of a JSON object to some value. Example usage:
///
/// json_value_t obj = json_new_object();
/// JSON_SET(obj, "property", json_string_v("value"));
#define JSON_SET(parent, prop, value) ({ \
    assert(parent.type == JSON_OBJECT); \
    dict_replace(parent.object_value, json_value_t, prop, value); \
})

/// JSON type identifier.
typedef enum json_type {
    JSON_NULL = 0,
    JSON_BOOL = 1,
    JSON_NUMBER = 2,
    JSON_STRING = 3,
    JSON_ARRAY = 4,
    JSON_OBJECT = 5,
} json_type_t;

/// A JSON value.
typedef struct json_value {
    json_type_t type;
    union {
        bool bool_value;
        double number_value;
        fstr_t string_value;
        list(json_value_t)* array_value;
        dict(json_value_t)* object_value;
    };
} json_value_t;

/// A JSON value, together with a heap which owns all values and strings contained
/// in that value.
typedef struct json_tree {
    json_value_t value;
    lwt_heap_t* heap;
} json_tree_t;

typedef struct {
    /// A message describing the failure, e.g. "unexpected trailing comma".
    fstr_t message;
    /// The (1-indexed) line the parse error occurred on.
    size_t line;
    /// The (1-indexed) column the parse error occurred on.
    size_t column;
} json_parse_eio_t;
define_eio_complex(json_parse, message, line, column);

typedef struct {
    /// The property name that was missing.
    fstr_t key;
} json_lookup_eio_t;
define_eio_complex(json_lookup, key);

typedef struct {
    /// The expected type.
    json_type_t expected;
    /// The actual type.
    json_type_t got;
} json_type_eio_t;
define_eio_complex(json_type, expected, got);

/// Parse a string into a json_tree_t. Throws exception_io on failure.
json_tree_t* json_parse(fstr_t str);

/// Serializes a JSON tree structure.
fstr_mem_t* json_stringify(json_value_t value);

/// Serializes a JSON tree structure in a human-readable manner.
fstr_mem_t* json_stringify_pretty(json_value_t value);

/// Compares two json values and returns true if they are of the same type
/// and exactly equal. It is undefined if two arrays or dicts are equal or not.
bool json_cmp(json_value_t a, json_value_t b);

/// Flattens a JSON value to a string. This destroys the type information
/// but makes the data easier to work with in cases where the type information
/// is irrelevant.
fstr_mem_t* json_flatten(json_value_t value);

/// Serializes a JSON type to a human readable string.
fstr_t json_serial_type(json_type_t type);

/// Returns true if value is empty, i.e. null, zero, false or zero length
/// string, array or object.
bool json_is_empty(json_value_t value);

/// Deep clones a json value.
json_value_t json_clone(json_value_t value, bool copy_strings);

/// Deep clones a json tree.
json_tree_t* json_clone_tree(json_tree_t* tree, bool copy_strings);

noret void _json_fail_invalid_type(json_type_t expected_type, json_type_t got_type);

noret void _json_fail_missing_property(fstr_t prop_name);

static inline fstr_t __attribute__((overloadable)) STR(json_value_t x) { return fss(json_stringify(x)); }
static inline fstr_t __attribute__((overloadable)) STR(json_type_t x) { return json_serial_type(x); }

static inline json_value_t json_new_array() {
    return json_array_v(new_list(json_value_t));
}

static inline json_value_t json_new_object() {
    return json_object_v(new_dict(json_value_t));
}

/// Create a new object and assign it as a property of another object.
static inline json_value_t json_new_obj_in_obj(json_value_t parent, fstr_t key) {
    json_value_t obj = json_new_object();
    JSON_SET(parent, key, obj);
    return obj;
}

/// Create a new array and assign it as a property of another object.
static json_value_t json_new_arr_in_obj(json_value_t parent, fstr_t key) {
    json_value_t arr = json_new_array();
    JSON_SET(parent, key, arr);
    return arr;
}

/// Create a new object and append it to another array.
static json_value_t json_new_obj_in_arr(json_value_t parent) {
    json_value_t obj = json_new_object();
    if (parent.type != JSON_ARRAY)
        _json_fail_invalid_type(JSON_ARRAY, parent.type);
    list_push_end(parent.array_value, json_value_t, obj);
    return obj;
}

/// Create a new array and append it to another array.
static json_value_t json_new_arr_in_arr(json_value_t parent) {
    json_value_t arr = json_new_array();
    if (parent.type != JSON_ARRAY)
        _json_fail_invalid_type(JSON_ARRAY, parent.type);
    list_push_end(parent.array_value, json_value_t, arr);
    return arr;
}

static inline void _json_type_expect(json_value_t value, json_type_t expected_type) {
    if (value.type != expected_type)
        _json_fail_invalid_type(expected_type, value.type);
}

/// Returns a number from a JSON value, throwing exception_io if the type is wrong.
static inline double json_get_number(json_value_t value) {
    _json_type_expect(value, JSON_NUMBER);
    return value.number_value;
}

/// Returns a string from a JSON value, throwing exception_io if the type is wrong.
static inline fstr_t json_get_string(json_value_t value) {
    _json_type_expect(value, JSON_STRING);
    return value.string_value;
}

/// Returns a boolean from a JSON value, throwing exception_io if the type is wrong.
static inline bool json_get_bool(json_value_t value) {
    _json_type_expect(value, JSON_BOOL);
    return value.bool_value;
}

/// Returns an list (array) from a JSON value, throwing exception_io if the type is wrong.
static inline list(json_value_t)* json_get_array(json_value_t value) {
    _json_type_expect(value, JSON_ARRAY);
    return value.array_value;
}

/// Returns a dict (object) from a JSON value, throwing exception_io if the type is wrong.
static inline dict(json_value_t)* json_get_object(json_value_t value) {
    _json_type_expect(value, JSON_OBJECT);
    return value.object_value;
}

static inline bool json_is_null(json_value_t value) {
    return value.type == JSON_NULL;
}

#endif  /* JSON_H */
