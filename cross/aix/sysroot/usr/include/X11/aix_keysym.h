/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos53H src/gos/2d/XTOP/include/aix_keysym.h 1.16                       */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1987,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)39	1.16  src/gos/2d/XTOP/include/aix_keysym.h, x11, gos53H, h2005_47B7 11/7/05 14:08:24 */

#ifndef	_aix_keysym_h
#define	_aix_keysym_h

/* dead	key keysym */
#define	XK_dead_degree		0x180000b0

/* Japanese Input Process functions */
#define	XK_ZenKouho		0x1800ff01
#define	XK_KanjiBangou		0x1800ff02
#define	XK_HenkanMenu		0x1800ff03
#define	XK_MaeKouho		0x1800ff04
#define	XK_BunsetsuYomi		0x1800ff05
#define	XK_LeftDouble		0x1800ff06
#define	XK_RightDouble		0x1800ff07
#define	XK_LeftPhrase		0x1800ff08
#define	XK_RightPhrase		0x1800ff09
#define	XK_ErInput		0x1800ff0a
#define	XK_Reset		0x1800ff0b

/* Greek dead keysym */
#define	XK_dead_accentdieresis	0x180007ae

/* Vietnamese keysyms */
#define	XK_dead_hook_above	0x180001d2
#define	XK_dong_sign		0x180001d3
#define	XK_Ydiaeresis		0x180001d4
#define	XK_oe			0x180001d5
#define	XK_OE			0x180001d6
#define	XK_uhorn		0x180001d7
#define	XK_Uhorn		0x180001d8
#define	XK_ohorn		0x180001d9
#define	XK_Ohorn		0x180001da

/* Thai	keysyms	*/
#define	XK_Thai_yamakkan	0x18000200
#define	XK_Thai_fongman		0x18000201
#define	XK_Thai_angkhankhu	0x18000202
#define	XK_Thai_khomut		0x18000203

/* Ukrainian keysyms */
#define	XK_Ukrainian_ghe	 0x18000300
#define	XK_Ukrainian_GHE	 0x18000301

/* Hindi keysyms */
#define	XK_hindi_candrabindu		0x18000901
#define	XK_hindi_anusvara		0x18000902
#define	XK_hindi_visarga		0x18000903
#define	XK_hindi_a			0x18000905
#define	XK_hindi_aa			0x18000906
#define	XK_hindi_i			0x18000907
#define	XK_hindi_ii			0x18000908
#define	XK_hindi_u			0x18000909
#define	XK_hindi_uu			0x1800090A
#define	XK_hindi_rvocalic		0x1800090B
#define	XK_hindi_lvocalic		0x1800090C
#define	XK_hindi_ecandra		0x1800090D
#define	XK_hindi_eshort			0x1800090E
#define	XK_hindi_e			0x1800090F
#define	XK_hindi_ai			0x18000910
#define	XK_hindi_ocandra		0x18000911
#define	XK_hindi_oshort			0x18000912
#define	XK_hindi_o			0x18000913
#define	XK_hindi_au			0x18000914
#define	XK_hindi_ka			0x18000915
#define	XK_hindi_kha			0x18000916
#define	XK_hindi_ga			0x18000917
#define	XK_hindi_gha			0x18000918
#define	XK_hindi_nga			0x18000919
#define	XK_hindi_ca			0x1800091A
#define	XK_hindi_cha			0x1800091B
#define	XK_hindi_ja			0x1800091C
#define	XK_hindi_jha			0x1800091D
#define	XK_hindi_nya			0x1800091E
#define	XK_hindi_tta			0x1800091F
#define	XK_hindi_ttha			0x18000920
#define	XK_hindi_dda			0x18000921
#define	XK_hindi_ddha			0x18000922
#define	XK_hindi_nna			0x18000923
#define	XK_hindi_ta			0x18000924
#define	XK_hindi_tha			0x18000925
#define	XK_hindi_da			0x18000926
#define	XK_hindi_dha			0x18000927
#define	XK_hindi_na			0x18000928
#define	XK_hindi_nnna			0x18000929
#define	XK_hindi_pa			0x1800092A
#define	XK_hindi_pha			0x1800092B
#define	XK_hindi_ba			0x1800092C
#define	XK_hindi_bha			0x1800092D
#define	XK_hindi_ma			0x1800092E
#define	XK_hindi_ya			0x1800092F
#define	XK_hindi_ra			0x18000930
#define	XK_hindi_rra			0x18000931
#define	XK_hindi_la			0x18000932
#define	XK_hindi_lla			0x18000933
#define	XK_hindi_llla			0x18000934
#define	XK_hindi_va			0x18000935
#define	XK_hindi_sha			0x18000936
#define	XK_hindi_ssa			0x18000937
#define	XK_hindi_sa			0x18000938
#define	XK_hindi_ha			0x18000939
#define	XK_hindi_nukta			0x1800093C
#define	XK_hindi_avagraha		0x1800093D
#define	XK_hindi_aavowelsign		0x1800093E
#define	XK_hindi_ivowelsign		0x1800093F
#define	XK_hindi_iivowelsign		0x18000940
#define	XK_hindi_uvowelsign		0x18000941
#define	XK_hindi_uuvowelsign		0x18000942
#define	XK_hindi_rvocalicvowelsign	0x18000943
#define	XK_hindi_rrvocalicvowelsign	0x18000944
#define	XK_hindi_ecandravowelsign	0x18000945
#define	XK_hindi_eshortvowelsign	0x18000946
#define	XK_hindi_evowelsign		0x18000947
#define	XK_hindi_aivowelsign		0x18000948
#define	XK_hindi_ocandravowelsign	0x18000949
#define	XK_hindi_oshortvowelsign	0x1800094A
#define	XK_hindi_ovowelsign		0x1800094B
#define	XK_hindi_auvowelsign		0x1800094C
#define	XK_hindi_virama			0x1800094D
#define	XK_hindi_om			0x18000950
#define	XK_hindi_udatta			0x18000951
#define	XK_hindi_anudatta		0x18000952
#define	XK_hindi_qa			0x18000958
#define	XK_hindi_khha			0x18000959
#define	XK_hindi_ghha			0x1800095A
#define	XK_hindi_za			0x1800095B
#define	XK_hindi_dddha			0x1800095C
#define	XK_hindi_rha			0x1800095D
#define	XK_hindi_fa			0x1800095E
#define	XK_hindi_yya			0x1800095F
#define	XK_hindi_rrvocalic		0x18000960
#define	XK_hindi_llvocalic		0x18000961
#define	XK_hindi_lvocalicvowelsign	0x18000962
#define	XK_hindi_llvocalicvowelsign	0x18000963
#define	XK_hindi_danda			0x18000964
#define	XK_hindi_doubledanda		0x18000965
#define	XK_hindi_zero			0x18000966
#define	XK_hindi_one			0x18000967
#define	XK_hindi_two			0x18000968
#define	XK_hindi_three			0x18000969
#define	XK_hindi_four			0x1800096A
#define	XK_hindi_five			0x1800096B
#define	XK_hindi_six			0x1800096C
#define	XK_hindi_seven			0x1800096D
#define	XK_hindi_eight			0x1800096E
#define	XK_hindi_nine			0x1800096F
#define	XK_hindi_abbreviation		0x18000970
#define	XK_hindi_rasub			0x18000971
#define	XK_hindi_reph			0x18000972
#define	XK_hindi_janya			0x18000973
#define	XK_hindi_tara			0x18000974
#define	XK_hindi_kassa			0x18000975
#define	XK_hindi_shara			0x18000976

