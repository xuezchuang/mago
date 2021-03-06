/*
   Copyright (c) 2014 Aldo J. Nunez

   Licensed under the Apache License, Version 2.0.
   See the LICENSE text file for details.
*/

#pragma once

#include "ArchData.h"


namespace Mago
{
    enum ProcFeaturesX86;


    class ArchDataX64 : public ArchData
    {
        ProcFeaturesX86 mProcFeatures;

    public:
        ArchDataX64();
        ArchDataX64( UINT64 procFeatures );

        virtual HRESULT BeginWalkStack( 
            IRegisterSet* topRegSet, 
            void* processContext,
            ReadProcessMemory64Proc readMemProc,
            FunctionTableAccess64Proc funcTabProc,
            GetModuleBase64Proc getModBaseProc,
            StackWalker*& stackWalker );

        virtual HRESULT BuildRegisterSet( 
            const void* threadContext,
            uint32_t threadContextSize,
            IRegisterSet*& regSet );
        virtual HRESULT BuildTinyRegisterSet( 
            const void* threadContext,
            uint32_t threadContextSize,
            IRegisterSet*& regSet );

        virtual uint32_t GetRegisterGroupCount();
        virtual bool GetRegisterGroup( uint32_t index, RegGroup& group );
        virtual int GetArchRegId( int debugRegId );
        virtual int GetPointerSize();
        virtual void GetThreadContextSpec( ArchThreadContextSpec& spec );
        virtual int GetPDataSize();
        virtual void GetPDataRange( 
            Address64 imageBase, 
            const void* pdata, 
            Address64& begin, 
            Address64& end );
    };


    // See MagoDECommon.h for ProcFeaturesX86

    // Unique register IDs based on debug register IDs.
    enum RegX64
    {
        RegX64_NONE,
        RegX64_AL,
        RegX64_CL,
        RegX64_DL,
        RegX64_BL,
        RegX64_AH,
        RegX64_CH,
        RegX64_DH,
        RegX64_BH,
        RegX64_AX,
        RegX64_CX,
        RegX64_DX,
        RegX64_BX,
        RegX64_SP,
        RegX64_BP,
        RegX64_SI,
        RegX64_DI,
        RegX64_EAX,
        RegX64_ECX,
        RegX64_EDX,
        RegX64_EBX,
        RegX64_ESP,
        RegX64_EBP,
        RegX64_ESI,
        RegX64_EDI,
        RegX64_ES,
        RegX64_CS,
        RegX64_SS,
        RegX64_DS,
        RegX64_FS,
        RegX64_GS,
        RegX64_FLAGS,
        RegX64_RIP,
        RegX64_EFLAGS,

        // Leave out Control registers CR0 .. CR8

        // Leave out Debug registers DR0 .. DR15

        // Leave out GDTR, GDTL, IDTR, IDTL, LDTR, TR

        RegX64_ST0,
        RegX64_ST1,
        RegX64_ST2,
        RegX64_ST3,
        RegX64_ST4,
        RegX64_ST5,
        RegX64_ST6,
        RegX64_ST7,
        RegX64_CTRL,
        RegX64_STAT,
        RegX64_TAG,
        RegX64_FPIP,
        RegX64_FPCS,
        RegX64_FPDO,
        RegX64_FPDS,
        // Leave out ISEM
        RegX64_FPEIP,
        RegX64_FPEDO,

        RegX64_MM0,
        RegX64_MM1,
        RegX64_MM2,
        RegX64_MM3,
        RegX64_MM4,
        RegX64_MM5,
        RegX64_MM6,
        RegX64_MM7,

        RegX64_XMM0,   // KATMAI registers
        RegX64_XMM1,
        RegX64_XMM2,
        RegX64_XMM3,
        RegX64_XMM4,
        RegX64_XMM5,
        RegX64_XMM6,
        RegX64_XMM7,

        RegX64_XMM0_0,   // KATMAI sub-registers
        RegX64_XMM0_1,
        RegX64_XMM0_2,
        RegX64_XMM0_3,
        RegX64_XMM1_0,
        RegX64_XMM1_1,
        RegX64_XMM1_2,
        RegX64_XMM1_3,
        RegX64_XMM2_0,
        RegX64_XMM2_1,
        RegX64_XMM2_2,
        RegX64_XMM2_3,
        RegX64_XMM3_0,
        RegX64_XMM3_1,
        RegX64_XMM3_2,
        RegX64_XMM3_3,
        RegX64_XMM4_0,
        RegX64_XMM4_1,
        RegX64_XMM4_2,
        RegX64_XMM4_3,
        RegX64_XMM5_0,
        RegX64_XMM5_1,
        RegX64_XMM5_2,
        RegX64_XMM5_3,
        RegX64_XMM6_0,
        RegX64_XMM6_1,
        RegX64_XMM6_2,
        RegX64_XMM6_3,
        RegX64_XMM7_0,
        RegX64_XMM7_1,
        RegX64_XMM7_2,
        RegX64_XMM7_3,

