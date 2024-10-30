#ifndef SE_COMP_ARCH24_CACHE_ISA_NICRONN__CACHE_H_
#define SE_COMP_ARCH24_CACHE_ISA_NICRONN__CACHE_H_
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <optional>
#include <iostream>
#include <list>
#include <bitset>

// Cache parameters
#define MEM_SIZE 262144    // 256 * 1024
#define ADDR_LEN 18
#define CACHE_WAY 4
#define CACHE_TAG_LEN 9
#define CACHE_INDEX_LEN 3
#define CACHE_OFFSET_LEN 6
#define CACHE_SIZE 2048   // 32 * 64
#define CACHE_LINE_SIZE 64
#define CACHE_LINE_COUNT 32
#define CACHE_SETS 8

class MemoryLRU {
  private:
    struct CacheLine {
        std::vector<uint8_t> cache_line_;
        uint32_t tag_ = 0xFFFFFFFF;

        CacheLine(uint32_t tag) : tag_(tag) {
            cache_line_.resize(CACHE_LINE_SIZE);
        }
    };

    std::vector<uint8_t> memory_;
    std::vector<std::list<CacheLine>> cache_;
    size_t cache_hit_ = 0;
    size_t requests_ = 0;

    const uint32_t tag_mask_ = 0x3FE00;  //CACHE_TAG_LEN * "1" + (ADDR_LEN - CACHE_TAG_LEN) * "0"
    const uint32_t index_mask_ = 0x1C0;  //CACHE_INDEX_LEN * "1" + (ADDR_LEN - CACHE_TAG_LEN - CACHE_INDEX_LEN) * "0"
    const uint32_t offset_mask_ = 0x3F;  //CACHE_OFFSET_LEN * "1"

    bool putByte(uint32_t addr, uint8_t data) {
        uint32_t tag = (addr & tag_mask_) >> CACHE_TAG_LEN;
        uint8_t index = (addr & index_mask_) >> CACHE_OFFSET_LEN;
        uint8_t offset = addr & offset_mask_;

        for (auto it = cache_[index].begin(); it != cache_[index].end(); ++it) {
            if (it->tag_ == tag) {
                auto temp = *it;
                cache_[index].erase(it);
                cache_[index].push_front(temp);
                temp.cache_line_[offset] = data;
                return true;
            }
        }

        if (cache_[index].size() == CACHE_WAY) {
            cache_[index].pop_back();
        }

        CacheLine new_line(tag);
        new_line.cache_line_[offset] = data;
        cache_[index].push_front(new_line);
        return false;
    }

    std::optional<uint8_t> getByte(uint32_t addr) {
        uint32_t tag = (addr & tag_mask_) >> CACHE_TAG_LEN;
        uint8_t index = (addr & index_mask_) >> CACHE_OFFSET_LEN;
        uint8_t offset = addr & offset_mask_;

        for (auto it = cache_[index].begin(); it != cache_[index].end(); ++it) {
            if (it->tag_ == tag) {
                auto temp = *it;
                cache_[index].erase(it);
                cache_[index].push_front(temp);
                return temp.cache_line_[offset];
            }
        }

        return std::nullopt;
    }

    void placeLine(uint32_t addr, const std::vector<uint8_t>& data) {
        for (uint8_t i = 0; i < CACHE_LINE_SIZE; ++i) {
            putByte(addr + i, data[i]);
        }
    }

    bool memoryPut(uint32_t addr, uint32_t data, uint8_t size) {
        bool full_hit = true;
        for (uint8_t i = 0; i < size; ++i) {
            full_hit &= putByte(addr + i, (data >> ((size - i - 1) * 8)));
        }

        if (full_hit) {
            ++cache_hit_;
        }

        for (uint8_t i = 0; i < size; ++i) {
            memory_[addr + i] = (data >> ((size - i - 1) * 8));
        }

        return full_hit;
    }

    std::optional<uint32_t> memoryGet(uint32_t addr, uint8_t size) {
        uint32_t data = 0;
        for (uint8_t i = 0; i < size; ++i) {
            std::optional<uint8_t> byte = getByte(addr + i);
            if (!byte.has_value()) {
                --cache_hit_;
                return std::nullopt;
            }
            data = (data << 8) | byte.value();
        }

        ++cache_hit_;
        return data;
    }

  public:
    MemoryLRU() {
        memory_.resize(MEM_SIZE);
        cache_.resize(CACHE_SETS);
    }

    uint32_t get(uint32_t addr, uint8_t size) {
        if (size > 4 || addr >= MEM_SIZE) {
            throw std::length_error("Invalid access");
        }

        ++requests_;
        std::optional<uint32_t> data = memoryGet(addr, size);
        if (data.has_value()) {
            return data.value();
        } else {
            uint32_t line_addr = addr & ~offset_mask_;
            placeLine(line_addr,
                      std::vector<uint8_t>(memory_.begin() + line_addr, memory_.begin() + line_addr + CACHE_LINE_SIZE));
            if ((size + (addr & offset_mask_)) > CACHE_LINE_SIZE) {
                placeLine(line_addr + CACHE_LINE_SIZE,
                          std::vector<uint8_t>(memory_.begin() + line_addr + CACHE_LINE_SIZE,
                                               memory_.begin() + line_addr + 2 * CACHE_LINE_SIZE));
            }
            return memoryGet(addr, size).value();
        }
    }

    void put(uint32_t addr, uint32_t data, uint8_t size) {
        if (size > 4 || addr >= MEM_SIZE) {
            throw std::length_error("Invalid access");
        }

        memoryPut(addr, data, size);
        ++requests_;
    }