/* Bengali Keysyms */

#define	 XK_Bengali_candrabindu		0x18000981
#define	 XK_Bengali_anusvara		0x18000982
#define	 XK_Bengali_visarga		0x18000983
#define	 XK_Bengali_a			0x18000985
#define	 XK_Bengali_aa			0x18000986
#define	 XK_Bengali_i			0x18000987
#define	 XK_Bengali_ii			0x18000988
#define	 XK_Bengali_u			0x18000989
#define	 XK_Bengali_uu			0x1800098A
#define	 XK_Bengali_rvocalic		0x1800098B
#define	 XK_Bengali_e			0x1800098F
#define	 XK_Bengali_ai			0x18000990
#define	 XK_Bengali_o			0x18000993
#define	 XK_Bengali_au			0x18000994
#define	 XK_Bengali_ka			0x18000995
#define	 XK_Bengali_kha			0x18000996
#define	 XK_Bengali_ga			0x18000997
#define	 XK_Bengali_gha			0x18000998
#define	 XK_Bengali_nga			0x18000999
#define	 XK_Bengali_ca			0x1800099A
#define	 XK_Bengali_cha			0x1800099B
#define	 XK_Bengali_ja			0x1800099C
#define	 XK_Bengali_jha			0x1800099D
#define	 XK_Bengali_nya			0x1800099E
#define	 XK_Bengali_tta			0x1800099F
#define	 XK_Bengali_ttha		0x180009A0
#define	 XK_Bengali_dda			0x180009A1
#define	 XK_Bengali_ddha		0x180009A2
#define	 XK_Bengali_nna			0x180009A3
#define	 XK_Bengali_ta			0x180009A4
#define	 XK_Bengali_tha			0x180009A5
#define	 XK_Bengali_da			0x180009A6
#define	 XK_Bengali_dha			0x180009A7
#define	 XK_Bengali_na			0x180009A8
#define	 XK_Bengali_pa			0x180009AA
#define	 XK_Bengali_pha			0x180009AB
#define	 XK_Bengali_ba			0x180009AC
#define	 XK_Bengali_bha			0x180009AD
#define	 XK_Bengali_ma			0x180009AE
#define	 XK_Bengali_ya			0x180009AF
#define	 XK_Bengali_ra			0x180009B0
#define	 XK_Bengali_la			0x180009B2
#define	 XK_Bengali_sha			0x180009B6
#define	 XK_Bengali_ssa			0x180009B7
#define	 XK_Bengali_sa			0x180009B8
#define	 XK_Bengali_ha			0x180009B9
#define	 XK_Bengali_nukta		0x180009BC
#define	 XK_Bengali_aavowelsign		0x180009BE
#define	 XK_Bengali_ivowelsign		0x180009BF
#define	 XK_Bengali_iivowelsign		0x180009C0
#define	 XK_Bengali_uvowelsign		0x180009C1
#define	 XK_Bengali_uuvowelsign		0x180009C2
#define	 XK_Bengali_rvocalicvowelsign	0x180009C3
#define	 XK_Bengali_evowelsign		0x180009C7
#define	 XK_Bengali_aivowelsign		0x180009C8
#define	 XK_Bengali_ovowelsign		0x180009CB
#define	 XK_Bengali_auvowelsign		0x180009CC
#define	 XK_Bengali_virama		0x180009CD
#define	 XK_Bengali_yya			0x180009DF
#define	 XK_Bengali_zero		0x180009E6
#define	 XK_Bengali_one			0x180009E7
#define	 XK_Bengali_two			0x180009E8
#define	 XK_Bengali_three		0x180009E9
#define	 XK_Bengali_four		0x180009EA
#define	 XK_Bengali_five		0x180009EB
#define	 XK_Bengali_six			0x180009EC
#define	 XK_Bengali_seven		0x180009ED
#define	 XK_Bengali_eight		0x180009EE
#define	 XK_Bengali_nine		0x180009EF
#define	 XK_Assamese_ra			0x180009F0
#define	 XK_Assamese_va			0x180009F1
#define	 XK_Bengali_viramara		0x180009F8
#define	 XK_Bengali_ravirama		0x180009F9
#define	 XK_Bengali_janya		0x180009FA
#define	 XK_Bengali_tara		0x180009FB
#define	 XK_Bengali_kassa		0x180009FC
#define	 XK_Bengali_shara		0x180009FD

