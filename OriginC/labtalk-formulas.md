# Labtalk Formulas
You can put labtalk in the `f(x)` row of columns:

```php
A$==B$?"MATCH":"DIFF"
Substitute("testSCOTTtest", "_", "SCOTT", 0)$;
Find(A$, "p")
Left(A$, Find(A$, "p"))
Left(A$, Find(A$, "p"))$==Left(B$, Find(B$, "p"))$?"MATCH":"DIFF"
TEXT(Left(A$, Find(A$, "p")))==TEXT(Left(B$, Find(B$, "p")))?"MATCH":"DIFF"
```
