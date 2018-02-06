# Clean Fractions from VScrollBar and HScrollBar Positions

**Default Values**
* `vScrollBar1.Minimum` = 0
* `vScrollBar1.Maximum` = 100
* `vScrollBar1.LargeChange` is 10
* `vScrollBar1.SmallChange` is 1

**With these values**
* Minimum `vScrollBar1.Value` is 0
* Maximum `vScrollBar1.Value` is 91 (!!!)

**The maximum is:**
```C#
vScrollBar1.Maximum - vScrollBar1.LargeChange + 1
```

**The _fractional position_ (from 0.0 to 1.0) is therefore:**
```C#
double frac = 1-((double)vScrollBar1.Value) / (vScrollBar1.Maximum - vScrollBar1.LargeChange + 1);
```

**If considering the "slider" as a window with thickness, the top and the bottom are:**
```C#
double frac_upper = 1-((double)(vScrollBar1.Value)) / vScrollBar1.Maximum;
double frac_lower = 1-((double)(vScrollBar1.Value + vScrollBar1.LargeChange - 1)) / vScrollBar1.Maximum;
```
