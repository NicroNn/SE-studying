#include <iostream>
#include <cinttypes>
#include <cstring>
#include <iomanip>
#include <string>

enum class RoundingMode {
    TowardZero,
    NearestEven,
    TowardInfinity,
    TowardNegInfinity
};

class MyFixedPoint {
private:
    int16_t intSize_;
    int16_t fracSize_;
    int32_t value_;
    RoundingMode roundingMode_;

public:
    uint64_t applyRounding(uint64_t result, uint64_t frac, uint64_t rhs, bool isNegative) {
        if (roundingMode_ == RoundingMode::NearestEven) {
            if (((frac << 1) > rhs) || ((frac << 1) == rhs && (result & 1))) {
                result++;
            }
        }
        if (roundingMode_ == RoundingMode::TowardInfinity) {
            if (frac != 0 && !isNegative) {
                result++;
            }
        }
        if (roundingMode_ == RoundingMode::TowardNegInfinity) {
            if (frac != 0 && isNegative) {
                result++;
            }
        }
        return result;
    }

    MyFixedPoint(int16_t intSize, int16_t fracSize, int32_t value, RoundingMode roundingMode) {
        intSize_ = intSize;
        fracSize_ = fracSize;
        value <<= (32 - intSize - fracSize);
        value >>= (32 - intSize - fracSize);
        value_ = value;
        roundingMode_ = roundingMode;
    }

    MyFixedPoint operator+(const MyFixedPoint &other) {
        return {intSize_, fracSize_, (int32_t) (value_ + other.value_), roundingMode_};
    }

    MyFixedPoint operator-(const MyFixedPoint &other) {
        return {intSize_, fracSize_, (int32_t) (value_ - other.value_), roundingMode_};
    }

    MyFixedPoint operator*(const MyFixedPoint &other) {
        bool isNegative = ((value_ < 0) ^ (other.value_ < 0));
        uint64_t lhs = abs(value_);
        uint64_t rhs = abs(other.value_);
        uint64_t result = (lhs * rhs) >> fracSize_;
        uint64_t frac = (lhs * rhs) & (((uint64_t) 1 << fracSize_) - 1);

        result = applyRounding(result, frac, rhs, isNegative);

        result = (isNegative) ? -result : result;

        return {intSize_, fracSize_, (int32_t) result, roundingMode_};
    }

    MyFixedPoint operator/(const MyFixedPoint &other) {
        if (other.value_ == 0) {
            std::cout << "division by zero";
            exit(0);
        }

        bool isNegative = ((value_ < 0) ^ (other.value_ < 0));
        uint64_t lhs = abs(value_);
        uint64_t rhs = abs(other.value_);
        uint64_t result = (lhs << fracSize_) / rhs;
        uint64_t frac = (lhs << fracSize_) % rhs;

        result = applyRounding(result, frac, rhs, isNegative);

        result = (isNegative) ? -result : result;

        return {intSize_, fracSize_, (int32_t) result, roundingMode_};
    }

    friend std::ostream &operator<<(std::ostream &stream, MyFixedPoint &num) {
        MyFixedPoint temp = num;
        const int kFracOutLen = 3;

        int64_t deg = 1000;

        temp.value_ <<= (32 - temp.intSize_ - temp.fracSize_);
        temp.value_ >>= (32 - temp.intSize_ - temp.fracSize_);

        bool isNegative = (temp.value_ >> (temp.intSize_ + temp.fracSize_ - 1)) & 1;
        if (isNegative) {
            temp.value_ = -temp.value_;
        }

        int64_t result = (temp.value_ * deg) >> temp.fracSize_;
        int64_t frac = (temp.value_ * deg) & (((int64_t) 1 << temp.fracSize_) - 1);

        result = num.applyRounding(result, (frac >> 1), ((uint64_t) 1 << (temp.fracSize_ - 1)), isNegative);

        if (result != 0 && isNegative) {
            stream << "-";
        }
        stream << result / deg << ".";
        std::string out = std::to_string(result % deg);
        out.insert(out.begin(), kFracOutLen - out.size(), '0');
        stream << out;

        return stream;
    }
};

enum class Precision {
    Half,
    Single
};

struct FloatComponents {
    uint64_t mantissa;
    int64_t exponent;
    uint64_t sign;

    FloatComponents(uint64_t mantissa_, int64_t exponent_, uint64_t sign_) {
        mantissa = mantissa_;
        exponent = exponent_;
        sign = sign_;
    }
};

template<Precision precision>
class MyFloatingPoint {
private:
    Precision precision_;
    int16_t size_;
    int16_t mantissaSize_;
    int16_t exponentSize_;
    uint32_t mantissaMask_;
    uint32_t exponentMask_;
    uint32_t value_;
    RoundingMode roundingMode_;

