/* Generated automatically by the program `genconstants'
   from the machine description file `md'.  */

#ifndef GCC_INSN_CONSTANTS_H
#define GCC_INSN_CONSTANTS_H

#define LAST_ALTIVEC_REGNO 108
#define VSCR_REGNO 110
#define STATIC_CHAIN_REGNUM 11
#define TSTTFGT_GPR 1015
#define FRAME_POINTER_REGNUM 113
#define TSTTFEQ_GPR 1013
#define CR1_REGNO 69
#define TEXASR_SPR 130
#define STACK_POINTER_REGNUM 1
#define TFHAR_SPR 128
#define TSTDFLT_GPR 1011
#define LAST_FPR_REGNO 63
#define CMPTFLT_GPR 1016
#define LR_REGNO 65
#define TSTDFGT_GPR 1009
#define CTR_REGNO 66
#define CMPTFGT_GPR 1014
#define TSTTFLT_GPR 1017
#define CR3_REGNO 71
#define E500_CR_IOR_COMPARE 1018
#define FIRST_GPR_REGNO 0
#define VRSAVE_REGNO 109
#define FIRST_FPR_REGNO 32
#define CR5_REGNO 73
#define CMPDFEQ_GPR 1006
#define TEXASR_REGNO 116
#define CR7_REGNO 75
#define SPE_ACC_REGNO 111
#define ARG_POINTER_REGNUM 67
#define TFHAR_REGNO 114
#define TFIAR_SPR 129
#define LAST_GPR_REGNO 31
#define CMPDFGT_GPR 1008
#define HARD_FRAME_POINTER_REGNUM 31
#define TOC_REGNUM 2
#define SPEFSCR_REGNO 112
#define CA_REGNO 76
#define TFIAR_REGNO 115
#define FIRST_ALTIVEC_REGNO 77
#define TEXASRU_SPR 131
#define MAX_CR_REGNO 75
#define CMPDFLT_GPR 1010
#define MAX_HTM_OPERANDS 4
#define CR0_REGNO 68
#define CR2_REGNO 70
#define CR4_REGNO 72
#define TSTDFEQ_GPR 1007
#define CMPTFEQ_GPR 1012
#define CR6_REGNO 74