/* Punjabi Keysyms */
#define XK_Gurmukhi_bindi                 0x18000A02
#define XK_Gurmukhi_a                     0x18000A05
#define XK_Gurmukhi_aa                    0x18000A06
#define XK_Gurmukhi_i                     0x18000A07
#define XK_Gurmukhi_ii                    0x18000A08
#define XK_Gurmukhi_u                     0x18000A09
#define XK_Gurmukhi_uu                    0x18000A0A
#define XK_Gurmukhi_ee                    0x18000A0F
#define XK_Gurmukhi_ai                    0x18000A10
#define XK_Gurmukhi_oo                    0x18000A13
#define XK_Gurmukhi_au                    0x18000A14
#define XK_Gurmukhi_ka                    0x18000A15
#define XK_Gurmukhi_kha                   0x18000A16
#define XK_Gurmukhi_ga                    0x18000A17
#define XK_Gurmukhi_gha                   0x18000A18
#define XK_Gurmukhi_nga                   0x18000A19
#define XK_Gurmukhi_ca                    0x18000A1A
#define XK_Gurmukhi_cha                   0x18000A1B
#define XK_Gurmukhi_ja                    0x18000A1C
#define XK_Gurmukhi_jha                   0x18000A1D
#define XK_Gurmukhi_nya                   0x18000A1E
#define XK_Gurmukhi_tta                   0x18000A1F
#define XK_Gurmukhi_ttha                  0x18000A20
#define XK_Gurmukhi_dda                   0x18000A21
#define XK_Gurmukhi_ddha                  0x18000A22
#define XK_Gurmukhi_nna                   0x18000A23
#define XK_Gurmukhi_ta                    0x18000A24
#define XK_Gurmukhi_tha                   0x18000A25
#define XK_Gurmukhi_da                    0x18000A26
#define XK_Gurmukhi_dha                   0x18000A27
#define XK_Gurmukhi_na                    0x18000A28
#define XK_Gurmukhi_pa                    0x18000A2A
#define XK_Gurmukhi_pha                   0x18000A2B
#define XK_Gurmukhi_ba                    0x18000A2C
#define XK_Gurmukhi_bha                   0x18000A2D
#define XK_Gurmukhi_ma                    0x18000A2E
#define XK_Gurmukhi_ya                    0x18000A2F
#define XK_Gurmukhi_ra                    0x18000A30
#define XK_Gurmukhi_la                    0x18000A32
#define XK_Gurmukhi_lla                   0x18000A33
#define XK_Gurmukhi_va                    0x18000A35
#define XK_Gurmukhi_sha                   0x18000A36
#define XK_Gurmukhi_sa                    0x18000A38
#define XK_Gurmukhi_ha                    0x18000A39
#define XK_Gurmukhi_nukta                 0x18000A3C
#define XK_Gurmukhi_aavowelsign           0x18000A3E
#define XK_Gurmukhi_ivowelsign            0x18000A3F
#define XK_Gurmukhi_iivowelsign           0x18000A40
#define XK_Gurmukhi_uvowelsign            0x18000A41
#define XK_Gurmukhi_uuvowelsign           0x18000A42
#define XK_Gurmukhi_eevowelsign           0x18000A47
#define XK_Gurmukhi_aivowelsign           0x18000A48
#define XK_Gurmukhi_oovowelsign           0x18000A4B
#define XK_Gurmukhi_auvowelsign           0x18000A4C
#define XK_Gurmukhi_virama                0x18000A4D
#define XK_Gurmukhi_zero                  0x18000A66
#define XK_Gurmukhi_one                   0x18000A67
#define XK_Gurmukhi_two                   0x18000A68
#define XK_Gurmukhi_three                 0x18000A69
#define XK_Gurmukhi_four                  0x18000A6A
#define XK_Gurmukhi_five                  0x18000A6B
#define XK_Gurmukhi_six                   0x18000A6C
#define XK_Gurmukhi_seven                 0x18000A6D
#define XK_Gurmukhi_eight                 0x18000A6E
#define XK_Gurmukhi_nine                  0x18000A6F
#define XK_Gurmukhi_tippi                 0x18000A70
#define XK_Gurmukhi_addak                 0x18000A71
#define XK_Gurmukhi_addakra               0x18000A72


