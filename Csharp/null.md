### Inline null-check (null coalescing operator)
```cs
// manual way
if (lineStyle == null)
  this.lineStyle = new Styles.Line();
else
  this.lineStyle = lineStyle;

// inline if statement
this.lineStyle = (lineStyle == null) ? new Styles.Line() : lineStyle;

// null coalescing operator
this.lineStyle = lineStyle ?? new Styles.Line();
```