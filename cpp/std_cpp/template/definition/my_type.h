#ifndef HOME_CPP_MY_TYPE_H
#define HOME_CPP_MY_TYPE_H

constexpr size_t TypeID_int8_t = 0;
constexpr size_t TypeID_uint8_t = 1;
constexpr size_t TypeID_int16_t = 2;
constexpr size_t TypeID_uint16_t = 3;
constexpr size_t TypeID_int32_t = 4;
constexpr size_t TypeID_uint32_t = 5;
constexpr size_t TypeID_int64_t = 6;
constexpr size_t TypeID_uint64_t = 7;
constexpr size_t TypeID_float = 8;
constexpr size_t TypeID_double = 9;
constexpr size_t TypeID_char = 10;
constexpr size_t TypeID_bool = 11;
constexpr size_t TypeID_struct = 12;

template <typename T>
constexpr size_t GetTypeID() {
    return TypeID_struct;
}
template <>
constexpr size_t GetTypeID<int8_t>() {
    return TypeID_int8_t;
}
template <>
constexpr size_t GetTypeID<uint8_t>() {
    return TypeID_uint8_t;
}
template <>
constexpr size_t GetTypeID<int16_t>() {
    return TypeID_int16_t;
}
template <>
constexpr size_t GetTypeID<uint16_t>() {
    return TypeID_uint16_t;
}
template <>
constexpr size_t GetTypeID<int32_t>() {
    return TypeID_int32_t;
}
template <>
constexpr size_t GetTypeID<uint32_t>() {
    return TypeID_uint32_t;
}
template <>
constexpr size_t GetTypeID<int64_t>() {
    return TypeID_int64_t;
}
template <>
constexpr size_t GetTypeID<uint64_t>() {
    return TypeID_uint64_t;
}
template <>
constexpr size_t GetTypeID<float>() {
    return TypeID_float;
}
template <>
constexpr size_t GetTypeID<double>() {
    return TypeID_double;
}
template <>
constexpr size_t GetTypeID<char>() {
    return TypeID_char;
}
template <>
constexpr size_t GetTypeID<bool>() {
    return TypeID_bool;
}

template <typename T>
struct TypeID {
    static constexpr size_t id = TypeID_struct;
};

template <>
struct TypeID<int8_t> {
    static constexpr size_t id = TypeID_int8_t;
};

template <>
struct TypeID<uint8_t> {
    static constexpr size_t id = TypeID_uint8_t;
};

template <>
struct TypeID<int16_t> {
    static constexpr size_t id = TypeID_int16_t;
};

template <>
struct TypeID<uint16_t> {
    static constexpr size_t id = TypeID_uint16_t;
};

template <>
struct TypeID<int32_t> {
    static constexpr size_t id = TypeID_int32_t;
};

template <>
struct TypeID<uint32_t> {
    static constexpr size_t id = TypeID_uint32_t;
};

template <>
struct TypeID<int64_t> {
    static constexpr size_t id = TypeID_int64_t;
};

template <>
struct TypeID<uint64_t> {
    static constexpr size_t id = TypeID_uint64_t;
};

template <>
struct TypeID<float> {
    static constexpr size_t id = TypeID_float;
};

template <>
struct TypeID<double> {
    static constexpr size_t id = TypeID_double;
};

template <>
struct TypeID<char> {
    static constexpr size_t id = TypeID_char;
};

template <>
struct TypeID<bool> {
    static constexpr size_t id = TypeID_bool;
};

#endif