/*Tamil	Keysym */
#define	XK_tamil_visarga		0x18000B83	
#define	XK_tamil_a			0x18000B85	
#define	XK_tamil_aa			0x18000B86	
#define	XK_tamil_i			0x18000B87	
#define	XK_tamil_ii			0x18000B88	
#define	XK_tamil_u			0x18000B89	
#define	XK_tamil_uu			0x18000B8A	
#define	XK_tamil_e			0x18000B8E	
#define	XK_tamil_ee			0x18000B8F	
#define	XK_tamil_ai			0x18000B90	
#define	XK_tamil_o			0x18000B92	
#define	XK_tamil_oo			0x18000B93	
#define	XK_tamil_au			0x18000B94	
#define	XK_tamil_ka			0x18000B95	
#define	XK_tamil_nga			0x18000B99	
#define	XK_tamil_ca			0x18000B9A	
#define	XK_tamil_ja			0x18000B9C	
#define	XK_tamil_nya			0x18000B9E	
#define	XK_tamil_tta			0x18000B9F	
#define	XK_tamil_nna			0x18000BA3	
#define	XK_tamil_ta			0x18000BA4	
#define	XK_tamil_na			0x18000BA8	
#define	XK_tamil_nnna			0x18000BA9	
#define	XK_tamil_pa			0x18000BAA	
#define	XK_tamil_ma			0x18000BAE	
#define	XK_tamil_ya			0x18000BAF	
#define	XK_tamil_ra			0x18000BB0	
#define	XK_tamil_rra			0x18000BB1	
#define	XK_tamil_la			0x18000BB2	
#define	XK_tamil_lla			0x18000BB3	
#define	XK_tamil_llla			0x18000BB4	
#define	XK_tamil_va			0x18000BB5	
#define	XK_tamil_ssa			0x18000BB7	
#define	XK_tamil_sa			0x18000BB8	
#define	XK_tamil_ha			0x18000BB9	
#define	XK_tamil_aavowelsign		0x18000BBE	
#define	XK_tamil_ivowelsign		0x18000BBF	
#define	XK_tamil_iivowelsign		0x18000BC0	
#define	XK_tamil_uvowelsign		0x18000BC1	
#define	XK_tamil_uuvowelsign		0x18000BC2	
#define	XK_tamil_evowelsign		0x18000BC6	
#define	XK_tamil_eevowelsign		0x18000BC7	
#define	XK_tamil_aivowelsign		0x18000BC8	
#define	XK_tamil_ovowelsign		0x18000BCA	
#define	XK_tamil_oovowelsign		0x18000BCB	
#define	XK_tamil_auvowelsign		0x18000BCC	
#define	XK_tamil_virama			0x18000BCD	
#define	XK_tamil_one			0x18000BE7	
#define	XK_tamil_two			0x18000BE8	
#define	XK_tamil_three			0x18000BE9	
#define	XK_tamil_four			0x18000BEA	
#define	XK_tamil_five			0x18000BEB	
#define	XK_tamil_six			0x18000BEC	
#define	XK_tamil_seven			0x18000BED	
#define	XK_tamil_eight			0x18000BEE	
#define	XK_tamil_nine			0x18000BEF	
#define	XK_tamil_ten			0x18000BF0	
#define	XK_tamil_hundred		0x18000BF1	
#define	XK_tamil_thousand		0x18000BF2	
#define	XK_tamil_tra			0x18000BFC	
#define	XK_tamil_ksha			0x18000BFD	
#define	XK_tamil_shra			0x18000BFE	
#define	XK_tamil_shri			0x18000BFF	