    FloatComponents getComps(uint32_t value) {
        return {value & mantissaMask_, (value >> mantissaSize_) & exponentMask_, (value >> (size_ - 1)) & 1};
    }

    void normalizeMantissaExponent(uint64_t &mantissa, int64_t &exponent) {
        if (exponent != 0) {
            mantissa |= ((uint64_t) 1 << mantissaSize_);
        } else {
            exponent++;
        }
    }

    void roundTowardZero(uint64_t &mantissa, int64_t &exponent) {
        mantissa &= mantissaMask_;
        if (exponent >= exponentMask_) {
            exponent = exponentMask_ - 1;
            mantissa = mantissaMask_;
        }
    }

    void roundNearestEven(uint64_t &mantissa, int64_t &exponent, uint64_t lostBits, int64_t lostSize) {
        if ((lostBits > ((uint64_t) 1 << (lostSize - 1))) ||
            (lostBits == ((uint64_t) 1 << (lostSize - 1)) && (mantissa & 1))) {
            mantissa++;
        }
        if ((mantissa >> mantissaSize_) > 1) {
            exponent++;
            mantissa >>= 1;
        }

        mantissa &= mantissaMask_;
        if (exponent >= exponentMask_) {
            exponent = exponentMask_;
            mantissa = 0;
        }
    }

    void roundTowardInfinity(uint64_t &mantissa, int64_t &exponent, uint64_t lostBits, uint64_t sign) {
        if (lostBits != 0 && !sign) {
            mantissa++;
        }
        if ((mantissa >> mantissaSize_) > 1) {
            exponent++;
            mantissa >>= 1;
        }

        mantissa &= mantissaMask_;
        if (exponent >= exponentMask_) {
            exponent = exponentMask_ - sign;
            mantissa = mantissaMask_ * sign;
        }
    }

    void roundTowardNegInfinity(uint64_t &mantissa, int64_t &exponent, uint64_t lostBits, uint64_t sign) {
        if (lostBits != 0 && sign) {
            mantissa++;
        }
        if ((mantissa >> mantissaSize_) > 1) {
            exponent++;
            mantissa >>= 1;
        }

        mantissa &= mantissaMask_;
        if (exponent >= exponentMask_) {
            exponent = exponentMask_ - (sign ^ 1);
            mantissa = mantissaMask_ * (sign ^ 1);
        }
    }

    std::pair<bool, MyFloatingPoint> handleSpecialCases(FloatComponents lhs, FloatComponents rhs) {
        auto isNaN = [this](FloatComponents f) {
            return f.exponent == exponentMask_ && f.mantissa != 0;
        };

        auto isInfinity = [this](FloatComponents f) {
            return f.exponent == exponentMask_ && f.mantissa == 0;
        };

        auto isZero = [](FloatComponents f) {
            return f.exponent == 0 && f.mantissa == 0;
        };

        // NaN
        if (isNaN(lhs) || isNaN(rhs)) {
            return {true, MyFloatingPoint((exponentMask_ << mantissaSize_) + mantissaMask_, roundingMode_)};
        }

        // Infinity
        if (isInfinity(lhs)) {
            if (isInfinity(rhs)) {
                return {true, MyFloatingPoint((exponentMask_ << mantissaSize_) + mantissaMask_, roundingMode_)}; // NaN
            }
            if (isZero(rhs)) {
                return {true, MyFloatingPoint((exponentMask_ << mantissaSize_) + mantissaMask_, roundingMode_)}; // NaN
            }
            return {true, MyFloatingPoint(((lhs.sign ^ rhs.sign) << (size_ - 1)) | (exponentMask_ << mantissaSize_),
                                          roundingMode_)};
        }

        if (isInfinity(rhs)) {
            if (isZero(lhs)) {
                return {true, MyFloatingPoint(0, roundingMode_)}; // Zero
            }
            return {true, MyFloatingPoint(((lhs.sign ^ rhs.sign) << (size_ - 1)), roundingMode_)}; // Zero
        }

        // Zero
        if (isZero(lhs) && isZero(rhs)) {
            return {true, MyFloatingPoint((exponentMask_ << mantissaSize_) + mantissaMask_, roundingMode_)}; // NaN
        }

        if (isZero(rhs)) {
            return {true, MyFloatingPoint(((lhs.sign ^ rhs.sign) << (size_ - 1)) | (exponentMask_ << mantissaSize_),
                                          roundingMode_)}; // Infinity
        }

        if (isZero(lhs)) {
            return {true, MyFloatingPoint(((lhs.sign ^ rhs.sign) << (size_ - 1)), roundingMode_)}; // Zero
        }

        return {false, MyFloatingPoint(0, roundingMode_)};
    }

