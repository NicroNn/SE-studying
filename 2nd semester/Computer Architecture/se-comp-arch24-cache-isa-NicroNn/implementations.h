#ifndef SE_COMP_ARCH24_CACHE_ISA_NICRONN__IMPLEMENTATIONS_H_
#define SE_COMP_ARCH24_CACHE_ISA_NICRONN__IMPLEMENTATIONS_H_
#include "instructions.h"
#include <unordered_set>

void instructionCaller(const std::vector<std::pair<std::string, std::vector<std::string>>>& instructions) {
    registers["ra"] = 705969807;
    while (PC / 4 <= instructions.size()) {
        auto inst = instructions[PC / 4].first;
        std::vector<std::string> args = instructions[PC / 4].second;
        if (inst == "lui") {
            RV32I::lui(args);
            continue;
        }
        if (inst == "auipc") {
            RV32I::auipc(args);
            continue;
        }
        if (inst == "addi") {
            RV32I::addi(args);
            continue;
        }
        if (inst == "slti") {
            RV32I::slti(args);
            continue;
        }
        if (inst == "sltiu") {
            RV32I::sltiu(args);
            continue;
        }
        if (inst == "xori") {
            RV32I::xori(args);
            continue;
        }
        if (inst == "ori") {
            RV32I::ori(args);
            continue;
        }
        if (inst == "andi") {
            RV32I::andi(args);
            continue;
        }
        if (inst == "slli") {
            RV32I::slli(args);
            continue;
        }
        if (inst == "srli") {
            RV32I::srli(args);
            continue;
        }
        if (inst == "srai") {
            RV32I::srai(args);
            continue;
        }
        if (inst == "add") {
            RV32I::add(args);
            continue;
        }
        if (inst == "sub") {
            RV32I::sub(args);
            continue;
        }
        if (inst == "sll") {
            RV32I::sll(args);
            continue;
        }
        if (inst == "slt") {
            RV32I::slt(args);
            continue;
        }
        if (inst == "sltu") {
            RV32I::sltu(args);
            continue;
        }
        if (inst == "Xor") {
            RV32I::Xor(args);
            continue;
        }
        if (inst == "srl") {
            RV32I::srl(args);
            continue;
        }
        if (inst == "sra") {
            RV32I::sra(args);
            continue;
        }
        if (inst == "Or") {
            RV32I::Or(args);
            continue;
        }
        if (inst == "And") {
            RV32I::And(args);
            continue;
        }
        if (inst == "fence") {
            RV32I::fence(args);
            continue;
        }
        if (inst == "fence_i") {
            RV32I::fence_i(args);
            continue;
        }
        if (inst == "csrrw") {
            RV32I::csrrw(args);
            continue;
        }
        if (inst == "csrrs") {
            RV32I::csrrs(args);
            continue;
        }
        if (inst == "csrrc") {
            RV32I::csrrc(args);
            continue;
        }
        if (inst == "csrrwi") {
            RV32I::csrrwi(args);
            continue;
        }
        if (inst == "csrrsi") {
            RV32I::csrrsi(args);
            continue;
        }
        if (inst == "csrrci") {
            RV32I::csrrci(args);
            continue;
        }
        if (inst == "ecall") {
            RV32I::ecall(args);
            continue;
        }
        if (inst == "ebreak") {
            RV32I::ebreak(args);
            continue;
        }
        if (inst == "uret") {
            RV32I::uret(args);
            continue;
        }
        if (inst == "sret") {
            RV32I::sret(args);
            continue;
        }
        if (inst == "mret") {
            RV32I::mret(args);
            continue;
        }
        if (inst == "wfi") {
            RV32I::wfi(args);
            continue;
        }
        if (inst == "sfence_vma") {
            RV32I::sfence_vma(args);
            continue;
        }
        if (inst == "lb") {
            RV32I::lb(args);
            continue;
        }
        if (inst == "lh") {
            RV32I::lh(args);
            continue;
        }
        if (inst == "lw") {
            RV32I::lw(args);
            continue;
        }
        if (inst == "lbu") {
            RV32I::lbu(args);
            continue;
        }
        if (inst == "lhu") {
            RV32I::lhu(args);
            continue;
        }
        if (inst == "sb") {
            RV32I::sb(args);
            continue;
        }
        if (inst == "sh") {
            RV32I::sh(args);
            continue;
        }
        if (inst == "sw") {
            RV32I::sw(args);
            continue;
        }
        if (inst == "jal") {
            RV32I::jal(args);
            continue;
        }
        if (inst == "jalr") {
            RV32I::jalr(args);
            continue;
        }
        if (inst == "beq") {
            RV32I::beq(args);
            continue;
        }
        if (inst == "bne") {
            RV32I::bne(args);
            continue;
        }
        if (inst == "blt") {
            RV32I::blt(args);
            continue;
        }
        if (inst == "bge") {
            RV32I::bge(args);
            continue;
        }
        if (inst == "bltu") {
            RV32I::bltu(args);
            continue;
        }
        if (inst == "bgeu") {
            RV32I::bgeu(args);
            continue;
        }

        if (inst == "mul") {
            RV32M::mul(args);
            continue;
        }
        if (inst == "mulh") {
            RV32M::mulh(args);
            continue;
        }
        if (inst == "mulhsu") {
            RV32M::mulhsu(args);
            continue;
        }
        if (inst == "mulhu") {
            RV32M::mulhu(args);
            continue;
        }
        if (inst == "div") {
            RV32M::div(args);
            continue;
        }
        if (inst == "divu") {
            RV32M::divu(args);
            continue;
        }
        if (inst == "rem") {
            RV32M::rem(args);
            continue;
        }
        if (inst == "remu") {
            RV32M::remu(args);
            continue;
        }
    }
}