/* Telugu Keysyms */
#define	XK_Telugu_candrabindu		0x18000C01
#define	XK_Telugu_anusvara		0x18000C02
#define	XK_Telugu_visarga		0x18000C03
#define	XK_Telugu_a			0x18000C05
#define	XK_Telugu_aa			0x18000C06
#define	XK_Telugu_i			0x18000C07
#define	XK_Telugu_ii			0x18000C08
#define	XK_Telugu_u			0x18000C09
#define	XK_Telugu_uu			0x18000C0A
#define	XK_Telugu_vocalicr		0x18000C0B
#define	XK_Telugu_e			0x18000C0E
#define	XK_Telugu_ee			0x18000C0F
#define	XK_Telugu_ai			0x18000C10
#define	XK_Telugu_o			0x18000C12
#define	XK_Telugu_oo			0x18000C13
#define	XK_Telugu_au			0x18000C14
#define	XK_Telugu_ka			0x18000C15
#define	XK_Telugu_kha			0x18000C16
#define	XK_Telugu_ga			0x18000C17
#define	XK_Telugu_gha			0x18000C18
#define	XK_Telugu_nga			0x18000C19
#define	XK_Telugu_ca			0x18000C1A
#define	XK_Telugu_cha			0x18000C1B
#define	XK_Telugu_ja			0x18000C1C
#define	XK_Telugu_jha			0x18000C1D
#define	XK_Telugu_nya			0x18000C1E
#define	XK_Telugu_tta			0x18000C1F
#define	XK_Telugu_ttha			0x18000C20
#define	XK_Telugu_dda			0x18000C21
#define	XK_Telugu_ddha			0x18000C22
#define	XK_Telugu_nna			0x18000C23
#define	XK_Telugu_ta			0x18000C24
#define	XK_Telugu_tha			0x18000C25
#define	XK_Telugu_da			0x18000C26
#define	XK_Telugu_dha			0x18000C27
#define	XK_Telugu_na			0x18000C28
#define	XK_Telugu_pa			0x18000C2A
#define	XK_Telugu_pha			0x18000C2B
#define	XK_Telugu_ba			0x18000C2C
#define	XK_Telugu_bha			0x18000C2D
#define	XK_Telugu_ma			0x18000C2E
#define	XK_Telugu_ya			0x18000C2F
#define	XK_Telugu_ra			0x18000C30
#define	XK_Telugu_rra			0x18000C31
#define	XK_Telugu_la			0x18000C32
#define	XK_Telugu_lla			0x18000C33
#define	XK_Telugu_va			0x18000C35
#define	XK_Telugu_sha			0x18000C36
#define	XK_Telugu_ssa			0x18000C37
#define	XK_Telugu_sa			0x18000C38
#define	XK_Telugu_ha			0x18000C39
#define	XK_Telugu_aavowelsign		0x18000C3E
#define	XK_Telugu_ivowelsign		0x18000C3F
#define	XK_Telugu_iivowelsign		0x18000C40
#define	XK_Telugu_uvowelsign		0x18000C41
#define	XK_Telugu_uuvowelsign		0x18000C42
#define	XK_Telugu_vocalicrvowelsign	0x18000C43
#define	XK_Telugu_evowelsign		0x18000C46
#define	XK_Telugu_eevowelsign		0x18000C47
#define	XK_Telugu_aivowelsign		0x18000C48
#define	XK_Telugu_ovowelsign		0x18000C4A
#define	XK_Telugu_oovowelsign		0x18000C4B
#define	XK_Telugu_auvowelsign		0x18000C4C
#define	XK_Telugu_virama		0x18000C4D
#define	XK_Telugu_zero			0x18000C66
#define	XK_Telugu_one			0x18000C67
#define	XK_Telugu_two			0x18000C68
#define	XK_Telugu_three			0x18000C69
#define	XK_Telugu_four			0x18000C6A
#define	XK_Telugu_five			0x18000C6B
#define	XK_Telugu_six			0x18000C6C
#define	XK_Telugu_seven			0x18000C6D
#define	XK_Telugu_eight			0x18000C6E
#define	XK_Telugu_nine			0x18000C6F
#define	XK_Telugu_tra			0x18000C70
#define	XK_Telugu_ksha			0x18000C71
#define	XK_Telugu_shra			0x18000C72
#define	XK_Telugu_jnya			0x18000C73
#define	XK_Telugu_viramara		0x18000C74

/*  Gujarati Keysyms*/
#define	 XK_Gujarati_candrabindu	0x18000A81
#define	 XK_Gujarati_anusvara		0x18000A82
#define	 XK_Gujarati_visarga		0x18000A83
#define	 XK_Gujarati_a			0x18000A85
#define	 XK_Gujarati_aa			0x18000A86
#define	 XK_Gujarati_i			0x18000A87
#define	 XK_Gujarati_ii			0x18000A88
#define	 XK_Gujarati_u			0x18000A89
#define	 XK_Gujarati_uu			0x18000A8A
#define	 XK_Gujarati_rvocalic		0x18000A8B
#define	 XK_Gujarati_candrae		0x18000A8D
#define	 XK_Gujarati_e			0x18000A8F
#define	 XK_Gujarati_ai			0x18000A90
#define	 XK_Gujarati_candrao		0x18000A91
#define	 XK_Gujarati_o			0x18000A93
#define	 XK_Gujarati_au			0x18000A94
#define	 XK_Gujarati_ka			0x18000A95
#define	 XK_Gujarati_kha		0x18000A96
#define	 XK_Gujarati_ga			0x18000A97
#define	 XK_Gujarati_gha		0x18000A98
#define	 XK_Gujarati_nga		0x18000A99
#define	 XK_Gujarati_ca			0x18000A9A
#define	 XK_Gujarati_cha		0x18000A9B
#define	 XK_Gujarati_ja			0x18000A9C
#define	 XK_Gujarati_jha		0x18000A9D
#define	 XK_Gujarati_nya		0x18000A9E
#define	 XK_Gujarati_tta		0x18000A9F
#define	 XK_Gujarati_ttha		0x18000AA0
#define	 XK_Gujarati_dda		0x18000AA1
#define	 XK_Gujarati_ddha		0x18000AA2
#define	 XK_Gujarati_nna		0x18000AA3
#define	 XK_Gujarati_ta			0x18000AA4
#define	 XK_Gujarati_tha		0x18000AA5
#define	 XK_Gujarati_da			0x18000AA6
#define	 XK_Gujarati_dha		0x18000AA7
#define	 XK_Gujarati_na			0x18000AA8
#define	 XK_Gujarati_pa			0x18000AAA
#define	 XK_Gujarati_pha		0x18000AAB
#define	 XK_Gujarati_ba			0x18000AAC
#define	 XK_Gujarati_bha		0x18000AAD
#define	 XK_Gujarati_ma			0x18000AAE
#define	 XK_Gujarati_ya			0x18000AAF
#define	 XK_Gujarati_ra			0x18000AB0
#define	 XK_Gujarati_la			0x18000AB2
#define	 XK_Gujarati_lla		0x18000AB3
#define	 XK_Gujarati_va			0x18000AB5
#define	 XK_Gujarati_sha		0x18000AB6
#define	 XK_Gujarati_ssa		0x18000AB7
#define	 XK_Gujarati_sa			0x18000AB8
#define	 XK_Gujarati_ha			0x18000AB9
#define	 XK_Gujarati_nukta		0x18000ABC
#define	 XK_Gujarati_aavowelsign	0x18000ABE
#define	 XK_Gujarati_ivowelsign		0x18000ABF
#define	 XK_Gujarati_iivowelsign	0x18000AC0
#define	 XK_Gujarati_uvowelsign		0x18000AC1
#define	 XK_Gujarati_uuvowelsign	0x18000AC2
#define	 XK_Gujarati_rvocalicvowelsign	0x18000AC3
#define	 XK_Gujarati_ecandravowelsign	0x18000AC5
#define	 XK_Gujarati_evowelsign		0x18000AC7
#define	 XK_Gujarati_aivowelsign	0x18000AC8
#define	 XK_Gujarati_ocandravowelsign	0x18000AC9
#define	 XK_Gujarati_ovowelsign		0x18000ACB
#define	 XK_Gujarati_auvowelsign	0x18000ACC
#define	 XK_Gujarati_virama		0x18000ACD
#define	 XK_Gujarati_zero		0x18000AE6
#define	 XK_Gujarati_one		0x18000AE7
#define	 XK_Gujarati_two		0x18000AE8
#define	 XK_Gujarati_three		0x18000AE9
#define	 XK_Gujarati_four		0x18000AEA
#define	 XK_Gujarati_five		0x18000AEB
#define	 XK_Gujarati_six		0x18000AEC
#define	 XK_Gujarati_seven		0x18000AED
#define	 XK_Gujarati_eight		0x18000AEE
#define	 XK_Gujarati_nine		0x18000AEF