    void handleLostBits(FloatComponents &res, uint64_t &lost, int64_t &lostSize, bool isPlus) {
        while ((res.mantissa >> mantissaSize_) != 1) {
            if ((res.mantissa >> mantissaSize_) > 1) {
                lostSize++;
                res.mantissa >>= 1;
                res.exponent++;
            } else {
                if (res.exponent <= 0 && !isPlus) {
                    break;
                }
                if (res.exponent == 1 && isPlus) {
                    res.exponent--;
                    break;
                }
                lostSize--;
                res.mantissa <<= 1;
                res.exponent--;
            }
        }
        if (res.exponent <= 0 && !isPlus) {
            res.mantissa >>= std::min(-res.exponent + 1, (int64_t) 63);
            lostSize += -res.exponent + 1;
            res.exponent = 0;
        }
        lostSize = std::max(lostSize, (int64_t) 0);
        if (lostSize < 64) {
            lost &= ((uint64_t) 1 << lostSize) - 1;
        }
        lostSize = std::min(lostSize, (int64_t) 64);
    }

    int determineAdjustment(bool sameSign, bool sign) const {
        if (sameSign) {
            if ((sign && roundingMode_ == RoundingMode::TowardNegInfinity) ||
                (!sign && roundingMode_ == RoundingMode::TowardInfinity)) {
                return 1;
            }
        } else {
            if ((sign && roundingMode_ == RoundingMode::TowardInfinity) ||
                roundingMode_ == RoundingMode::TowardZero ||
                (!sign && roundingMode_ == RoundingMode::TowardNegInfinity)) {
                return -1;
            }
        }
        return 0;
    }

public:
    MyFloatingPoint(uint32_t value, RoundingMode roundingMode) {
        precision_ = precision;
        size_ = (precision == Precision::Half) ? 16 : 32;
        mantissaSize_ = (precision == Precision::Half) ? 10 : 23;
        exponentSize_ = (precision == Precision::Half) ? 5 : 8;
        mantissaMask_ = ((uint64_t) 1 << mantissaSize_) - 1;
        exponentMask_ = ((uint64_t) 1 << exponentSize_) - 1;
        value_ = value;
        roundingMode_ = roundingMode;
    }

    MyFloatingPoint operator+(const MyFloatingPoint &other) {
        FloatComponents lhs = getComps(value_);
        FloatComponents rhs = getComps(other.value_);

        if ((lhs.exponent == 0 && lhs.mantissa == 0) && (rhs.exponent == 0 && rhs.mantissa == 0)) {
            if (lhs.sign && rhs.sign && roundingMode_ == RoundingMode::TowardNegInfinity) {
                return MyFloatingPoint(((uint64_t)1 << (size_ - 1)), roundingMode_);
            }
            return MyFloatingPoint(0, roundingMode_);
        }

        auto [isSpecial, specialResult] = handleSpecialCases(lhs, rhs);
        if (isSpecial) return specialResult;
        
        normalizeMantissaExponent(lhs.mantissa, lhs.exponent);
        normalizeMantissaExponent(rhs.mantissa, rhs.exponent);

        int16_t diffExponent = lhs.exponent - rhs.exponent;
        if (diffExponent < 0) {
            std::swap(lhs, rhs);
            diffExponent = -diffExponent;
        }

        FloatComponents res = {0, lhs.exponent, 0};

        if (diffExponent > mantissaSize_ + 1) {
            bool sameSign = !(lhs.sign ^ rhs.sign);
            int adjustment = determineAdjustment(sameSign, lhs.sign);

            lhs.mantissa += adjustment;

            res.mantissa = lhs.mantissa;
            res.exponent = lhs.exponent;
            res.sign = lhs.sign;
        } else {
            lhs.mantissa <<= diffExponent;
            lhs.exponent = rhs.exponent;

            int64_t signedLhsMantissa = lhs.sign ? -lhs.mantissa : lhs.mantissa;
            int64_t signedRhsMantissa = rhs.sign ? -rhs.mantissa : rhs.mantissa;

            int64_t signedResult = signedLhsMantissa + signedRhsMantissa;

            res.sign = signedResult < 0;
            res.mantissa = std::abs(signedResult);
            res.exponent = lhs.exponent;
        }

        uint64_t lost = res.mantissa;
        int64_t lostSize = 0;
        handleLostBits(res, lost, lostSize, true);

        if (roundingMode_ == RoundingMode::TowardZero) roundTowardZero(res.mantissa, res.exponent);
        if (roundingMode_ == RoundingMode::NearestEven) roundNearestEven(res.mantissa, res.exponent, lost, lostSize);
        if (roundingMode_ == RoundingMode::TowardInfinity)
            roundTowardInfinity(res.mantissa, res.exponent, lost, res.sign);
        if (roundingMode_ == RoundingMode::TowardNegInfinity)
            roundTowardNegInfinity(res.mantissa, res.exponent, lost, res.sign);

        if (res.exponent == 0 && res.mantissa == 0) {
            if (roundingMode_ == RoundingMode::TowardNegInfinity) {
                return MyFloatingPoint(((uint64_t) 1 << (size_ - 1)), roundingMode_);
            }
            return MyFloatingPoint(0, roundingMode_);
        }

        return MyFloatingPoint(res.mantissa | (res.exponent << mantissaSize_) | (res.sign << (size_ - 1)),
                               roundingMode_);
    }

