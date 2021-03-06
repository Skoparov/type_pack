#pragma once
#include "palg.h"

using namespace palg;

void test_size()
{
    static_assert(size_v<pack<>> == 0);
    static_assert(size_v<pack<void>> == 1);
    static_assert(size_v<pack<void, double>> == 2);
}

void test_repack()
{
    using repacked = repack_t<pack<int, double>, std::is_same>;
    static_assert(std::is_same_v<repacked, std::is_same<int, double>>);
}

void test_find()
{
    static_assert(find_v<pack<bool, void, bool>, bool> == 0);
    static_assert(find_v<pack<bool, void, bool>, bool, 1> == 2);
    static_assert(find_v<pack<bool, void, bool>, void> == 1);
    static_assert(find_v<pack<bool, void, bool>, void, 1> == 1);
    static_assert(find_v<pack<bool, void, bool>, float> == 3);
    static_assert(find_v<pack<>, float> == 1);

    static_assert(find_if_v<pack<void, int, bool>, fun<std::is_arithmetic>> == 1);
    static_assert(find_if_v<pack<void, int, bool>, fun<std::is_arithmetic>, 2> == 2);
}

void test_enumerate_if()
{
    using arithm_seq = enumerate_if_t<pack<void, int, void, double>, fun<std::is_arithmetic>>;
    static_assert(std::is_same_v<arithm_seq, std::index_sequence<1, 3>>);

    using class_seq = enumerate_if_t<pack<void, int, void, double>, fun<std::is_class>>;
    static_assert(std::is_same_v<class_seq, std::index_sequence<>>);

    using empty_pack = enumerate_if_t<pack<>, fun<std::is_arithmetic>>;
    static_assert(std::is_same_v<empty_pack, std::index_sequence<>>);

    using int_idx_pack = enumerate_t<pack<int, void, int>, int>;
    static_assert(std::is_same_v<int_idx_pack, std::index_sequence<0, 2>>);
}

void test_has_types()
{
    static_assert(has_types_v<pack<bool, void, double>, bool>);
    static_assert(has_types_v<pack<bool, void, double>, bool, void, double>);
    static_assert(!has_types_v<pack<int, int>, bool>);
    static_assert(!has_types_v<pack<int, int>, bool, int>);
    static_assert(!has_types_v<pack<>, bool, int>);

    static_assert(has_types_nodup_v<pack<bool, void, double>, bool>);
    static_assert(has_types_nodup_v<pack<bool, void, double>, bool, void, double>);
    static_assert(!has_types_nodup_v<pack<int>, bool>);
    static_assert(!has_types_nodup_v<pack<int>, bool, int>);
    static_assert(!has_types_nodup_v<pack<>, bool, int>);
}

void test_type_at()
{
    using void_type = type_at_t<pack<void>, 0>;
    static_assert(std::is_same_v<void_type, void>);

    using double_type = type_at_t<pack<void, double>, 1>;
    static_assert(std::is_same_v<double_type, double>);

    static_assert(std::is_same_v<front_t<pack<void, double>>, void>);
    static_assert(std::is_same_v<back_t<pack<void, double>>, double>);
}

void test_append()
{
    using int_double_pack = append_if_t<pack<>, any_of<int, double>, int, double>;
    static_assert(std::is_same_v<int_double_pack, pack<int, double>>);

    using empty_pack = append_if_t<pack<>, none_of<int, double>, int, double>;
    static_assert(std::is_same_v<empty_pack, pack<>>);

    using int_pack = append_if_t<pack<>, any_of<int>, int, double>;
    static_assert(std::is_same_v<int_pack, pack<int>>);

    using int_double_int_pack = append_if_t<pack<int, double>, any_of<int>, int>;
    static_assert(std::is_same_v<int_double_int_pack, pack<int, double, int>>);

    using empty_pack2 = append_if_t<pack<>, any_of<int>>;
    static_assert(std::is_same_v<empty_pack2, pack<>>);

    using int_double_pack2 = append_t<pack<>, int, double>;
    static_assert(std::is_same_v<int_double_pack2, pack<int, double>>);
}