enum unspec {
  UNSPEC_FRSP = 0,
  UNSPEC_PROBE_STACK = 1,
  UNSPEC_TOCPTR = 2,
  UNSPEC_TOC = 3,
  UNSPEC_MOVSI_GOT = 4,
  UNSPEC_MV_CR_OV = 5,
  UNSPEC_FCTIWZ = 6,
  UNSPEC_FRIM = 7,
  UNSPEC_FRIN = 8,
  UNSPEC_FRIP = 9,
  UNSPEC_FRIZ = 10,
  UNSPEC_LD_MPIC = 11,
  UNSPEC_MPIC_CORRECT = 12,
  UNSPEC_TLSGD = 13,
  UNSPEC_TLSLD = 14,
  UNSPEC_MOVESI_FROM_CR = 15,
  UNSPEC_MOVESI_TO_CR = 16,
  UNSPEC_TLSDTPREL = 17,
  UNSPEC_TLSDTPRELHA = 18,
  UNSPEC_TLSDTPRELLO = 19,
  UNSPEC_TLSGOTDTPREL = 20,
  UNSPEC_TLSTPREL = 21,
  UNSPEC_TLSTPRELHA = 22,
  UNSPEC_TLSTPRELLO = 23,
  UNSPEC_TLSGOTTPREL = 24,
  UNSPEC_TLSTLS = 25,
  UNSPEC_FIX_TRUNC_TF = 26,
  UNSPEC_MV_CR_GT = 27,
  UNSPEC_STFIWX = 28,
  UNSPEC_POPCNTB = 29,
  UNSPEC_FRES = 30,
  UNSPEC_SP_SET = 31,
  UNSPEC_SP_TEST = 32,
  UNSPEC_SYNC = 33,
  UNSPEC_LWSYNC = 34,
  UNSPEC_SYNC_OP = 35,
  UNSPEC_ATOMIC = 36,
  UNSPEC_CMPXCHG = 37,
  UNSPEC_XCHG = 38,
  UNSPEC_AND = 39,
  UNSPEC_DLMZB = 40,
  UNSPEC_DLMZB_CR = 41,
  UNSPEC_DLMZB_STRLEN = 42,
  UNSPEC_RSQRT = 43,
  UNSPEC_TOCREL = 44,
  UNSPEC_MACHOPIC_OFFSET = 45,
  UNSPEC_BPERM = 46,
  UNSPEC_COPYSIGN = 47,
  UNSPEC_PARITY = 48,
  UNSPEC_FCTIW = 49,
  UNSPEC_FCTID = 50,
  UNSPEC_LFIWAX = 51,
  UNSPEC_LFIWZX = 52,
  UNSPEC_FCTIWUZ = 53,
  UNSPEC_GRP_END_NOP = 54,
  UNSPEC_P8V_FMRGOW = 55,
  UNSPEC_P8V_MTVSRWZ = 56,
  UNSPEC_P8V_RELOAD_FROM_GPR = 57,
  UNSPEC_P8V_MTVSRD = 58,
  UNSPEC_P8V_XXPERMDI = 59,
  UNSPEC_P8V_RELOAD_FROM_VSX = 60,
  UNSPEC_ADDG6S = 61,
  UNSPEC_CDTBCD = 62,
  UNSPEC_CBCDTD = 63,
  UNSPEC_DIVE = 64,
  UNSPEC_DIVEO = 65,
  UNSPEC_DIVEU = 66,
  UNSPEC_DIVEUO = 67,
  UNSPEC_UNPACK_128BIT = 68,
  UNSPEC_PACK_128BIT = 69,
  UNSPEC_LSQ = 70,
  UNSPEC_FUSION_GPR = 71,
  UNSPEC_PREDICATE = 72,
  UNSPEC_REDUC = 73,
  UNSPEC_VSX_CONCAT = 74,
  UNSPEC_VSX_CVDPSXWS = 75,
  UNSPEC_VSX_CVDPUXWS = 76,
  UNSPEC_VSX_CVSPDP = 77,
  UNSPEC_VSX_CVSPDPN = 78,
  UNSPEC_VSX_CVDPSPN = 79,
  UNSPEC_VSX_CVSXWDP = 80,
  UNSPEC_VSX_CVUXWDP = 81,
  UNSPEC_VSX_CVSXDSP = 82,
  UNSPEC_VSX_CVUXDSP = 83,
  UNSPEC_VSX_CVSPSXDS = 84,
  UNSPEC_VSX_CVSPUXDS = 85,
  UNSPEC_VSX_TDIV = 86,
  UNSPEC_VSX_TSQRT = 87,
  UNSPEC_VSX_SET = 88,
  UNSPEC_VSX_ROUND_I = 89,
  UNSPEC_VSX_ROUND_IC = 90,
  UNSPEC_VSX_SLDWI = 91,
  UNSPEC_VSX_XXSPLTW = 92,
  UNSPEC_VSX_XXSPLTD = 93,
  UNSPEC_VSX_DIVSD = 94,
  UNSPEC_VSX_DIVUD = 95,
  UNSPEC_VSX_MULSD = 96,
  UNSPEC_VSX_XVCVSXDDP = 97,
  UNSPEC_VSX_XVCVUXDDP = 98,
  UNSPEC_VSX_XVCVDPSXDS = 99,
  UNSPEC_VSX_XVCVDPUXDS = 100,
  UNSPEC_VCMPBFP = 101,
  UNSPEC_VMSUMU = 102,
  UNSPEC_VMSUMM = 103,
  UNSPEC_VMSUMSHM = 104,
  UNSPEC_VMSUMUHS = 105,
  UNSPEC_VMSUMSHS = 106,
  UNSPEC_VMHADDSHS = 107,
  UNSPEC_VMHRADDSHS = 108,
  UNSPEC_VMLADDUHM = 109,
  UNSPEC_VADDCUW = 110,
  UNSPEC_VADDU = 111,
  UNSPEC_VADDS = 112,
  UNSPEC_VAVGU = 113,
  UNSPEC_VAVGS = 114,
  UNSPEC_VMULEUB = 115,
  UNSPEC_VMULESB = 116,
  UNSPEC_VMULEUH = 117,
  UNSPEC_VMULESH = 118,
  UNSPEC_VMULOUB = 119,
  UNSPEC_VMULOSB = 120,
  UNSPEC_VMULOUH = 121,
  UNSPEC_VMULOSH = 122,
  UNSPEC_VPKPX = 123,
  UNSPEC_VPACK_SIGN_SIGN_SAT = 124,
  UNSPEC_VPACK_SIGN_UNS_SAT = 125,
  UNSPEC_VPACK_UNS_UNS_SAT = 126,
  UNSPEC_VPACK_UNS_UNS_MOD = 127,
  UNSPEC_VPACK_UNS_UNS_MOD_DIRECT = 128,
  UNSPEC_VSLV4SI = 129,
  UNSPEC_VSLO = 130,
  UNSPEC_VSR = 131,
  UNSPEC_VSRO = 132,
  UNSPEC_VSUBCUW = 133,
  UNSPEC_VSUBU = 134,
  UNSPEC_VSUBS = 135,
  UNSPEC_VSUM4UBS = 136,
  UNSPEC_VSUM4S = 137,
  UNSPEC_VSUM2SWS = 138,
  UNSPEC_VSUMSWS = 139,
  UNSPEC_VPERM = 140,
  UNSPEC_VPERM_UNS = 141,
  UNSPEC_VRFIN = 142,
  UNSPEC_VCFUX = 143,
  UNSPEC_VCFSX = 144,
  UNSPEC_VCTUXS = 145,
  UNSPEC_VCTSXS = 146,
  UNSPEC_VLOGEFP = 147,
  UNSPEC_VEXPTEFP = 148,
  UNSPEC_VSLDOI = 149,
  UNSPEC_VUNPACK_HI_SIGN = 150,
  UNSPEC_VUNPACK_LO_SIGN = 151,
  UNSPEC_VUNPACK_HI_SIGN_DIRECT = 152,
  UNSPEC_VUNPACK_LO_SIGN_DIRECT = 153,
  UNSPEC_VUPKHPX = 154,
  UNSPEC_VUPKLPX = 155,
  UNSPEC_DST = 156,
  UNSPEC_DSTT = 157,
  UNSPEC_DSTST = 158,
  UNSPEC_DSTSTT = 159,
  UNSPEC_LVSL = 160,
  UNSPEC_LVSR = 161,
  UNSPEC_LVE = 162,
  UNSPEC_STVX = 163,
  UNSPEC_STVXL = 164,
  UNSPEC_STVE = 165,
  UNSPEC_SET_VSCR = 166,
  UNSPEC_GET_VRSAVE = 167,
  UNSPEC_LVX = 168,
  UNSPEC_REDUC_PLUS = 169,
  UNSPEC_VECSH = 170,
  UNSPEC_EXTEVEN_V4SI = 171,
  UNSPEC_EXTEVEN_V8HI = 172,
  UNSPEC_EXTEVEN_V16QI = 173,
  UNSPEC_EXTEVEN_V4SF = 174,
  UNSPEC_EXTODD_V4SI = 175,
  UNSPEC_EXTODD_V8HI = 176,
  UNSPEC_EXTODD_V16QI = 177,
  UNSPEC_EXTODD_V4SF = 178,
  UNSPEC_INTERHI_V4SI = 179,
  UNSPEC_INTERHI_V8HI = 180,
  UNSPEC_INTERHI_V16QI = 181,
  UNSPEC_INTERLO_V4SI = 182,
  UNSPEC_INTERLO_V8HI = 183,
  UNSPEC_INTERLO_V16QI = 184,
  UNSPEC_LVLX = 185,
  UNSPEC_LVLXL = 186,
  UNSPEC_LVRX = 187,
  UNSPEC_LVRXL = 188,
  UNSPEC_STVLX = 189,
  UNSPEC_STVLXL = 190,
  UNSPEC_STVRX = 191,
  UNSPEC_STVRXL = 192,
  UNSPEC_VMULWHUB = 193,
  UNSPEC_VMULWLUB = 194,
  UNSPEC_VMULWHSB = 195,
  UNSPEC_VMULWLSB = 196,
  UNSPEC_VMULWHUH = 197,
  UNSPEC_VMULWLUH = 198,
  UNSPEC_VMULWHSH = 199,
  UNSPEC_VMULWLSH = 200,
  UNSPEC_VUPKHUB = 201,
  UNSPEC_VUPKHUH = 202,
  UNSPEC_VUPKLUB = 203,
  UNSPEC_VUPKLUH = 204,
  UNSPEC_VPERMSI = 205,
  UNSPEC_VPERMHI = 206,
  UNSPEC_INTERHI = 207,
  UNSPEC_INTERLO = 208,
  UNSPEC_VUPKHS_V4SF = 209,
  UNSPEC_VUPKLS_V4SF = 210,
  UNSPEC_VUPKHU_V4SF = 211,
  UNSPEC_VUPKLU_V4SF = 212,
  UNSPEC_VGBBD = 213,
  UNSPEC_VMRGH_DIRECT = 214,
  UNSPEC_VMRGL_DIRECT = 215,
  UNSPEC_VSPLT_DIRECT = 216,
  UNSPEC_VSUMSWS_DIRECT = 217,
  UNSPEC_VADDCUQ = 218,
  UNSPEC_VADDEUQM = 219,
  UNSPEC_VADDECUQ = 220,
  UNSPEC_VSUBCUQ = 221,
  UNSPEC_VSUBEUQM = 222,
  UNSPEC_VSUBECUQ = 223,
  UNSPEC_VBPERMQ = 224,
  UNSPEC_BCDADD = 225,
  UNSPEC_BCDSUB = 226,
  UNSPEC_BCD_OVERFLOW = 227,
  UNSPEC_MOVSD_LOAD = 228,
  UNSPEC_MOVSD_STORE = 229,
  UNSPEC_DDEDPD = 230,
  UNSPEC_DENBCD = 231,
  UNSPEC_DXEX = 232,
  UNSPEC_DIEX = 233,
  UNSPEC_DSCLI = 234,
  UNSPEC_DSCRI = 235,
  UNSPEC_INTERHI_V2SF = 236,
  UNSPEC_INTERLO_V2SF = 237,
  UNSPEC_EXTEVEN_V2SF = 238,
  UNSPEC_EXTODD_V2SF = 239,
  UNSPEC_VCIPHER = 240,
  UNSPEC_VNCIPHER = 241,
  UNSPEC_VCIPHERLAST = 242,
  UNSPEC_VNCIPHERLAST = 243,
  UNSPEC_VSBOX = 244,
  UNSPEC_VSHASIGMA = 245,
  UNSPEC_VPERMXOR = 246,
  UNSPEC_VPMSUM = 247
};
#define NUM_UNSPEC_VALUES 248
extern const char *const unspec_strings[];