    MyFloatingPoint operator-(const MyFloatingPoint &other) {
        MyFloatingPoint rhs = other;
        rhs.value_ ^= ((uint64_t) 1 << (size_ - 1));
        return *this + rhs;
    }

    MyFloatingPoint operator*(const MyFloatingPoint &other) {
        FloatComponents lhs = getComps(value_);
        FloatComponents rhs = getComps(other.value_);

        auto [isSpecial, specialResult] = handleSpecialCases(lhs, rhs);
        if (isSpecial) return specialResult;

        normalizeMantissaExponent(lhs.mantissa, lhs.exponent);
        normalizeMantissaExponent(rhs.mantissa, rhs.exponent);

        FloatComponents res = FloatComponents(lhs.mantissa * rhs.mantissa,
                                              lhs.exponent + rhs.exponent - ((uint64_t) 1 << (exponentSize_ - 1)) + 1
                                              - mantissaSize_,
                                              lhs.sign ^ rhs.sign);

        uint64_t lost = res.mantissa;
        int64_t lostSize = 0;
        handleLostBits(res, lost, lostSize, false);

        if (roundingMode_ == RoundingMode::TowardZero) roundTowardZero(res.mantissa, res.exponent);
        if (roundingMode_ == RoundingMode::NearestEven) roundNearestEven(res.mantissa, res.exponent, lost, lostSize);
        if (roundingMode_ == RoundingMode::TowardInfinity)
            roundTowardInfinity(res.mantissa, res.exponent, lost, res.sign);
        if (roundingMode_ == RoundingMode::TowardNegInfinity)
            roundTowardNegInfinity(res.mantissa, res.exponent, lost, res.sign);

        return MyFloatingPoint(res.mantissa | (res.exponent << mantissaSize_) | (res.sign << (size_ - 1)),
                               roundingMode_);
    }

    MyFloatingPoint operator/(const MyFloatingPoint &other) {
        FloatComponents lhs = getComps(value_);
        FloatComponents rhs = getComps(other.value_);

        if (rhs.exponent == 0 && rhs.mantissa == 0 || lhs.mantissa == rhs.mantissa && rhs.exponent == 0)
            return MyFloatingPoint(((lhs.sign ^ rhs.sign) << (size_ - 1)) | (exponentMask_ << mantissaSize_),
                                   roundingMode_);

        auto [isSpecial, specialResult] = handleSpecialCases(lhs, rhs);
        if (isSpecial) return specialResult;

        normalizeMantissaExponent(lhs.mantissa, lhs.exponent);
        normalizeMantissaExponent(rhs.mantissa, rhs.exponent);

        int32_t shift = 64 - 2 * mantissaSize_ - 2;

        FloatComponents res = FloatComponents((lhs.mantissa << (shift + mantissaSize_)) / rhs.mantissa,
                                              lhs.exponent - rhs.exponent + ((uint64_t) 1 << (exponentSize_ - 1)) - 1
                                              - shift,
                                              lhs.sign ^ rhs.sign);

        MyFixedPoint helperNum = {8, 8, 0, roundingMode_};

        uint64_t temp = (lhs.mantissa << (shift + mantissaSize_)) % rhs.mantissa;
        res.mantissa = helperNum.applyRounding(res.mantissa, temp, rhs.mantissa, res.sign);

        uint64_t lost = res.mantissa;
        int64_t lostSize = 0;
        handleLostBits(res, lost, lostSize, false);

        if (roundingMode_ == RoundingMode::TowardZero) roundTowardZero(res.mantissa, res.exponent);
        if (roundingMode_ == RoundingMode::NearestEven) roundNearestEven(res.mantissa, res.exponent, lost, lostSize);
        if (roundingMode_ == RoundingMode::TowardInfinity)
            roundTowardInfinity(res.mantissa, res.exponent, lost, res.sign);
        if (roundingMode_ == RoundingMode::TowardNegInfinity)
            roundTowardNegInfinity(res.mantissa, res.exponent, lost, res.sign);

        return MyFloatingPoint(res.mantissa | (res.exponent << mantissaSize_) | (res.sign << (size_ - 1)),
                               roundingMode_);
    }