        RegX64_XMM0L,
        RegX64_XMM1L,
        RegX64_XMM2L,
        RegX64_XMM3L,
        RegX64_XMM4L,
        RegX64_XMM5L,
        RegX64_XMM6L,
        RegX64_XMM7L,

        RegX64_XMM0H,
        RegX64_XMM1H,
        RegX64_XMM2H,
        RegX64_XMM3H,
        RegX64_XMM4H,
        RegX64_XMM5H,
        RegX64_XMM6H,
        RegX64_XMM7H,

        RegX64_MXCSR,   // XMM status register

        RegX64_EMM0L,   // XMM sub-registers (WNI integer)
        RegX64_EMM1L,
        RegX64_EMM2L,
        RegX64_EMM3L,
        RegX64_EMM4L,
        RegX64_EMM5L,
        RegX64_EMM6L,
        RegX64_EMM7L,

        RegX64_EMM0H,
        RegX64_EMM1H,
        RegX64_EMM2H,
        RegX64_EMM3H,
        RegX64_EMM4H,
        RegX64_EMM5H,
        RegX64_EMM6H,
        RegX64_EMM7H,

        // do not change the order of these regs, first one must be even too
        RegX64_MM00,
        RegX64_MM01,
        RegX64_MM10,
        RegX64_MM11,
        RegX64_MM20,
        RegX64_MM21,
        RegX64_MM30,
        RegX64_MM31,
        RegX64_MM40,
        RegX64_MM41,
        RegX64_MM50,
        RegX64_MM51,
        RegX64_MM60,
        RegX64_MM61,
        RegX64_MM70,
        RegX64_MM71,

        // Extended KATMAI registers
        RegX64_XMM8,   // KATMAI registers
        RegX64_XMM9,
        RegX64_XMM10,
        RegX64_XMM11,
        RegX64_XMM12,
        RegX64_XMM13,
        RegX64_XMM14,
        RegX64_XMM15,

        RegX64_XMM8_0,   // KATMAI sub-registers
        RegX64_XMM8_1,
        RegX64_XMM8_2,
        RegX64_XMM8_3,
        RegX64_XMM9_0,
        RegX64_XMM9_1,
        RegX64_XMM9_2,
        RegX64_XMM9_3,
        RegX64_XMM10_0,
        RegX64_XMM10_1,
        RegX64_XMM10_2,
        RegX64_XMM10_3,
        RegX64_XMM11_0,
        RegX64_XMM11_1,
        RegX64_XMM11_2,
        RegX64_XMM11_3,
        RegX64_XMM12_0,
        RegX64_XMM12_1,
        RegX64_XMM12_2,
        RegX64_XMM12_3,
        RegX64_XMM13_0,
        RegX64_XMM13_1,
        RegX64_XMM13_2,
        RegX64_XMM13_3,
        RegX64_XMM14_0,
        RegX64_XMM14_1,
        RegX64_XMM14_2,
        RegX64_XMM14_3,
        RegX64_XMM15_0,
        RegX64_XMM15_1,
        RegX64_XMM15_2,
        RegX64_XMM15_3,

        RegX64_XMM8L,
        RegX64_XMM9L,
        RegX64_XMM10L,
        RegX64_XMM11L,
        RegX64_XMM12L,
        RegX64_XMM13L,
        RegX64_XMM14L,
        RegX64_XMM15L,

        RegX64_XMM8H,
        RegX64_XMM9H,
        RegX64_XMM10H,
        RegX64_XMM11H,
        RegX64_XMM12H,
        RegX64_XMM13H,
        RegX64_XMM14H,
        RegX64_XMM15H,

        RegX64_EMM8L,   // XMM sub-registers (WNI integer)
        RegX64_EMM9L,
        RegX64_EMM10L,
        RegX64_EMM11L,
        RegX64_EMM12L,
        RegX64_EMM13L,
        RegX64_EMM14L,
        RegX64_EMM15L,

