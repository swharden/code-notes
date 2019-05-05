# Abstract Classes in C#

* An abstract class cannot be instantiated.
* Abstract classes provide a common definition of a base class that multiple derived classes can share.
* Abstract classes may also define abstract methods.

## Example 1

```cs
public class D
{
    public virtual void DoWork(int i)
    {
        // Original implementation.
    }
}

public abstract class E : D
{
    public abstract override void DoWork(int i);
}

public class F : E
{
    public override void DoWork(int i)
    {
        // New implementation.
    }
}
```

## Example 2
```cs
abstract class ShapesClass
{
    abstract public int Area();
}

class Square : ShapesClass
{
    int side = 0;

    public Square(int n)
    {
        side = n;
    }
    // Area method is required to avoid
    // a compile-time error.
    public override int Area()
    {
        return side * side;
    }

    static void Main() 
    {
        Square sq = new Square(12);
        Console.WriteLine("Area of the square = {0}", sq.Area());
    }

    interface I
    {
        void M();
    }
    abstract class C : I
    {
        public abstract void M();
    }

}
```

### Sealing Classes and Methods
* A sealed class cannot be used as a base class (or abstract class).
* Sealed classes prevent derivation. 
* They can be slightly faster than regular classes.
* Methods can be sealed too.

```cs
public sealed class D
{
    // Class members here.
}
```

```cs
public class D : C
{
    public sealed override void DoWork() { }
}
```
