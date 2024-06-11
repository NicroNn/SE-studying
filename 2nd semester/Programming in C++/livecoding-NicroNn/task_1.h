/*
    Место для решения первой задачи
*/
template<typename InputIterator, typename Predicate>
bool less_half_of(InputIterator first, InputIterator last, Predicate pred) {
    if (first == last) return true;

    int total_count = 0;
    for (InputIterator it = first; it != last; ++it) {
        ++total_count;
    }

    int matching_count = 0;
    for (InputIterator it = first; it != last; ++it) {
        if (pred(*it)) {
            ++matching_count;
        }
    }

    return matching_count < total_count / 2;
}
