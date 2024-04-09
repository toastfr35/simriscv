
# RISC-V compiler (windows)

* Install the RISC-V compiler from  https://gnutoolchains.com/risc-v/
* Edit test/Makefile to change 'PREFIX'

# Example run

```
./simriscv.exe test/test.bin

0x00000000:     auipc           sp, 0x100
                                                                     SP = 0x0 -> 0x100000
0x00000004:     addi            sp, sp, -4
                                                                     SP = 0x100000 -> 0xffffc
0x00000008:     jal             0x28
                                                                     RA = 0x0 -> 0xc
0x00000030:     c.addi          sp, -0x10
                                                                     SP = 0xffffc -> 0xfffec
0x00000032:     c.fswsp         ft1, 8(sp)
                                                                     WRITE 8 bytes (0xc) @ 0xffff4
0x00000034:     c.fswsp         fs0, 0(sp)
                                                                     WRITE 8 bytes (0x0) @ 0xfffec
0x00000036:     c.addi4spn              s0, sp, 0x10
                                                                     FP = 0x0 -> 0xffffc
                                                                     S0 = 0x0 -> 0xffffc
0x00000038:     addi            a0, zero, 1
                                                                     A0 = 0x0 -> 0x1
0x0000003c:     flw             fa5, 0x15c(zero)
                                                                     READ  4 bytes (0x3f800000) @ 0x15c
                                                                     FA5 = 0x0 -> 0x3f800000
0x00000040:     fmv.s           fa0, fa5
                                                                     FA0 = 0x0 -> 0x3f800000
0x00000044:     jal             -0x36
                                                                     RA = 0xc -> 0x48
0x0000000e:     c.addi          sp, -0x20
                                                                     SP = 0xfffec -> 0xfffcc
0x00000010:     c.fswsp         fs0, 0x18(sp)
                                                                     WRITE 8 bytes (0xffffc) @ 0xfffe4
0x00000012:     c.addi4spn              s0, sp, 0x20
                                                                     FP = 0xffffc -> 0xfffec
                                                                     S0 = 0xffffc -> 0xfffec
0x00000014:     fsw             fa0, -0x14(s0)
                                                                     WRITE 4 bytes (0x3f800000) @ 0xfffd8
0x00000018:     flw             fa4, -0x14(s0)
                                                                     READ  4 bytes (0x3f800000) @ 0xfffd8
                                                                     FA4 = 0x0 -> 0x3f800000
0x0000001c:     flw             fa5, 0x158(zero)
                                                                     READ  4 bytes (0x42c80000) @ 0x158
                                                                     FA5 = 0x3f800000 -> 0x42c80000
0x00000020:     fdiv.s          fa5, fa4, fa5
                                                                     FA5 = 0x42c80000 -> 0x3c23d70a
0x00000024:     fsw             fa5, -0x14(s0)
                                                                     WRITE 4 bytes (0x3c23d70a) @ 0xfffd8
0x00000028:     c.nop
0x0000002a:     c.flwsp         fs0, 0x18(sp)
                                                                     READ  8 bytes (0xffffc) @ 0xfffe4
                                                                     FP = 0xfffec -> 0xffffc
                                                                     S0 = 0xfffec -> 0xffffc
0x0000002c:     c.addi16sp              sp, 0x20
                                                                     SP = 0xfffcc -> 0xfffec
0x0000002e:     c.jr            ra
0x00000048:     addi            a1, a1, 0x20
                                                                     A1 = 0x0 -> 0x20
0x0000004c:     c.nop
0x0000004e:     c.flwsp         ft1, 8(sp)
                                                                     READ  8 bytes (0xc) @ 0xffff4
                                                                     RA = 0x48 -> 0xc
0x00000050:     c.flwsp         fs0, 0(sp)
                                                                     READ  8 bytes (0x0) @ 0xfffec
                                                                     FP = 0xffffc -> 0x0
                                                                     S0 = 0xffffc -> 0x0
0x00000052:     c.addi          sp, 0x10
                                                                     SP = 0xfffec -> 0xffffc
0x00000054:     c.jr            ra
```