std::unordered_map<std::string, uint8_t> opcode_map = {
        {"lui", 0b0110111}, {"auipc", 0b0010111}, {"jal", 0b1101111}, {"jalr", 0b1100111},
        {"beq", 0b1100011}, {"bne", 0b1100011}, {"blt", 0b1100011}, {"bge", 0b1100011},
        {"bltu", 0b1100011}, {"bgeu", 0b1100011}, {"lb", 0b0000011}, {"lh", 0b0000011},
        {"lw", 0b0000011}, {"lbu", 0b0000011}, {"lhu", 0b0000011}, {"sb", 0b0100011},
        {"sh", 0b0100011}, {"sw", 0b0100011}, {"addi", 0b0010011}, {"slti", 0b0010011},
        {"sltiu", 0b0010011}, {"xori", 0b0010011}, {"ori", 0b0010011}, {"andi", 0b0010011},
        {"slli", 0b0010011}, {"srli", 0b0010011}, {"srai", 0b0010011}, {"add", 0b0110011},
        {"sub", 0b0110011}, {"sll", 0b0110011}, {"slt", 0b0110011}, {"sltu", 0b0110011},
        {"xor", 0b0110011}, {"srl", 0b0110011}, {"sra", 0b0110011}, {"or", 0b0110011},
        {"and", 0b0110011}, {"mul", 0b0110011}, {"mulh", 0b0110011}, {"mulhsu", 0b0110011},
        {"mulhu", 0b0110011}, {"div", 0b0110011}, {"divu", 0b0110011}, {"rem", 0b0110011},
        {"remu", 0b0110011}
};

std::unordered_map<std::string, uint8_t> funct3_map = {
        {"beq", 0b000}, {"bne", 0b001}, {"blt", 0b100}, {"bge", 0b101},
        {"bltu", 0b110}, {"bgeu", 0b111}, {"lb", 0b000}, {"lh", 0b001},
        {"lw", 0b010}, {"lbu", 0b100}, {"lhu", 0b101}, {"sb", 0b000},
        {"sh", 0b001}, {"sw", 0b010}, {"addi", 0b000}, {"slti", 0b010},
        {"sltiu", 0b011}, {"xori", 0b100}, {"ori", 0b110}, {"andi", 0b111},
        {"slli", 0b001}, {"srli", 0b101}, {"srai", 0b101}, {"add", 0b000},
        {"sub", 0b000}, {"sll", 0b001}, {"slt", 0b010}, {"sltu", 0b011},
        {"xor", 0b100}, {"srl", 0b101}, {"sra", 0b101}, {"or", 0b110},
        {"and", 0b111}, {"mul", 0b000}, {"mulh", 0b001}, {"mulhsu", 0b010},
        {"mulhu", 0b011}, {"div", 0b100}, {"divu", 0b101}, {"rem", 0b110},
        {"remu", 0b111}
};

std::unordered_map<std::string, uint8_t> funct7_map = {
        {"add", 0b0000000}, {"sub", 0b0100000}, {"sll", 0b0000000}, {"slt", 0b0000000},
        {"sltu", 0b0000000}, {"xor", 0b0000000}, {"srl", 0b0000000}, {"sra", 0b0100000},
        {"or", 0b0000000}, {"and", 0b0000000}, {"mul", 0b0000001}, {"mulh", 0b0000001},
        {"mulhsu", 0b0000001}, {"mulhu", 0b0000001}, {"div", 0b0000001}, {"divu", 0b0000001},
        {"rem", 0b0000001}, {"remu", 0b0000001}
};