void test_prepend()
{
    using int_double_pack = prepend_if_t<pack<>, any_of<int, double>, int, double>;
    static_assert(std::is_same_v<int_double_pack, pack<int, double>>);

    using empty_pack = prepend_if_t<pack<>, none_of<int, double>, int, double>;
    static_assert(std::is_same_v<empty_pack, pack<>>);

    using int_pack = prepend_if_t<pack<>, any_of<int>, int, double>;
    static_assert(std::is_same_v<int_pack, pack<int>>);

    using int_double_int_pack = prepend_if_t<pack<int, double>, any_of<int>, int>;
    static_assert(std::is_same_v<int_double_int_pack, pack<int, int, double>>);

    using empty_pack2 = prepend_if_t<pack<>, any_of<int>>;
    static_assert(std::is_same_v<empty_pack2, pack<>>);

    using int_double_pack2 = prepend_t<pack<>, int, double>;
    static_assert(std::is_same_v<int_double_pack2, pack<int, double>>);
}

void pop()
{
    using pack3 =  pack<int, double, void>;

    static_assert(std::is_same_v<pop_front_n_if_t<pack3, always, 2>, pack<void>>);
    static_assert(std::is_same_v<pop_front_n_if_t<pack3, never, 2>, pack3>);
    static_assert(std::is_same_v<pop_front_n_if_t<pack3, always, 0>, pack3>);
    static_assert(std::is_same_v<pop_front_n_t<pack3, 2>, pack<void>>);
    static_assert(std::is_same_v<pop_front_n_t<pack3, 0>, pack3>);
    static_assert(std::is_same_v<pop_front_n_t<pack<>, 0>, pack<>>);

    static_assert(std::is_same_v<pop_front_if_t<pack<int, double>, always>, pack<double>>);
    static_assert(std::is_same_v<pop_front_if_t<pack<int, double>, never>, pack<int, double>>);
    static_assert(std::is_same_v<pop_front_t<pack<int, double>>,pack<double>>);

    static_assert(std::is_same_v<pop_back_n_if_t<pack3, always, 2>, pack<int>>);
    static_assert(std::is_same_v<pop_back_n_if_t<pack3, never, 2>, pack3>);
    static_assert(std::is_same_v<pop_back_n_if_t<pack3, always, 0>, pack3>);
    static_assert(std::is_same_v<pop_back_n_t<pack3, 2>, pack<int>>);
    static_assert(std::is_same_v<pop_back_n_t<pack3, 0>, pack3>);
    static_assert(std::is_same_v<pop_back_n_t<pack<>, 0>, pack<>>);

    static_assert(std::is_same_v<pop_back_if_t<pack<int, double>, always>, pack<int>>);
    static_assert(std::is_same_v<pop_back_if_t<pack<int, double>, never>, pack<int, double>>);
    static_assert(std::is_same_v<pop_back_t<pack<int, double>>, pack<int>>);
}

void test_concat()
{
    static_assert(std::is_same_v<concat_t<pack<void>>, pack<void>>);

    using void_double_pack = concat_t<pack<>, pack<void, double>>;
    static_assert(std::is_same_v<void_double_pack, pack<void, double>>);

    using void_double_pack2 = concat_t<pack<void, double>, pack<>>;
    static_assert(std::is_same_v<void_double_pack2, pack<void, double>>);

    using void_int_double_pack = concat_t<pack<void, int>, pack<double>>;
    static_assert(std::is_same_v<void_int_double_pack, pack<void, int, double>>);

    using void_int_double_pack2 = concat_t<pack<void>, pack<int>, pack<double>>;
    static_assert(std::is_same_v<void_int_double_pack2, pack<void, int, double>>);
}


