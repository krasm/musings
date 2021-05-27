#!/usr/bin/env python3

import sys

def dig(v):
    if 0 <= v <= 9:
        return chr(ord('0') + v)
    return chr(ord('A') + (v-10))

def val(s):
    if ord('0') <= ord(s) <= ord('9'):
        return ord(s) - ord('0')
    return 10 + (ord(s) - ord('A'))

def convert_10(a):
    result = 0
    i = len(a) - 1
    while i >= 0:
        result = result + (val(a[i]) * (32 ** i))
        i = i - 1

    return result

def convert_32(a):
    result = ""
    while(a > 0):
        result = dig(a % 32) + result
        a = a // 32

    return result

if __name__ == "__main__":
    a32 = sys.argv[1]
    b32 = sys.argv[2]

    a10 = convert_10(a32)
    b10 = convert_10(b32)
    r = (a10 * a10) - (b10 * b10)

    print(f"{a32}^2 - {b32}^2 == {r}  {convert_32(r)}")
