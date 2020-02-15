## 2D Array in Csharp

```cs
int[,] arr = new int[5, 10];
for (int row = 0; row < arr.GetLength(0); row++)
{
    for (int column = 0; column < arr.GetLength(1); column++)
    {
        int value = (row + 1) * (column + 1);
        arr[row, column] = value;
        Debug.Write($"{value, 3} ");
    }
    Debug.WriteLine("");
}
```

```
  1   2   3   4   5   6   7   8   9  10 
  2   4   6   8  10  12  14  16  18  20 
  3   6   9  12  15  18  21  24  27  30 
  4   8  12  16  20  24  28  32  36  40 
  5  10  15  20  25  30  35  40  45  50 
```
