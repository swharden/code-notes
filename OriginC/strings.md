# strings

## Float Formatting
Unlike Python, `%03.4f` doesn't cause three zero-padded left characters...

```c
char demo[50];
sprintf(demo,"%.4f",1.23456789);
out_str(demo);
// 1.2346
```

## Trim Whitespace
```c
str.TrimLeft();
str.TrimRight();
```
