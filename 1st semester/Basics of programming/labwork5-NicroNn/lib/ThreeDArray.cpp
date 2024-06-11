#include "ThreeDArray.h"

ThreeDArray::ThreeDArray(uint64_t height, uint64_t width, uint64_t depth)
    : height_(height), width_(width), depth_(depth) {
    total_size_ = height * width * depth;
    extra_field_ = 0;
    main_arr_ = new uint16_t[total_size_]{};
    extra_bit_arr_ = new uint8_t[total_size_ / 8 + 1]{};
}

ThreeDArray ThreeDArray::make_array(uint64_t height, uint64_t width, uint64_t depth) {
    return {height, width, depth};
}

ThreeDArray::ThreeDArray(const ThreeDArray& other)
    : height_(other.height_), width_(other.width_), depth_(other.depth_), total_size_(other.total_size_) {
    main_arr_ = new uint16_t[total_size_];
    extra_bit_arr_ = new uint8_t[total_size_ / 8 + 1];

    std::copy(other.main_arr_, other.main_arr_ + total_size_, main_arr_);
    std::copy(other.extra_bit_arr_, other.extra_bit_arr_ + total_size_ / 8 + 1, extra_bit_arr_);
}

ThreeDArray& ThreeDArray::operator=(const ThreeDArray& other) {
    if (this != &other) {
        delete[] main_arr_;
        delete[] extra_bit_arr_;

        height_ = other.height_;
        width_ = other.width_;
        depth_ = other.depth_;
        total_size_ = other.total_size_;

        main_arr_ = new uint16_t[total_size_];
        extra_bit_arr_ = new uint8_t[total_size_ / 8 + 1];

        std::copy(other.main_arr_, other.main_arr_ + total_size_, main_arr_);
        std::copy(other.extra_bit_arr_, other.extra_bit_arr_ + total_size_ / 8 + 1, extra_bit_arr_);
    }

    return *this;
}

ThreeDArray::~ThreeDArray() {
    delete[] main_arr_;
    delete[] extra_bit_arr_;
}

uint64_t ThreeDArray::GetSize() const {
    return total_size_;
}

uint64_t ThreeDArray::GetHeight() const {
    return height_;
}

uint64_t ThreeDArray::GetWidth() const {
    return width_;
}

uint64_t ThreeDArray::GetDepth() const {
    return depth_;
}

uint16_t& ThreeDArray::operator()(uint64_t i, uint64_t j, uint64_t k) {
    uint64_t index = i * (width_ * depth_) + j * depth_ + k;
    return main_arr_[index];
}

uint16_t ThreeDArray::GetElement(uint64_t index) const {
    return main_arr_[index];
}

uint8_t ThreeDArray::GetBits(uint64_t index) const {
    return extra_bit_arr_[index];
}

uint16_t& ThreeDArray::AccessElement(uint64_t index) {
    return main_arr_[index];
}

void ThreeDArray::SetBits(uint64_t index, uint8_t bits) {
    extra_bit_arr_[index] |= bits;
}

void ThreeDArray::ExtraFieldToArray(uint64_t index) {
    uint64_t bitIndex = index / 8;
    uint8_t bitOffset = index % 8;
    main_arr_[index] = extra_field_ % (1 << 16);
    if (extra_field_ >= (1 << 16)) {
        extra_bit_arr_[bitIndex] |= (1 << bitOffset);
    }
}

uint32_t& ThreeDArray::AccessExtraField(uint64_t index) {
    uint64_t bitIndex = index / 8;
    uint8_t bitOffset = index % 8;
    extra_field_ = main_arr_[index] + (extra_bit_arr_[bitIndex] & (1 << bitOffset)) * (1 << (16 - bitOffset));
    ExtraFieldToArray(index);

    return extra_field_;
}

ThreeDArray::OneD::OneD(ThreeDArray& array, uint64_t x_index, uint64_t y_index)
    : array_(array), x_index_(x_index), y_index_(y_index) {}