    friend std::ostream &operator<<(std::ostream &stream, MyFloatingPoint &num) {
        const int kOutPrecision = (num.precision_ == Precision::Half) ? 3 : 6;

        FloatComponents comps = num.getComps(num.value_);

        if (comps.exponent == num.exponentMask_) {
            if (comps.mantissa == 0) {
                stream << ((comps.sign == 0) ? "inf" : "-inf");
            } else {
                stream << "nan";
            }
            return stream;
        }
        if (comps.exponent == 0 && comps.mantissa == 0) {
            stream << (comps.sign ? "-" : "") << "0x0." << std::string(kOutPrecision, '0') << "p+0";
            return stream;
        }

        if (comps.exponent == 0) {
            while ((comps.mantissa >> num.mantissaSize_) != 1) {
                comps.mantissa <<= 1;
                comps.exponent--;
            }
            comps.exponent++;
            comps.mantissa &= num.mantissaMask_;
        }

        stream << (comps.sign ? "-" : "") << "0x1." << std::hex << std::setw(kOutPrecision) << std::setfill('0')
               << std::right << (comps.mantissa << (kOutPrecision * 4 - num.mantissaSize_)) << std::dec << "p";
        int32_t exp_value = comps.exponent - ((uint64_t) 1 << (num.exponentSize_ - 1)) + 1;
        stream << (exp_value >= 0 ? "+" : "") << exp_value;

        return stream;
    }
};

int main(int argc, char *argv[]) {
    std::string numType = argv[1];
    bool isFixed = ((numType != "f") && (numType != "h"));

    bool isSingleNum = argc == 4;
    if (isFixed) {
        char *token = std::strtok(argv[1], ".");
        int intSize = std::stoi(token);
        token = std::strtok(nullptr, ".");
        int fracSize = std::stoi(token);
        RoundingMode rounding_mode = static_cast<RoundingMode>(std::stoi(argv[2]));
        MyFixedPoint num1(intSize, fracSize, std::stoll(argv[3], nullptr, 16), rounding_mode);
        if (isSingleNum) {
            std::cout << num1;
        } else {
            std::string op = argv[4];
            MyFixedPoint num2(intSize, fracSize, std::stoll(argv[argc - 1], nullptr, 16), rounding_mode);
            MyFixedPoint res(intSize, fracSize, 0, rounding_mode);
            if (op == "+") res = num1 + num2;
            if (op == "-") res = num1 - num2;
            if (op == "*" || op == "M" || op == "x") res = num1 * num2;
            if (op == "/") res = num1 / num2;

            std::cout << res;
        }
    } else {
        if (numType == "f") {
            RoundingMode rounding_mode = static_cast<RoundingMode>(std::stoi(argv[2]));
            MyFloatingPoint<Precision::Single> num1(std::stoull(argv[3], nullptr, 16), rounding_mode);
            if (isSingleNum) {
                std::cout << num1;
            } else {
                std::string op = argv[4];
                MyFloatingPoint<Precision::Single> num2(std::stoull(argv[5], nullptr, 16), rounding_mode);
                MyFloatingPoint<Precision::Single> res(0, rounding_mode);
                if (op == "+") res = num1 + num2;
                if (op == "-") res = num1 - num2;
                if (op == "*" || op == "M" || op == "x") res = num1 * num2;
                if (op == "/") res = num1 / num2;

                std::cout << res;
            }
        } else {
            RoundingMode rounding_mode = static_cast<RoundingMode>(std::stoi(argv[2]));
            MyFloatingPoint<Precision::Half> num1(std::stoull(argv[3], nullptr, 16), rounding_mode);
            if (isSingleNum) {
                std::cout << num1;
            } else {
                std::string op = argv[4];
                MyFloatingPoint<Precision::Half> num2(std::stoull(argv[5], nullptr, 16), rounding_mode);
                MyFloatingPoint<Precision::Half> res(0, rounding_mode);
                if (op == "+") res = num1 + num2;
                if (op == "-") res = num1 - num2;
                if (op == "*" || op == "M" || op == "x") res = num1 * num2;
                if (op == "/") res = num1 / num2;

                std::cout << res;
            }
        }
    }

    return 0;
}
