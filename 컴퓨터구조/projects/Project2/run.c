/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   SCE212 Ajou University                                    */
/*   run.c                                                     */
/*   Adapted from CS311@KAIST                                  */
/*                                                             */
/***************************************************************/

#include <stdio.h>

#include "util.h"
#include "run.h"

int text_size;

/***************************************************************/
/*                                                             */
/* Procedure: get_inst_info                                    */
/*                                                             */
/* Purpose: Read insturction information                       */
/*                                                             */
/***************************************************************/
instruction* get_inst_info(uint32_t pc)
{
    return &INST_INFO[(pc - MEM_TEXT_START) >> 2];
}

/***************************************************************/
/*                                                             */
/* Procedure: process_instruction                              */
/*                                                             */
/* Purpose: Process one instrction                             */
/*                                                             */
/***************************************************************/
void process_instruction()
{
    instruction *instr = get_inst_info(CURRENT_STATE.PC);
    int rd = CURRENT_STATE.REGS[instr[0].r_t.r_i.r_i.r.rd];
    int rs = CURRENT_STATE.REGS[instr[0].r_t.r_i.rs];
    int rt = CURRENT_STATE.REGS[instr[0].r_t.r_i.rt];
    int imm = instr[0].r_t.r_i.r_i.imm;

    CURRENT_STATE.PC += 4;

    switch(instr[0].opcode)
    {
        //TYPE R
        case 0x0:		////(0x000000)
            switch(instr[0].func_code)
            {
                case 0x21:		//ADDU
                    CURRENT_STATE.REGS[instr[0].r_t.r_i.r_i.r.rd] = rs + (unsigned int)rt;
                    break;
                case 0x24:		//AND
                    CURRENT_STATE.REGS[instr[0].r_t.r_i.r_i.r.rd] = rs & rt;
                    break;
                case 0x27:		//NOR
                    CURRENT_STATE.REGS[instr[0].r_t.r_i.r_i.r.rd] = ~(rs | rt);
                    break;
                case 0x25:		//OR
                    CURRENT_STATE.REGS[instr[0].r_t.r_i.r_i.r.rd] = rs | rt;
                    break;
                case 0x2A:		//SLT
                    CURRENT_STATE.REGS[instr[0].r_t.r_i.r_i.r.rd] = rs < rt;
                    break;
                case 0x2b:		//SLTU
                    CURRENT_STATE.REGS[instr[0].r_t.r_i.r_i.r.rd] = rs < (unsigned int)rt;
                    break;
                case 0x0:		//SLL
                    CURRENT_STATE.REGS[instr[0].r_t.r_i.r_i.r.rd] = rt << instr[0].r_t.r_i.r_i.r.shamt;
                    break;
                case 0x2:		//SRL
                    CURRENT_STATE.REGS[instr[0].r_t.r_i.r_i.r.rd] = rt >> instr[0].r_t.r_i.r_i.r.shamt;
                    break;
                case 0x22:		//SUB
                    CURRENT_STATE.REGS[instr[0].r_t.r_i.r_i.r.rd] = rs - rt;
                    break;
                case 0x23:		//SUBU
                    CURRENT_STATE.REGS[instr[0].r_t.r_i.r_i.r.rd] = rs - (unsigned int)rt;
                    break;
                case 0x8:       //JR
                    CURRENT_STATE.PC = rs;
            }
            break;

        //TYPE I
        case 0x9:		//(0x001001)ADDIU
            CURRENT_STATE.REGS[instr[0].r_t.r_i.rt] = rs + (unsigned int)imm;
            break;
        case 0xc:		//(0x001100)ANDI
            CURRENT_STATE.REGS[instr[0].r_t.r_i.rt] = rs & imm;
            break;
        case 0xf:		//(0x001111)LUI	
            CURRENT_STATE.REGS[instr[0].r_t.r_i.rt] = imm << 16;
            break;
        case 0xd:		//(0x001101)ORI
            CURRENT_STATE.REGS[instr[0].r_t.r_i.rt] = rs | imm;
            break;
        case 0xb:		//(0x001011)SLTIU
            CURRENT_STATE.REGS[instr[0].r_t.r_i.rt] = rs < (unsigned int)imm;
            break;
        case 0x23:		//(0x100011)LW
            CURRENT_STATE.REGS[instr[0].r_t.r_i.rt] = mem_read_32(rs + imm);
            break;
        case 0x2b:		//(0x101011)SW
            mem_write_32(rs + imm, rt);
            break;
        case 0x4:	    //(0x000100)BEQ
            if (rs == rt)
                CURRENT_STATE.PC += imm * 4;
            break;
        case 0x5:		//(0x000101)BNE
            if (rs != rt)
                CURRENT_STATE.PC += imm * 4;
            break;

        //TYPE J
        case 0x3:		//(0x000011)JAL
            CURRENT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
        case 0x2:		//(0x000010)J
            CURRENT_STATE.PC = instr[0].r_t.target << 2;
    }

    if (CURRENT_STATE.PC >= (MEM_TEXT_START + text_size))
        RUN_BIT = FALSE;
}