uint16_t& ThreeDArray::OneD::operator[](uint64_t z_index) {
    uint64_t index = x_index_ * (array_.GetWidth() * array_.GetDepth()) + y_index_ * array_.GetDepth() + z_index;
    return array_.AccessElement(index);
}

ThreeDArray::TwoD::TwoD(ThreeDArray& array, uint64_t x_index)
    : array_(array), x_index_(x_index) {}

ThreeDArray::OneD ThreeDArray::TwoD::operator[](uint64_t y_index) {
    return OneD(array_, x_index_, y_index);
}

ThreeDArray::TwoD ThreeDArray::operator[](uint64_t x_index) {
    return TwoD(*this, x_index);
}

ThreeDArray ThreeDArray::operator*(uint32_t number) {
    ThreeDArray result = ThreeDArray(height_, width_, depth_);
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            for (int k = 0; k < depth_; ++k) {
                uint64_t index = i * (width_ * depth_) + j * depth_ + k;
                uint64_t bitIndex = index / 8;
                uint8_t bitOffset = index % 8;
                uint32_t multiply = main_arr_[index] * number;

                if (multiply >= (1 << 16)) {
                    result.SetBits(bitIndex, 1 << bitOffset);
                    multiply %= (1 << 16);
                }
                result[i][j][k] = multiply;
            }
        }
    }

    return result;
}

ThreeDArray ThreeDArray::operator+(ThreeDArray& add) {
    ThreeDArray result = ThreeDArray(height_, width_, depth_);
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            for (int k = 0; k < depth_; ++k) {
                uint64_t index = i * (width_ * depth_) + j * depth_ + k;
                uint64_t bitIndex = index / 8;
                uint8_t bitOffset = index % 8;
                uint32_t summary = main_arr_[index] + add[i][j][k];

                if (summary >= (1 << 16)) {
                    result.SetBits(bitIndex, 1 << bitOffset);
                    summary %= (1 << 16);
                }
                result[i][j][k] = summary;
            }
        }
    }

    return result;
}

ThreeDArray ThreeDArray::operator-(ThreeDArray& sub) {
    ThreeDArray result = ThreeDArray(height_, width_, depth_);
    if (total_size_ != sub.GetSize()) {
        throw std::runtime_error("Different sizes");
    }
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            for (int k = 0; k < depth_; ++k) {
                uint64_t index = i * (width_ * depth_) + j * depth_ + k;
                uint64_t bitIndex = index / 8;
                uint8_t bitOffset = index % 8;

                if ((GetBits(bitIndex) & (1 << bitOffset)) <
                    (sub.GetBits(bitIndex) & (1 << bitOffset)) ||
                    main_arr_[index] < sub[i][j][k] && (sub.GetBits(bitIndex) & (1 << bitOffset))) {
                    throw std::runtime_error("Negative result");
                }

                uint32_t subtracted = 0;
                if (main_arr_[index] < sub[i][j][k]) {
                    if (!(extra_bit_arr_[bitIndex] & (1 << bitOffset))) {
                        throw std::runtime_error("Negative result");
                    }

                    subtracted = main_arr_[index] + (1 << 16) - sub[i][j][k];
                    extra_bit_arr_[bitIndex] &= ~(1 << bitOffset);
                } else {
                    subtracted = main_arr_[index] - sub[i][j][k];
                }

                result[i][j][k] = subtracted;
            }
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& stream, const ThreeDArray& array){
    for (int i = 0; i < array.GetSize(); ++i) {
        uint64_t bitIndex = i / 8;
        uint8_t bitOffset = i % 8;
        stream << array.GetElement(i) +  // main part
        (array.GetBits(bitIndex) & (1 << bitOffset)) * (1 << (16 - bitOffset)) << ' ';  //last bit
    }

    return stream;
}

std::istream& operator>>(std::istream& stream, ThreeDArray& array){
    for (int i = 0; i < array.GetSize(); ++i) {
        stream >> array.AccessElement(i);
    }

    return stream;
}
