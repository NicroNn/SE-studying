#ifndef THREE_D_ARRAY_H
#define THREE_D_ARRAY_H

#include <cinttypes>
#include <iostream>

class ThreeDArray {
  private:
    uint64_t height_;
    uint64_t width_;
    uint64_t depth_;
    uint64_t total_size_;
    uint32_t extra_field_;
    uint16_t* main_arr_ = nullptr;
    uint8_t* extra_bit_arr_ = nullptr;

    ThreeDArray(uint64_t height, uint64_t width, uint64_t depth);

  public:
    static const uint8_t kExtraMemory = 56;

    static ThreeDArray make_array(uint64_t height, uint64_t width, uint64_t depth);

    ThreeDArray(const ThreeDArray& other);
    ThreeDArray& operator=(const ThreeDArray& other);
    ~ThreeDArray();

    uint64_t GetSize() const;
    uint64_t GetHeight() const;
    uint64_t GetWidth() const;
    uint64_t GetDepth() const;

    uint16_t& operator()(uint64_t i, uint64_t j, uint64_t k);
    uint16_t GetElement(uint64_t index) const;
    uint8_t GetBits(uint64_t index) const;
    uint16_t& AccessElement(uint64_t index);
    void SetBits(uint64_t index, uint8_t bits);
    void ExtraFieldToArray(uint64_t index);
    uint32_t& AccessExtraField(uint64_t index);

    class OneD {
      private:
        ThreeDArray& array_;
        uint64_t x_index_;
        uint64_t y_index_;

      public:
        OneD(ThreeDArray& array, uint64_t x_index, uint64_t y_index);

        uint16_t& operator[](uint64_t z_index);
    };

    class TwoD {
      private:
        ThreeDArray& array_;
        uint64_t x_index_;

      public:
        TwoD(ThreeDArray& array, uint64_t x_index);
        OneD operator[](uint64_t y_index);
    };

    TwoD operator[](uint64_t x_index);

    ThreeDArray operator*(uint32_t number);
    ThreeDArray operator+(ThreeDArray& add);
    ThreeDArray operator-(ThreeDArray& sub);

    size_t CalculateTotalMemoryUsage() const {
        size_t objectSize = sizeof(*this);  // Size of the ThreeDArray object itself
        size_t mainArrSize = total_size_ * sizeof(uint16_t);  // Size of the main array
        size_t extraBitArrSize = (total_size_ / 8 + 1) * sizeof(uint8_t);  // Size of the extra bit array

        return objectSize + mainArrSize + extraBitArrSize;
    }


};

std::ostream& operator<<(std::ostream& stream, const ThreeDArray& array);
std::istream& operator>>(std::istream& stream, ThreeDArray& array);

#endif // THREE_D_ARRAY_H
