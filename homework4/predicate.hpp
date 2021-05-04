#pragma once

#include <iterator>
#include <functional>

template <typename InputIt, typename Pred_Type>
bool allOf(InputIt start, InputIt end, Pred_Type prd) {

    for (;  start != end; start++) {
        if (prd(*start) == 0) 
            return false;
    }

    return true;
}

template <typename InputIt, typename Pred_Type>
bool anyOf(InputIt start, InputIt end, Pred_Type prd) {

    for (; start != end; start++) {
        if (prd(*start)) 
            return true;
    }

    return false;
}

template <typename InputIt, typename Pred_Type>
bool noneOf(InputIt start, InputIt end, Pred_Type prd) {

    for (; start != end; start++) {
        if (prd(*start)) 
            return false;
    }

    return true;
}

template <typename InputIt, typename Pred_Type>
bool oneOf(InputIt start, InputIt end, Pred_Type prd) {

    bool flag = false;

    for (; start != end; start++) {
        if (prd(*start)) {
            if (flag == false) { flag = true; }
            else { return false; }
        }
    }
    return flag;
}
//fixed use default template argument std::less
template <typename InputIt, typename Comp_Type = std::less<
    typename std::iterator_traits<InputIt>::value_type>>
bool isSorted(InputIt start, InputIt end, Comp_Type cmp = Comp_Type()) {

    InputIt first1 = start;
    InputIt second1 = ++start;

    while (second1 != end) {
        if (!cmp(*first1, *second1)) return false;
        first1++; second1++;
    }

    return true;
}

template <typename InputIt, typename Pred_Type>
bool isPartitioned(InputIt start, InputIt end, Pred_Type prd) {

    bool curValue = prd(*start);
    bool changed = false;
    start++;

    for (; start != end; start++) {
        if (prd(*start) != curValue) {
            if (changed) {
                return false;
            }
            changed = true;
            curValue = !curValue;
        }
    }

    return true;
}

template <typename ForwardIt, typename Type>
ForwardIt findNot(ForwardIt first, ForwardIt last, Type value){

    for (; first != last; first++) {
        if (*first != value) return first;
    }

    return last;
}

template <typename ForwardIt, typename Type>
ForwardIt findBackward(ForwardIt first, ForwardIt last, Type value) {

    ForwardIt last_equal = last;

    for (; first != last; first++) {
        if (*first == value) {
            last_equal = first;
        }
    }

    return last_equal;
}

template <typename InputIt, typename Comp_Type>
bool isPalindrome(InputIt first, InputIt last, Comp_Type cmp) {

    InputIt right_comp_el = first; last--;

    while (first != last && right_comp_el != last) {

        if (cmp(*first, *last) == 0) return false;

        right_comp_el = first;
        first++;
        last--;
    }

    return true;
}
