#ifndef __SERVO_H
#define __SERVO_H

sbit servo_signal1 = P0^4;

void write_pos(int position);
void set_timer(int x);


#endif