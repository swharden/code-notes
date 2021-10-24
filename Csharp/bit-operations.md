# Bit Flipping in C#

### Reading, Writing, and Flipping bits in C
```C
y = (x>>n)&1;    // stores nth bit of x in y.  y becomes 0 or 1.
x&=~(1<<n);      // forces nth bit of x to be 0.  all other bits left alone.
x&=(1<<(n+1))-1; // leaves lowest n bits of x; all higher bits set to 0.
x|=(1<<n);       // forces nth bit of x to be 1.  all other bits left alone.
x^=(1<<n);       // toggles nth bit of x.  all other bits left alone.
x=~x;            // toggles ALL the bits in x.
```

### Reverse the Bits in a Byte
```CS
/// <summary>
/// return a byte with all of its bits in reverse order
/// </summary>
public static byte ReverseBits(byte b1)
{
    byte b2 = 0;
    for (int i=0; i<8; i++)
    {
        b2 += (byte)(((b1 >> i) & 1) << 7 - i);
    }
    return b2;
}
```

### Split a long number into multiple bytes
```CS
bytesToSend.Add(ReverseBits((byte)((freqCode >> 00) & 0xFF))); // 1 LSB
bytesToSend.Add(ReverseBits((byte)((freqCode >> 08) & 0xFF))); // 2
bytesToSend.Add(ReverseBits((byte)((freqCode >> 16) & 0xFF))); // 3
bytesToSend.Add(ReverseBits((byte)((freqCode >> 24) & 0xFF))); // 4 MSB
```
