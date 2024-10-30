#ifndef SE_COMP_ARCH24_CACHE_ISA_NICRONN__INSTRUCTIONS_H_
#define SE_COMP_ARCH24_CACHE_ISA_NICRONN__INSTRUCTIONS_H_
#include <iostream>
#include "system.h"
namespace RV32I {
void lui(const std::vector<std::string>& args) {
    updateReg(args[0], std::stoi(args[1]) << 12);
    PC += 4;
}
void auipc(const std::vector<std::string>& args) {
    int imm = std::stoi(args[1]) << 12;
    updateReg(args[0], PC + imm);
    PC += 4;
}
void addi(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] + std::stoi(args[2]));
    PC += 4;
}
void slti(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] < std::stoi(args[2]));
    PC += 4;
}
void sltiu(const std::vector<std::string>& args) {
    updateReg(args[0], (uint32_t) registers[args[1]] < (uint32_t) std::stoi(args[2]));
    PC += 4;
}
void xori(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] ^ std::stoi(args[2]));
    PC += 4;
}
void ori(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] | std::stoi(args[2]));
    PC += 4;
}
void andi(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] & std::stoi(args[2]));
    PC += 4;
}
void slli(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] << std::stoi(args[2]));
    PC += 4;
}
void srli(const std::vector<std::string>& args) {
    updateReg(args[0], (uint32_t) registers[args[1]] >> std::stoi(args[2]));
    PC += 4;
}
void srai(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] >> std::stoi(args[2]));
    PC += 4;
}
void add(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] + registers[args[2]]);
    PC += 4;
}
void sub(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] - registers[args[2]]);
    PC += 4;
}
void sll(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] << registers[args[2]]);
    PC += 4;
}
void slt(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] < registers[args[2]]);
    PC += 4;
}
void sltu(const std::vector<std::string>& args) {
    updateReg(args[0], (uint32_t) registers[args[1]] + (uint32_t) registers[args[2]]);
    PC += 4;
}
void Xor(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] ^ registers[args[2]]);
    PC += 4;
}
void srl(const std::vector<std::string>& args) {
    updateReg(args[0], (uint32_t) registers[args[1]] >> registers[args[2]]);
    PC += 4;
}
void sra(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] >> registers[args[2]]);
    PC += 4;
}
void Or(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] | registers[args[2]]);
    PC += 4;
}
void And(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] & registers[args[2]]);
    PC += 4;
}
void fence(const std::vector<std::string>& args) {
    std::cout << "fence is not supported\n";
}
void fence_i(const std::vector<std::string>& args) {
    std::cout << "fence_i is not supported\n";
}
void csrrw(const std::vector<std::string>& args) {
    std::cout << "csrrw is not supported\n";
}
void csrrs(const std::vector<std::string>& args) {
    std::cout << "csrrs is not supported\n";
}
void csrrc(const std::vector<std::string>& args) {
    std::cout << "csrrc is not supported\n";
}
void csrrwi(const std::vector<std::string>& args) {
    std::cout << "csrrwi is not supported\n";
}
void csrrsi(const std::vector<std::string>& args) {
    std::cout << "csrrsi is not supported\n";
}
void csrrci(const std::vector<std::string>& args) {
    std::cout << "csrrci is not supported\n";
}
void ecall(const std::vector<std::string>& args) {
    std::cout << "ecall is not supported\n";
}
void ebreak(const std::vector<std::string>& args) {
    std::cout << "ebreak is not supported\n";
}
void uret(const std::vector<std::string>& args) {
    std::cout << "uret is not supported\n";
}
void sret(const std::vector<std::string>& args) {
    std::cout << "sret is not supported\n";
}
void mret(const std::vector<std::string>& args) {
    std::cout << "mret is not supported\n";
}
void wfi(const std::vector<std::string>& args) {
    std::cout << "wfi is not supported\n";
}
void sfence_vma(const std::vector<std::string>& args) {
    std::cout << "sfence_vma is not supported\n";
}
void lb(const std::vector<std::string>& args) {
    int addr = registers[args[1]] + std::stoi(args[2]);
    uint32_t data = memory.get(addr, 1);
    uint32_t datap = memoryp.get(addr, 1);
    updateReg(args[0], static_cast<char>(data));
    PC += 4;
}

void lh(const std::vector<std::string>& args) {
    int addr = registers[args[1]] + std::stoi(args[2]);
    uint32_t data = memory.get(addr, 2);
    uint32_t datap = memoryp.get(addr, 2);
    updateReg(args[0], static_cast<int16_t>(data));
    PC += 4;
}

void lw(const std::vector<std::string>& args) {
    int addr = registers[args[1]] + std::stoi(args[2]);
    uint32_t data = memory.get(addr, 4);
    uint32_t datap = memoryp.get(addr, 4);
    updateReg(args[0], data);
    PC += 4;
}