        RegX64_EMM8H,
        RegX64_EMM9H,
        RegX64_EMM10H,
        RegX64_EMM11H,
        RegX64_EMM12H,
        RegX64_EMM13H,
        RegX64_EMM14H,
        RegX64_EMM15H,

        // Low byte forms of some standard registers
        RegX64_SIL,
        RegX64_DIL,
        RegX64_BPL,
        RegX64_SPL,

        // 64-bit regular registers
        RegX64_RAX,
        RegX64_RBX,
        RegX64_RCX,
        RegX64_RDX,
        RegX64_RSI,
        RegX64_RDI,
        RegX64_RBP,
        RegX64_RSP,

        // 64-bit integer registers with 8-, 16-, and 32-bit forms (B, W, and D)
        RegX64_R8,
        RegX64_R9,
        RegX64_R10,
        RegX64_R11,
        RegX64_R12,
        RegX64_R13,
        RegX64_R14,
        RegX64_R15,

        RegX64_R8B,
        RegX64_R9B,
        RegX64_R10B,
        RegX64_R11B,
        RegX64_R12B,
        RegX64_R13B,
        RegX64_R14B,
        RegX64_R15B,

        RegX64_R8W,
        RegX64_R9W,
        RegX64_R10W,
        RegX64_R11W,
        RegX64_R12W,
        RegX64_R13W,
        RegX64_R14W,
        RegX64_R15W,

        RegX64_R8D,
        RegX64_R9D,
        RegX64_R10D,
        RegX64_R11D,
        RegX64_R12D,
        RegX64_R13D,
        RegX64_R14D,
        RegX64_R15D,

        // AVX registers 256 bits
        RegX64_YMM0,
        RegX64_YMM1,
        RegX64_YMM2,
        RegX64_YMM3,
        RegX64_YMM4,
        RegX64_YMM5,
        RegX64_YMM6,
        RegX64_YMM7,
        RegX64_YMM8, 
        RegX64_YMM9,
        RegX64_YMM10,
        RegX64_YMM11,
        RegX64_YMM12,
        RegX64_YMM13,
        RegX64_YMM14,
        RegX64_YMM15,

        // AVX registers upper 128 bits
        RegX64_YMM0H,
        RegX64_YMM1H,
        RegX64_YMM2H,
        RegX64_YMM3H,
        RegX64_YMM4H,
        RegX64_YMM5H,
        RegX64_YMM6H,
        RegX64_YMM7H,
        RegX64_YMM8H, 
        RegX64_YMM9H,
        RegX64_YMM10H,
        RegX64_YMM11H,
        RegX64_YMM12H,
        RegX64_YMM13H,
        RegX64_YMM14H,
        RegX64_YMM15H,

        //Lower/upper 8 bytes of XMM registers.  Unlike RegX64_XMM<regnum><H/L>, these
        //values reprsesent the bit patterns of the registers as 64-bit integers, not
        //the representation of these registers as a double.
        RegX64_XMM0IL,
        RegX64_XMM1IL,
        RegX64_XMM2IL,
        RegX64_XMM3IL,
        RegX64_XMM4IL,
        RegX64_XMM5IL,
        RegX64_XMM6IL,
        RegX64_XMM7IL,
        RegX64_XMM8IL,
        RegX64_XMM9IL,
        RegX64_XMM10IL,
        RegX64_XMM11IL,
        RegX64_XMM12IL,
        RegX64_XMM13IL,
        RegX64_XMM14IL,
        RegX64_XMM15IL,

        RegX64_XMM0IH,
        RegX64_XMM1IH,
        RegX64_XMM2IH,
        RegX64_XMM3IH,
        RegX64_XMM4IH,
        RegX64_XMM5IH,
        RegX64_XMM6IH,
        RegX64_XMM7IH,
        RegX64_XMM8IH,
        RegX64_XMM9IH,
        RegX64_XMM10IH,
        RegX64_XMM11IH,
        RegX64_XMM12IH,
        RegX64_XMM13IH,
        RegX64_XMM14IH,
        RegX64_XMM15IH,

