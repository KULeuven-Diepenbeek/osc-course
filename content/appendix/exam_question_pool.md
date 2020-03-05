---
title: 'A. Exam Question Pool'
draft: true
---

## ch1
## ch2: Interrupts

### Exercise: calculation w.r.t. timer

Assume we have an ATMega controller, identical to the one on the Arduino. This controller has a crystal that oscillates at **2^10 kHz**. The prescaler that is present in the ATMega is set to divide the incoming clock with a factor 1024.
There is an **8-bit** counter that will count and an interrupt on the Timer's overflow is enable. When this interrupt hits, the LED is toggled.

**Question 1:** What is the **frequency** at which the LED flashes ? Calculate and motivate your calculations.

**Question 2:** Give the line of C code to overwrite the counter value TCNT0 so that frequency of the flashing LED is **10 Hz**. Motviate your calculations.

**Solution:**
The frequency with which the TCCR0 counts is 2^10 * 1e3 / 2^10 = 1e3 Hz = 1000 Hz. The corresponding period equals 1 ms.

The counter needs 2^8 clock ticks to reach its maximum. Therefore it will count from 0 to 255 in 256 * 1ms = 256 ms. This duration is half of the period, so the period of the toggling LED is 512ms, which corresponds to **1.95 Hz**.

If the desired frequency is 10 Hz, which corresponds to a period of 0.1 s, the LED should toggle every 0.05 s.
0.05 s / 0.001 s  = 50 ticks = 0x32 ticks

0xFF - 0x32 = 0xCD

**TCNT0 = 0xCD;** or **TCNT0 = ~(0x32);**


## ch3
## ch4
## ch5
## ch6
## ch7
## ch8
## ch9