/* Kazakh Keysyms */
#define	XK_Cyrillic_SCHWA		0x180004D8
#define	XK_Cyrillic_schwa		0x180004D9
#define	XK_Cyrillic_EN_descender	0x180004A2
#define	XK_Cyrillic_en_descender	0x180004A3
#define	XK_Cyrillic_GHE_stroke		0x18000492
#define	XK_Cyrillic_ghe_stroke		0x18000493
#define	XK_Cyrillic_straight_U		0x180004AE
#define	XK_Cyrillic_straight_u		0x180004AF
#define	XK_Cyrillic_straight_U_stroke	0x180004B0
#define	XK_Cyrillic_straight_u_stroke	0x180004B1
#define	XK_Cyrillic_KA_descender	0x1800049A
#define	XK_Cyrillic_ka_descender	0x1800049B
#define	XK_Cyrillic_barred_O		0x180004E8
#define	XK_Cyrillic_barred_o		0x180004E9
#define	XK_Cyrillic_SHHA		0x180004BA
#define	XK_Cyrillic_shha		0x180004BB

/* Malayalam Keysyms */
#define	XK_Malayalam_anusvara		0x18000D02
#define	XK_Malayalam_visarga		0x18000D03
#define	XK_Malayalam_a			0x18000D05
#define	XK_Malayalam_aa			0x18000D06
#define	XK_Malayalam_i			0x18000D07
#define	XK_Malayalam_ii			0x18000D08
#define	XK_Malayalam_u			0x18000D09
#define	XK_Malayalam_uu			0x18000D0A
#define	XK_Malayalam_rvocalic		0x18000D0B
#define	XK_Malayalam_e			0x18000D0E
#define	XK_Malayalam_ee			0x18000D0F
#define	XK_Malayalam_ai			0x18000D10
#define	XK_Malayalam_o			0x18000D12
#define	XK_Malayalam_oo			0x18000D13
#define	XK_Malayalam_au			0x18000D14
#define	XK_Malayalam_ka			0x18000D15
#define	XK_Malayalam_kha		0x18000D16
#define	XK_Malayalam_ga			0x18000D17
#define	XK_Malayalam_gha		0x18000D18
#define	XK_Malayalam_nga		0x18000D19
#define	XK_Malayalam_ca			0x18000D1A
#define	XK_Malayalam_cha		0x18000D1B
#define	XK_Malayalam_ja			0x18000D1C
#define	XK_Malayalam_jha		0x18000D1D
#define	XK_Malayalam_nya		0x18000D1E
#define	XK_Malayalam_tta		0x18000D1F
#define	XK_Malayalam_ttha		0x18000D20
#define	XK_Malayalam_dda		0x18000D21
#define	XK_Malayalam_ddha		0x18000D22
#define	XK_Malayalam_nna		0x18000D23
#define	XK_Malayalam_ta			0x18000D24
#define	XK_Malayalam_tha		0x18000D25
#define	XK_Malayalam_da			0x18000D26
#define	XK_Malayalam_dha		0x18000D27
#define	XK_Malayalam_na			0x18000D28
#define	XK_Malayalam_pa			0x18000D2A
#define	XK_Malayalam_pha		0x18000D2B
#define	XK_Malayalam_ba			0x18000D2C
#define	XK_Malayalam_bha		0x18000D2D
#define	XK_Malayalam_ma			0x18000D2E
#define	XK_Malayalam_ya			0x18000D2F
#define	XK_Malayalam_ra			0x18000D30
#define	XK_Malayalam_rra		0x18000D31
#define	XK_Malayalam_la			0x18000D32
#define	XK_Malayalam_lla		0x18000D33
#define	XK_Malayalam_llla		0x18000D34
#define	XK_Malayalam_va			0x18000D35
#define	XK_Malayalam_sha		0x18000D36
#define	XK_Malayalam_ssa		0x18000D37
#define	XK_Malayalam_sa			0x18000D38
#define	XK_Malayalam_ha			0x18000D39
#define	XK_Malayalam_aavowelsign	0x18000D3E
#define	XK_Malayalam_ivowelsign		0x18000D3F
#define	XK_Malayalam_iivowelsign	0x18000D40
#define	XK_Malayalam_uvowelsign		0x18000D41
#define	XK_Malayalam_uuvowelsign	0x18000D42
#define	XK_Malayalam_rvocalicvowelsign	0x18000D43
#define	XK_Malayalam_evowelsign		0x18000D46
#define	XK_Malayalam_eevowelsign	0x18000D47
#define	XK_Malayalam_aivowelsign	0x18000D48
#define	XK_Malayalam_ovowelsign		0x18000D4A
#define	XK_Malayalam_oovowelsign	0x18000D4B
#define	XK_Malayalam_auvowelsign	0x18000D57
#define	XK_Malayalam_virama		0x18000D4D
#define	XK_Malayalam_zero		0x18000D66
#define	XK_Malayalam_one		0x18000D67
#define	XK_Malayalam_two		0x18000D68
#define	XK_Malayalam_three		0x18000D69
#define	XK_Malayalam_four		0x18000D6A
#define	XK_Malayalam_five		0x18000D6B
#define	XK_Malayalam_six		0x18000D6C
#define	XK_Malayalam_seven		0x18000D6D
#define	XK_Malayalam_eight		0x18000D6E
#define	XK_Malayalam_nine		0x18000D6F
#define	XK_Malayalam_ravirama		0x18000D70
#define	XK_Malayalam_janya		0x18000D71
#define	XK_Malayalam_tara		0x18000D72
#define	XK_Malayalam_kassa		0x18000D73
#define	XK_Malayalam_shara		0x18000D74
#define	XK_Malayalam_zwnj		0x18000D75

