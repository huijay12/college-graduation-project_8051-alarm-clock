#ifndef __BEE_H
#define __BEE_H

#define Fsm	65536-460800/185 //�Ĥ@�� FA#
#define Gm	65536-460800/196 //�Ĥ@�� SO
#define Gsm	65536-460800/207 //�Ĥ@�� SO#
#define Am	65536-460800/220 //�Ĥ@�� LA
#define Asm	65536-460800/233 //�Ĥ@�� LA#
#define Bm	65536-460800/246 //�Ĥ@�� SI
#define C	65536-460800/261 //�ĤG�� DO
#define Cs	65536-460800/277 //�ĤG�� DO#
#define D	65536-460800/293 //�ĤG�� RE
#define Ds	65536-460800/311 //�ĤG�� RE#
#define E	65536-460800/329 //�ĤG�� MI
#define F	65536-460800/349 //�ĤG�� FA
#define Fs	65536-460800/369 //�ĤG�� FA#
#define G	65536-460800/392 //�ĤG�� SO
#define Gs	65536-460800/415 //�ĤG�� SO#
#define A	65536-460800/440 //�ĤG�� LA
#define As	65536-460800/466 //�ĤG�� LA#
#define B	65536-460800/493 //�ĤG�� SI
#define Cp	65536-460800/523 //�ĤT�� DO
#define Csp	65536-460800/554 //�ĤT�� DO#
#define Dp	65536-460800/587 //�ĤT�� RE	
#define Dsp	65536-460800/622 //�ĤT�� RE#
#define Ep	65536-460800/659 //�ĤT�� MI
#define Fp	65536-460800/698 //�ĤT�� FA
#define Fsp	65536-460800/739 //�ĤT�� FA#
#define Gp	65536-460800/783 //�ĤT�� SO
#define Gsp	65536-460800/830 //�ĤT�� SO#

#define s   1
#define end 0



sbit Speaker = P1^7;
sbit button = P0^5;
sbit P11 = P1^1;

	
     
#endif