void lbu(const std::vector<std::string>& args) {
    int addr = registers[args[1]] + std::stoi(args[2]);
    uint32_t data = memory.get(addr, 1);
    uint32_t datap = memoryp.get(addr, 1);
    updateReg(args[0], static_cast<unsigned char>(data));
    PC += 4;
}

void lhu(const std::vector<std::string>& args) {
    int addr = registers[args[1]] + std::stoi(args[2]);
    uint32_t data = memory.get(addr, 2);
    uint32_t datap = memoryp.get(addr, 2);
    updateReg(args[0], static_cast<uint16_t>(data));
    PC += 4;
}

void sb(const std::vector<std::string>& args) {
    char data = static_cast<char>(registers[args[0]]);
    int addr = registers[args[1]] + std::stoi(args[2]);
    memory.put(addr, data, 1);
    memoryp.put(addr, data, 1);
    PC += 4;
}

void sh(const std::vector<std::string>& args) {
    int16_t data = static_cast<int16_t>(registers[args[0]]);
    int addr = registers[args[1]] + std::stoi(args[2]);
    memory.put(addr, data, 2);
    memoryp.put(addr, data, 2);
    PC += 4;
}

void sw(const std::vector<std::string>& args) {
    int data = registers[args[0]];
    int addr = registers[args[1]] + std::stoi(args[2]);
    memory.put(addr, data, 4);
    memoryp.put(addr, data, 4);
    PC += 4;
}
void jal(const std::vector<std::string>& args) {
    updateReg(args[0], PC + 4);
    PC += std::stoi(args[1]);
}
void jalr(const std::vector<std::string>& args) {
    PC = registers[args[1]] + std::stoi(args[2]);
    updateReg(args[0], PC + 4);
}
void beq(const std::vector<std::string>& args) {
    if (registers[args[0]] == registers[args[1]]) {
        PC += std::stoi(args[2]);
    } else {
        PC += 4;
    }
}
void bne(const std::vector<std::string>& args) {
    if (registers[args[0]] != registers[args[1]]) {
        PC += std::stoi(args[2]);
    } else {
        PC += 4;
    }
}
void blt(const std::vector<std::string>& args) {
    if (registers[args[0]] < registers[args[1]]) {
        PC += std::stoi(args[2]);
    } else {
        PC += 4;
    }
}
void bge(const std::vector<std::string>& args) {
    if (registers[args[0]] >= registers[args[1]]) {
        PC += std::stoi(args[2]);
    } else {
        PC += 4;
    }
}
void bltu(const std::vector<std::string>& args) {
    uint32_t temp1 = registers[args[0]];
    uint32_t temp2 = registers[args[1]];
    if (temp1 < temp2) {
        PC += std::stoi(args[2]);
    } else {
        PC += 4;
    }
}
void bgeu(const std::vector<std::string>& args) {
    uint32_t temp1 = registers[args[0]];
    uint32_t temp2 = registers[args[1]];
    if (temp1 >= temp2) {
        PC += std::stoi(args[2]);
    } else {
        PC += 4;
    }
}
}

namespace RV32M {
void mul(const std::vector<std::string>& args) {
    updateReg(args[0], registers[args[1]] * registers[args[2]]);
    PC += 4;
}
void mulh(const std::vector<std::string>& args) {
    int64_t res = (int64_t) registers[args[1]] * (int64_t) registers[args[2]];
    updateReg(args[0], res >> 32);
    PC += 4;
}
void mulhsu(const std::vector<std::string>& args) {
    int64_t res = (int64_t) (int32_t) registers[args[1]] * (uint32_t) registers[args[2]];
    updateReg(args[0], res >> 32);
    PC += 4;
}
void mulhu(const std::vector<std::string>& args) {
    int64_t res = (uint64_t) registers[args[1]] * (uint64_t) registers[args[2]];
    updateReg(args[0], res >> 32);
    PC += 4;
}
void div(const std::vector<std::string>& args) {
    if (registers[args[2]] != 0) {
        updateReg(args[0], (int) registers[args[1]] / (int) registers[args[2]]);
    } else {
        updateReg(args[0], 0);
    }
    PC += 4;
}
void divu(const std::vector<std::string>& args) {
    if (registers[args[2]] != 0) {
        updateReg(args[0], (uint32_t) registers[args[1]] / (uint32_t) registers[args[2]]);
    } else {
        updateReg(args[0], 0);
    }
    PC += 4;
}
void rem(const std::vector<std::string>& args) {
    if (registers[args[2]] != 0) {
        updateReg(args[0], (int) registers[args[1]] % (int) registers[args[2]]);
    } else {
        updateReg(args[0], 0);
    }
    PC += 4;
}
void remu(const std::vector<std::string>& args) {
    if (registers[args[2]] != 0) {
        updateReg(args[0], (uint32_t) registers[args[1]] % (uint32_t) registers[args[2]]);
    } else {
        updateReg(args[0], 0);
    }
    PC += 4;
}
}
#endif //SE_COMP_ARCH24_CACHE_ISA_NICRONN__INSTRUCTIONS_H_