void test_invert()
{
    static_assert(std::is_same_v<pack<>, invert_t<pack<>>>);
    static_assert(std::is_same_v<pack<void>, invert_t<pack<void>>>);

    using pack_double_void = invert_t<pack<void, double>>;
    static_assert(std::is_same_v<pack<double, void>, pack_double_void>);
}

void test_remove()
{
    using empty_pack = remove_if_t<pack<>, any_of<int>>;
    static_assert(std::is_same_v<pack<>, empty_pack>);

    using double_pack = remove_if_t<pack<int, double>, any_of<int>>;
    static_assert(std::is_same_v<double_pack, pack<double>>);

    using empty_pack = remove_if_t<pack<int, double>, any_of<int, double>>;
    static_assert(std::is_same_v<empty_pack, pack<>>);

    using empty_pack2 = remove_if_t<pack<int, double>, fun<std::is_arithmetic>>;
    static_assert(std::is_same_v<empty_pack2, pack<>>);

    using int_double_pack = remove_if_t<pack<int, double>, none_of<int, double>>;
    static_assert(std::is_same_v<int_double_pack, pack<int, double>>);

    using empty_pack2 = remove_t<pack<int, double>, int, double>;
    static_assert(std::is_same_v<empty_pack2, pack<>>);
}

void test_unique()
{
    using int_pack = unique_t<pack<int, int>>;
    static_assert(std::is_same_v<int_pack, pack<int>>);

    using int_double_pack = unique_t<pack<int, double, int, double>>;
    static_assert(std::is_same_v<int_double_pack, pack<int, double>>);

    using empty_pack = unique_t<pack<>>;
    static_assert(std::is_same_v<empty_pack, pack<>>);
}

template<typename T>
using add_const_and_pointer = std::add_pointer<std::add_const_t<T>>;

void test_transform()
{
    using int_pack = pack<int, int>;
    static_assert(std::is_same_v<pack<>, transform_t<pack<>, fun<std::add_pointer>>>);
    
    using int_ptr_pack = transform_t<int_pack, fun<std::add_pointer>>;
    static_assert(std::is_same_v<int_ptr_pack, pack<int*, int*>>);

    using const_int_pack = transform_t<int_pack, fun<add_const_and_pointer>>;
    static_assert(std::is_same_v<const_int_pack, pack<const int*, const int*>>);
}

void test_predicates()
{
    using namespace detail;

    static_assert(!eval_v<not_<always>>);
    static_assert(eval_v<not_<not_<always>>>);

    static_assert(eval_v<or_<never, always>>);
    static_assert(eval_v<or_<never, never, always>>);
    static_assert(eval_v<not_<or_<never, never>>>);
    static_assert(eval_v<not_<or_<never, never, never>>>);

    static_assert(eval_v<and_<always, always>>);
    static_assert(eval_v<and_<always, always, always>>);
    static_assert(eval_v<not_<and_<never, never>>>);
    static_assert(eval_v<not_<and_<never, always>>>);
    static_assert(eval_v<not_<and_<never, never, never>>>);
    static_assert(eval_v<not_<and_<never, always, never>>>);

    static_assert(eval_v<and_<always, not_<never>>>);
    static_assert(eval_v<and_<always, or_<always, never>, always>>);
    static_assert(eval_v<and_<always, or_<always, never>, always>>);

    using is_numeric_and_pod = and_<fun<std::is_arithmetic>, fun<std::is_pod>>;
    static_assert(eval_v<is_numeric_and_pod, int>);
    static_assert(eval_v<not_<is_numeric_and_pod>, void>);
}

template<class A, class B>
using max_type = std::conditional<(sizeof(A) > sizeof(B)), A, B>;

void test_select()
{
    static_assert(std::is_same_v<select_t<pack<>, fun<max_type>>, default_select>);
    static_assert(std::is_same_v<select_t<pack<char, int>, fun<max_type>>, int>);
    static_assert(std::is_same_v<select_t<pack<char, int, double>, fun<max_type>>, double>);
}