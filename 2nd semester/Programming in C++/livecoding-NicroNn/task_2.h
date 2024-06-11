/*
    Место для решения второй задачи
*/
#include <utility>

template<typename Iterator1, typename Iterator2>
class PythonZip {
    Iterator1 begin1, end1;
    Iterator2 begin2, end2;

  public:
    PythonZip(Iterator1 begin1, Iterator1 end1, Iterator2 begin2, Iterator2 end2)
        : begin1(begin1), end1(end1), begin2(begin2), end2(end2) {}

    template<typename T1, typename T2>
    class iterator {
        T1 iter1;
        T2 iter2;

      public:
        iterator(T1 iter1, T2 iter2) : iter1(iter1), iter2(iter2) {}

        std::pair<typename T1::value_type, typename T2::value_type> operator*() const {
            return std::make_pair(*iter1, *iter2);
        }

        iterator& operator++() {
            ++iter1;
            ++iter2;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return iter1 != other.iter1 && iter2 != other.iter2;
        }
    };

    iterator<Iterator1, Iterator2> begin() const {
        return iterator<Iterator1, Iterator2>(begin1, begin2);
    }

    iterator<Iterator1, Iterator2> end() const {
        return iterator<Iterator1, Iterator2>(end1, end2);
    }
};

template<typename Container1, typename Container2>
PythonZip<typename Container1::const_iterator, typename Container2::const_iterator> pythonzip(const Container1& container_1, const Container2& container_2) {
    return PythonZip<typename Container1::const_iterator, typename Container2::const_iterator>(container_1.begin(), container_1.end(), container_2.begin(), container_2.end());
}