        RegX64_YMM0I0,        // AVX integer registers
        RegX64_YMM0I1,
        RegX64_YMM0I2,
        RegX64_YMM0I3,
        RegX64_YMM1I0,
        RegX64_YMM1I1,
        RegX64_YMM1I2,
        RegX64_YMM1I3,
        RegX64_YMM2I0,
        RegX64_YMM2I1,
        RegX64_YMM2I2,
        RegX64_YMM2I3,
        RegX64_YMM3I0,
        RegX64_YMM3I1,
        RegX64_YMM3I2,
        RegX64_YMM3I3,
        RegX64_YMM4I0,
        RegX64_YMM4I1,
        RegX64_YMM4I2,
        RegX64_YMM4I3,
        RegX64_YMM5I0,
        RegX64_YMM5I1,
        RegX64_YMM5I2,
        RegX64_YMM5I3,
        RegX64_YMM6I0,
        RegX64_YMM6I1,
        RegX64_YMM6I2,
        RegX64_YMM6I3,
        RegX64_YMM7I0,
        RegX64_YMM7I1,
        RegX64_YMM7I2,
        RegX64_YMM7I3,
        RegX64_YMM8I0,
        RegX64_YMM8I1,
        RegX64_YMM8I2,
        RegX64_YMM8I3,
        RegX64_YMM9I0,
        RegX64_YMM9I1,
        RegX64_YMM9I2,
        RegX64_YMM9I3,
        RegX64_YMM10I0,
        RegX64_YMM10I1,
        RegX64_YMM10I2,
        RegX64_YMM10I3,
        RegX64_YMM11I0,
        RegX64_YMM11I1,
        RegX64_YMM11I2,
        RegX64_YMM11I3,
        RegX64_YMM12I0,
        RegX64_YMM12I1,
        RegX64_YMM12I2,
        RegX64_YMM12I3,
        RegX64_YMM13I0,
        RegX64_YMM13I1,
        RegX64_YMM13I2,
        RegX64_YMM13I3,
        RegX64_YMM14I0,
        RegX64_YMM14I1,
        RegX64_YMM14I2,
        RegX64_YMM14I3,
        RegX64_YMM15I0,
        RegX64_YMM15I1,
        RegX64_YMM15I2,
        RegX64_YMM15I3,

        RegX64_YMM0F0,        // AVX floating-point single precise registers
        RegX64_YMM0F1,
        RegX64_YMM0F2,
        RegX64_YMM0F3,
        RegX64_YMM0F4,
        RegX64_YMM0F5,
        RegX64_YMM0F6,
        RegX64_YMM0F7,
        RegX64_YMM1F0,
        RegX64_YMM1F1,
        RegX64_YMM1F2,
        RegX64_YMM1F3,
        RegX64_YMM1F4,
        RegX64_YMM1F5,
        RegX64_YMM1F6,
        RegX64_YMM1F7,
        RegX64_YMM2F0,
        RegX64_YMM2F1,
        RegX64_YMM2F2,
        RegX64_YMM2F3,
        RegX64_YMM2F4,
        RegX64_YMM2F5,
        RegX64_YMM2F6,
        RegX64_YMM2F7,
        RegX64_YMM3F0,
        RegX64_YMM3F1,
        RegX64_YMM3F2,
        RegX64_YMM3F3,
        RegX64_YMM3F4,
        RegX64_YMM3F5,
        RegX64_YMM3F6,
        RegX64_YMM3F7,
        RegX64_YMM4F0,
        RegX64_YMM4F1,
        RegX64_YMM4F2,
        RegX64_YMM4F3,
        RegX64_YMM4F4,
        RegX64_YMM4F5,
        RegX64_YMM4F6,
        RegX64_YMM4F7,
        RegX64_YMM5F0,
        RegX64_YMM5F1,
        RegX64_YMM5F2,
        RegX64_YMM5F3,
        RegX64_YMM5F4,
        RegX64_YMM5F5,
        RegX64_YMM5F6,
        RegX64_YMM5F7,
        RegX64_YMM6F0,
        RegX64_YMM6F1,
        RegX64_YMM6F2,
        RegX64_YMM6F3,
        RegX64_YMM6F4,
        RegX64_YMM6F5,
        RegX64_YMM6F6,
        RegX64_YMM6F7,
        RegX64_YMM7F0,
        RegX64_YMM7F1,
        RegX64_YMM7F2,
        RegX64_YMM7F3,
        RegX64_YMM7F4,
        RegX64_YMM7F5,
        RegX64_YMM7F6,
        RegX64_YMM7F7,
        RegX64_YMM8F0,
        RegX64_YMM8F1,
        RegX64_YMM8F2,
        RegX64_YMM8F3,
        RegX64_YMM8F4,
        RegX64_YMM8F5,
        RegX64_YMM8F6,
        RegX64_YMM8F7,
        RegX64_YMM9F0,
        RegX64_YMM9F1,
        RegX64_YMM9F2,
        RegX64_YMM9F3,
        RegX64_YMM9F4,
        RegX64_YMM9F5,
        RegX64_YMM9F6,
        RegX64_YMM9F7,
        RegX64_YMM10F0,
        RegX64_YMM10F1,
        RegX64_YMM10F2,
        RegX64_YMM10F3,
        RegX64_YMM10F4,
        RegX64_YMM10F5,
        RegX64_YMM10F6,
        RegX64_YMM10F7,
        RegX64_YMM11F0,
        RegX64_YMM11F1,
        RegX64_YMM11F2,
        RegX64_YMM11F3,
        RegX64_YMM11F4,
        RegX64_YMM11F5,
        RegX64_YMM11F6,
        RegX64_YMM11F7,
        RegX64_YMM12F0,
        RegX64_YMM12F1,
        RegX64_YMM12F2,
        RegX64_YMM12F3,
        RegX64_YMM12F4,
        RegX64_YMM12F5,
        RegX64_YMM12F6,
        RegX64_YMM12F7,
        RegX64_YMM13F0,
        RegX64_YMM13F1,
        RegX64_YMM13F2,
        RegX64_YMM13F3,
        RegX64_YMM13F4,
        RegX64_YMM13F5,
        RegX64_YMM13F6,
        RegX64_YMM13F7,
        RegX64_YMM14F0,
        RegX64_YMM14F1,
        RegX64_YMM14F2,
        RegX64_YMM14F3,
        RegX64_YMM14F4,
        RegX64_YMM14F5,
        RegX64_YMM14F6,
        RegX64_YMM14F7,
        RegX64_YMM15F0,
        RegX64_YMM15F1,
        RegX64_YMM15F2,
        RegX64_YMM15F3,
        RegX64_YMM15F4,
        RegX64_YMM15F5,
        RegX64_YMM15F6,
        RegX64_YMM15F7,
    