std::unordered_set<std::string> r_type_instructions = {
        "add", "sub", "sll", "slt", "sltu", "xor", "srl", "sra", "or", "and",
        "mul", "mulh", "mulhsu", "mulhu", "div", "divu", "rem", "remu"
};

std::unordered_set<std::string> i_type_instructions = {
        "addi", "slti", "sltiu", "xori", "ori", "andi", "slli", "srli", "srai",
        "jalr", "lb", "lh", "lw", "lbu", "lhu"
};

std::unordered_set<std::string> s_type_instructions = {"sb", "sh", "sw"};
std::unordered_set<std::string> b_type_instructions = {"beq", "bne", "blt", "bge", "bltu", "bgeu"};
std::unordered_set<std::string> u_type_instructions = {"lui", "auipc"};
std::unordered_set<std::string> j_type_instructions = {"jal"};

uint32_t encode_r_type(const std::string& instr, const std::vector<std::string>& args) {
    uint32_t rd = registers[args[0]];
    uint32_t rs1 = registers[args[1]];
    uint32_t rs2 = registers[args[2]];
    uint32_t funct3 = funct3_map[instr];
    uint32_t funct7 = funct7_map[instr];
    uint32_t opcode = opcode_map[instr];
    return (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
}

uint32_t encode_i_type(const std::string& instr, const std::vector<std::string>& args) {
    uint32_t rd = registers[args[0]];
    uint32_t rs1 = registers[args[1]];
    uint32_t imm = std::stoi(args[2]);
    imm &= 0xFFF;
    uint32_t funct3 = funct3_map[instr];
    uint32_t opcode = opcode_map[instr];
    return (imm << 20) | ((rs1 - imm) << 15) | (funct3 << 12) | ((rd - imm) << 7) | opcode;
}

uint32_t encode_s_type(const std::string& instr, const std::vector<std::string>& args) {
    uint32_t rs2 = registers[args[0]];
    uint32_t rs1 = registers[args[1]];
    int32_t imm = std::stoi(args[2]);
    uint32_t funct3 = funct3_map[instr];
    uint32_t opcode = opcode_map[instr];
    return ((imm & 0xFE0) << 20) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | ((imm & 0x1F) << 7) | opcode;
}

uint32_t encode_b_type(const std::string& instr, const std::vector<std::string>& args) {
    uint32_t rs1 = registers[args[0]];
    uint32_t rs2 = registers[args[1]];
    int32_t imm = std::stoi(args[2]);
    uint32_t funct3 = funct3_map[instr];
    uint32_t opcode = opcode_map[instr];
    return ((imm & 0x1000) << 19) | ((imm & 0x7E0) << 20) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12)
           | ((imm & 0x1E) << 7) | ((imm & 0x800) >> 4) | opcode;
}

uint32_t encode_u_type(const std::string& instr, const std::vector<std::string>& args) {
    uint32_t rd = registers[args[0]];
    int32_t imm = std::stoi(args[1]);
    uint32_t opcode = opcode_map[instr];
    return (imm & 0xFFFFF000) | (rd << 7) | opcode;
}

uint32_t encode_j_type(const std::string& instr, const std::vector<std::string>& args) {
    uint32_t rd = registers[args[0]];
    int32_t imm = std::stoi(args[1]);
    uint32_t opcode = opcode_map[instr];
    return ((imm & 0x100000) << 11) | ((imm & 0x7FE) << 20) | ((imm & 0x800) << 9) | ((imm & 0xFF000) >> 11) | (rd << 7)
           | opcode;
}

uint32_t encode_instruction(const std::string& instr, const std::vector<std::string>& args) {
    if (r_type_instructions.contains(instr)) {
        return encode_r_type(instr, args);
    }
    if (i_type_instructions.contains(instr)) {
        return encode_i_type(instr, args);
    }
    if (s_type_instructions.contains(instr)) {
        return encode_s_type(instr, args);
    }
    if (b_type_instructions.contains(instr)) {
        return encode_b_type(instr, args);
    }
    if (u_type_instructions.contains(instr)) {
        return encode_u_type(instr, args);
    }
    if (j_type_instructions.contains(instr)) {
        return encode_j_type(instr, args);
    }
    throw std::invalid_argument("Unsupported instruction type");
}

void translate_to_binary(const std::vector<std::pair<std::string, std::vector<std::string>>>& instructions, const std::string& output_file) {
    std::ofstream out(output_file, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Unable to open output file");
    }

    for (const auto& instr : instructions) {
        uint32_t binary_instr = encode_instruction(instr.first, instr.second);
        out.write(reinterpret_cast<const char*>(&binary_instr), sizeof(binary_instr));
    }

    out.close();
}

#endif //SE_COMP_ARCH24_CACHE_ISA_NICRONN__IMPLEMENTATIONS_H_