enum unspecv {
  UNSPECV_BLOCK = 0,
  UNSPECV_LL = 1,
  UNSPECV_SC = 2,
  UNSPECV_PROBE_STACK_RANGE = 3,
  UNSPECV_EH_RR = 4,
  UNSPECV_ISYNC = 5,
  UNSPECV_MFTB = 6,
  UNSPECV_SET_VRSAVE = 7,
  UNSPECV_MTVSCR = 8,
  UNSPECV_MFVSCR = 9,
  UNSPECV_DSSALL = 10,
  UNSPECV_DSS = 11,
  UNSPECV_HTM_TABORT = 12,
  UNSPECV_HTM_TABORTXC = 13,
  UNSPECV_HTM_TABORTXCI = 14,
  UNSPECV_HTM_TBEGIN = 15,
  UNSPECV_HTM_TCHECK = 16,
  UNSPECV_HTM_TEND = 17,
  UNSPECV_HTM_TRECHKPT = 18,
  UNSPECV_HTM_TRECLAIM = 19,
  UNSPECV_HTM_TSR = 20,
  UNSPECV_HTM_TTEST = 21,
  UNSPECV_HTM_MFSPR = 22,
  UNSPECV_HTM_MTSPR = 23
};
#define NUM_UNSPECV_VALUES 24
extern const char *const unspecv_strings[];

#endif /* GCC_INSN_CONSTANTS_H */