/*  Kannada Keysyms */

#define	 XK_Kannada_anusvara		0x18000C82
#define	 XK_Kannada_visarga		0x18000C83
#define	 XK_Kannada_a			0x18000C85
#define	 XK_Kannada_aa			0x18000C86
#define	 XK_Kannada_i			0x18000C87
#define	 XK_Kannada_ii			0x18000C88
#define	 XK_Kannada_u			0x18000C89
#define	 XK_Kannada_uu			0x18000C8A
#define	 XK_Kannada_vocalicr		0x18000C8B
#define	 XK_Kannada_e			0x18000C8E
#define	 XK_Kannada_ee			0x18000C8F
#define	 XK_Kannada_ai			0x18000C90
#define	 XK_Kannada_o			0x18000C92
#define	 XK_Kannada_oo			0x18000C93
#define	 XK_Kannada_au			0x18000C94
#define	 XK_Kannada_ka			0x18000C95
#define	 XK_Kannada_kha			0x18000C96
#define	 XK_Kannada_ga			0x18000C97
#define	 XK_Kannada_gha			0x18000C98
#define	 XK_Kannada_nga			0x18000C99
#define	 XK_Kannada_ca			0x18000C9A
#define	 XK_Kannada_cha			0x18000C9B
#define	 XK_Kannada_ja			0x18000C9C
#define	 XK_Kannada_jha			0x18000C9D
#define	 XK_Kannada_nya			0x18000C9E
#define	 XK_Kannada_tta			0x18000C9F
#define	 XK_Kannada_ttha		0x18000CA0
#define	 XK_Kannada_dda			0x18000CA1
#define	 XK_Kannada_ddha		0x18000CA2
#define	 XK_Kannada_nna			0x18000CA3
#define	 XK_Kannada_ta			0x18000CA4
#define	 XK_Kannada_tha			0x18000CA5
#define	 XK_Kannada_da			0x18000CA6
#define	 XK_Kannada_dha			0x18000CA7
#define	 XK_Kannada_na			0x18000CA8
#define	 XK_Kannada_pa			0x18000CAA
#define	 XK_Kannada_pha			0x18000CAB
#define	 XK_Kannada_ba			0x18000CAC
#define	 XK_Kannada_bha			0x18000CAD
#define	 XK_Kannada_ma			0x18000CAE
#define	 XK_Kannada_ya			0x18000CAF
#define	 XK_Kannada_ra			0x18000CB0
#define	 XK_Kannada_la			0x18000CB2
#define	 XK_Kannada_lla			0x18000CB3
#define	 XK_Kannada_va			0x18000CB5
#define	 XK_Kannada_sha			0x18000CB6
#define	 XK_Kannada_ssa			0x18000CB7
#define	 XK_Kannada_sa			0x18000CB8
#define	 XK_Kannada_ha			0x18000CB9
#define	 XK_Kannada_nukta		0x18000CBC
#define	 XK_Kannada_aavowelsign		0x18000CBE
#define	 XK_Kannada_ivowelsign		0x18000CBF
#define	 XK_Kannada_iivowelsign		0x18000CC0
#define	 XK_Kannada_uvowelsign		0x18000CC1
#define	 XK_Kannada_uuvowelsign		0x18000CC2
#define	 XK_Kannada_vocalicrvowelsign	0x18000CC3
#define	 XK_Kannada_evowelsign		0x18000CC6
#define	 XK_Kannada_eevowelsign		0x18000CC7
#define	 XK_Kannada_aivowelsign		0x18000CC8
#define	 XK_Kannada_ovowelsign		0x18000CCA
#define	 XK_Kannada_oovowelsign		0x18000CCB
#define	 XK_Kannada_auvowelsign		0x18000CCC
#define	 XK_Kannada_virama		0x18000CCD
#define	 XK_Kannada_zero		0x18000CE6
#define	 XK_Kannada_one			0x18000CE7
#define	 XK_Kannada_two			0x18000CE8
#define	 XK_Kannada_three		0x18000CE9
#define	 XK_Kannada_four		0x18000CEA
#define	 XK_Kannada_five		0x18000CEB
#define	 XK_Kannada_six			0x18000CEC
#define	 XK_Kannada_seven		0x18000CED
#define	 XK_Kannada_eight		0x18000CEE
#define	 XK_Kannada_nine		0x18000CEF
#define	 XK_Kannada_tra			0x18000CF0
#define	 XK_Kannada_kssa		0x18000CF1
#define	 XK_Kannada_shra		0x18000CF2
#define	 XK_Kannada_jnya		0x18000CF3
#define	 XK_Kannada_viramara		0x18000CF4
#define	 XK_Kannada_ravirama		0x18000CF5


