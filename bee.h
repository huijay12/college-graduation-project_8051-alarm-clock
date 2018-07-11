#ifndef __BEE_H
#define __BEE_H

#define Fsm	65536-460800/185 //第一度 FA#
#define Gm	65536-460800/196 //第一度 SO
#define Gsm	65536-460800/207 //第一度 SO#
#define Am	65536-460800/220 //第一度 LA
#define Asm	65536-460800/233 //第一度 LA#
#define Bm	65536-460800/246 //第一度 SI
#define C	65536-460800/261 //第二度 DO
#define Cs	65536-460800/277 //第二度 DO#
#define D	65536-460800/293 //第二度 RE
#define Ds	65536-460800/311 //第二度 RE#
#define E	65536-460800/329 //第二度 MI
#define F	65536-460800/349 //第二度 FA
#define Fs	65536-460800/369 //第二度 FA#
#define G	65536-460800/392 //第二度 SO
#define Gs	65536-460800/415 //第二度 SO#
#define A	65536-460800/440 //第二度 LA
#define As	65536-460800/466 //第二度 LA#
#define B	65536-460800/493 //第二度 SI
#define Cp	65536-460800/523 //第三度 DO
#define Csp	65536-460800/554 //第三度 DO#
#define Dp	65536-460800/587 //第三度 RE	
#define Dsp	65536-460800/622 //第三度 RE#
#define Ep	65536-460800/659 //第三度 MI
#define Fp	65536-460800/698 //第三度 FA
#define Fsp	65536-460800/739 //第三度 FA#
#define Gp	65536-460800/783 //第三度 SO
#define Gsp	65536-460800/830 //第三度 SO#

#define s   1
#define end 0



sbit Speaker = P1^7;
sbit button = P0^5;
sbit P11 = P1^1;

	
     
#endif