        RegX64_YMM0D0,        // AVX floating-point double precise registers
        RegX64_YMM0D1,
        RegX64_YMM0D2,
        RegX64_YMM0D3,
        RegX64_YMM1D0,
        RegX64_YMM1D1,
        RegX64_YMM1D2,
        RegX64_YMM1D3,
        RegX64_YMM2D0,
        RegX64_YMM2D1,
        RegX64_YMM2D2,
        RegX64_YMM2D3,
        RegX64_YMM3D0,
        RegX64_YMM3D1,
        RegX64_YMM3D2,
        RegX64_YMM3D3,
        RegX64_YMM4D0,
        RegX64_YMM4D1,
        RegX64_YMM4D2,
        RegX64_YMM4D3,
        RegX64_YMM5D0,
        RegX64_YMM5D1,
        RegX64_YMM5D2,
        RegX64_YMM5D3,
        RegX64_YMM6D0,
        RegX64_YMM6D1,
        RegX64_YMM6D2,
        RegX64_YMM6D3,
        RegX64_YMM7D0,
        RegX64_YMM7D1,
        RegX64_YMM7D2,
        RegX64_YMM7D3,
        RegX64_YMM8D0,
        RegX64_YMM8D1,
        RegX64_YMM8D2,
        RegX64_YMM8D3,
        RegX64_YMM9D0,
        RegX64_YMM9D1,
        RegX64_YMM9D2,
        RegX64_YMM9D3,
        RegX64_YMM10D0,
        RegX64_YMM10D1,
        RegX64_YMM10D2,
        RegX64_YMM10D3,
        RegX64_YMM11D0,
        RegX64_YMM11D1,
        RegX64_YMM11D2,
        RegX64_YMM11D3,
        RegX64_YMM12D0,
        RegX64_YMM12D1,
        RegX64_YMM12D2,
        RegX64_YMM12D3,
        RegX64_YMM13D0,
        RegX64_YMM13D1,
        RegX64_YMM13D2,
        RegX64_YMM13D3,
        RegX64_YMM14D0,
        RegX64_YMM14D1,
        RegX64_YMM14D2,
        RegX64_YMM14D3,
        RegX64_YMM15D0,
        RegX64_YMM15D1,
        RegX64_YMM15D2,
        RegX64_YMM15D3,

        RegX64_Max,
    };
}