    float getCacheHitRate() const {
        return float(cache_hit_) / requests_;
    }
};

class MemorypLRU {
  private:
    struct CacheLine {
        std::vector<uint8_t> cache_line_;
        uint32_t tag_ = 0xFFFFFFFF;
        bool bit_ = false;

        CacheLine(uint32_t tag) : tag_(tag) {
            cache_line_.resize(CACHE_LINE_SIZE);
        }
    };

    std::vector<uint8_t> memory_;
    std::vector<std::list<CacheLine>> cache_;
    size_t cache_hit_ = 0;
    size_t requests_ = 0;

    const uint32_t tag_mask_ = 0x3FE00; //CACHE_TAG_LEN "1" + (ADDR_LEN - CACHE_TAG_LEN) "0"
    const uint32_t index_mask_ = 0x1C0; //CACHE_INDEX_LEN "1" + (ADDR_LEN - CACHE_TAG_LEN - CACHE_INDEX_LEN) "0"
    const uint32_t offset_mask_ = 0x3F; //CACHE_OFFSET_LEN * "1"

    bool putByte(uint32_t addr, uint8_t data) {
        uint32_t tag = (addr & tag_mask_) >> CACHE_TAG_LEN;
        uint8_t index = (addr & index_mask_) >> CACHE_OFFSET_LEN;
        uint8_t offset = addr & offset_mask_;

        for (auto it = cache_[index].begin(); it != cache_[index].end(); ++it) {
            if (it->tag_ == tag) {
                auto temp = *it;
                cache_[index].erase(it);
                cache_[index].push_front(temp);
                temp.cache_line_[offset] = data;
                temp.bit_ = true;
                return true;
            }
        }

        if (cache_[index].size() == CACHE_WAY) {
            auto victim = std::find_if(cache_[index].begin(), cache_[index].end(), [](const CacheLine& line) { return !line.bit_; });
            if (victim == cache_[index].end()) {
                for (auto& line : cache_[index]) {
                    line.bit_ = false;
                }
                victim = cache_[index].begin();
            }
            cache_[index].erase(victim);
        }

        CacheLine new_line(tag);
        new_line.cache_line_[offset] = data;
        new_line.bit_ = true;
        cache_[index].push_front(new_line);
        return false;
    }

    std::optional<uint8_t> getByte(uint32_t addr) {
        uint32_t tag = (addr & tag_mask_) >> CACHE_TAG_LEN;
        uint8_t index = (addr & index_mask_) >> CACHE_OFFSET_LEN;
        uint8_t offset = addr & offset_mask_;

        for (auto it = cache_[index].begin(); it != cache_[index].end(); ++it) {
            if (it->tag_ == tag) {
                auto temp = *it;
                cache_[index].erase(it);
                cache_[index].push_front(temp);
                temp.bit_ = true;
                return temp.cache_line_[offset];
            }
        }

        return std::nullopt;
    }

    void placeLine(uint32_t addr, const std::vector<uint8_t>& data) {
        for (uint8_t i = 0; i < CACHE_LINE_SIZE; ++i) {
            putByte(addr + i, data[i]);
        }
    }

    bool memoryPut(uint32_t addr, uint32_t data, uint8_t size) {
        bool full_hit = true;
        for (uint8_t i = 0; i < size; ++i) {
            full_hit &= putByte(addr + i, (data >> ((size - i - 1) * 8)));
        }

        if (full_hit) {
            ++cache_hit_;
        }

        for (uint8_t i = 0; i < size; ++i) {
            memory_[addr + i] = (data >> ((size - i - 1) * 8));
        }

        return full_hit;
    }

    std::optional<uint32_t> memoryGet(uint32_t addr, uint8_t size) {
        uint32_t data = 0;
        for (uint8_t i = 0; i < size; ++i) {
            std::optional<uint8_t> byte = getByte(addr + i);
            if (!byte.has_value()) {
                --cache_hit_;
                return std::nullopt;
            }
            data = (data << 8) | byte.value();
        }

        ++cache_hit_;
        return data;
    }

  public:
    MemorypLRU() {
        memory_.resize(MEM_SIZE);
        cache_.resize(CACHE_SETS);
    }

    uint32_t get(uint32_t addr, uint8_t size) {
        if (size > 4 || addr >= MEM_SIZE) {
            throw std::length_error("Invalid access");
        }

        ++requests_;
        std::optional<uint32_t> data = memoryGet(addr, size);
        if (data.has_value()) {
            return data.value();
        } else {
            uint32_t line_addr = addr & ~offset_mask_;
            placeLine(line_addr,
                      std::vector<uint8_t>(memory_.begin() + line_addr, memory_.begin() + line_addr + CACHE_LINE_SIZE));
            if ((size + (addr & offset_mask_)) > CACHE_LINE_SIZE) {
                placeLine(line_addr + CACHE_LINE_SIZE,
                          std::vector<uint8_t>(memory_.begin() + line_addr + CACHE_LINE_SIZE,
                                               memory_.begin() + line_addr + 2 * CACHE_LINE_SIZE));
            }
            return memoryGet(addr, size).value();
        }
    }

    void put(uint32_t addr, uint32_t data, uint8_t size) {
        if (size > 4 || addr >= MEM_SIZE) {
            throw std::length_error("Invalid access");
        }

        memoryPut(addr, data, size);
        ++requests_;
    }

    float getCacheHitRate() const {
        return float(cache_hit_) / requests_;
    }
};

#endif //SE_COMP_ARCH24_CACHE_ISA_NICRONN__CACHE_H_