/*  Oriya Keysyms*/

#define	XK_Oriya_candrabindu		0x18000B01
#define	XK_Oriya_anusvara		0x18000B02
#define	XK_Oriya_visarga		0x18000B03
#define	XK_Oriya_a			0x18000B05
#define	XK_Oriya_aa			0x18000B06
#define	XK_Oriya_i			0x18000B07
#define	XK_Oriya_ii			0x18000B08
#define	XK_Oriya_u			0x18000B09
#define	XK_Oriya_uu			0x18000B0A
#define	XK_Oriya_vocalic_r		0x18000B0B
#define	XK_Oriya_e			0x18000B0F
#define	XK_Oriya_ai			0x18000B10
#define	XK_Oriya_o			0x18000B13
#define	XK_Oriya_au			0x18000B14
#define	XK_Oriya_ka			0x18000B15
#define	XK_Oriya_kha			0x18000B16
#define	XK_Oriya_ga			0x18000B17
#define	XK_Oriya_gha			0x18000B18
#define	XK_Oriya_nga			0x18000B19
#define	XK_Oriya_ca			0x18000B1A
#define	XK_Oriya_cha			0x18000B1B
#define	XK_Oriya_ja			0x18000B1C
#define	XK_Oriya_jha			0x18000B1D
#define	XK_Oriya_nya			0x18000B1E
#define	XK_Oriya_tta			0x18000B1F
#define	XK_Oriya_ttha			0x18000B20
#define	XK_Oriya_dda			0x18000B21
#define	XK_Oriya_ddha			0x18000B22
#define	XK_Oriya_nna			0x18000B23
#define	XK_Oriya_ta			0x18000B24
#define	XK_Oriya_tha			0x18000B25
#define	XK_Oriya_da			0x18000B26
#define	XK_Oriya_dha			0x18000B27
#define	XK_Oriya_na			0x18000B28
#define	XK_Oriya_pa			0x18000B2A
#define	XK_Oriya_pha			0x18000B2B
#define	XK_Oriya_ba			0x18000B2C
#define	XK_Oriya_bha			0x18000B2D
#define	XK_Oriya_ma			0x18000B2E
#define	XK_Oriya_ya			0x18000B2F
#define	XK_Oriya_ra			0x18000B30
#define	XK_Oriya_la			0x18000B32
#define	XK_Oriya_lla			0x18000B33
#define	XK_Oriya_va			0x18000B35
#define	XK_Oriya_sha			0x18000B36
#define	XK_Oriya_ssa			0x18000B37
#define	XK_Oriya_sa			0x18000B38
#define	XK_Oriya_ha			0x18000B39
#define	XK_Oriya_nukta			0x18000B3C
#define	XK_Oriya_aavowelsign		0x18000B3E
#define	XK_Oriya_ivowelsign		0x18000B3F
#define	XK_Oriya_iivowelsign		0x18000B40
#define	XK_Oriya_uvowelsign		0x18000B41
#define	XK_Oriya_uuvowelsign		0x18000B42
#define	XK_Oriya_vocalicrvowelsign	0x18000B43
#define	XK_Oriya_evowelsign		0x18000B47
#define	XK_Oriya_aivowelsign		0x18000B48
#define	XK_Oriya_ovowelsign		0x18000B4B
#define	XK_Oriya_auvowelsign		0x18000B4C
#define	XK_Oriya_virama			0x18000B4D
#define	XK_Oriya_yya			0x18000B5F
#define	XK_Oriya_zero			0x18000B66
#define	XK_Oriya_one			0x18000B67
#define	XK_Oriya_two			0x18000B68
#define	XK_Oriya_three			0x18000B69
#define	XK_Oriya_four			0x18000B6A
#define	XK_Oriya_five			0x18000B6B
#define	XK_Oriya_six			0x18000B6C
#define	XK_Oriya_seven			0x18000B6D
#define	XK_Oriya_eight			0x18000B6E
#define	XK_Oriya_nine			0x18000B6F
#define	XK_Oriya_wa			0x18000B71
#define	XK_Oriya_viramara		0x18000B72
#define	XK_Oriya_ravirama		0x18000B73
#define	XK_Oriya_jnya			0x18000B74
#define	XK_Oriya_tra			0x18000B75
#define	XK_Oriya_kssa			0x18000B76
#define	XK_Oriya_shra			0x18000B77

#endif	/* _aix_keysym_h */