# Interfaces in C#
* An interface is like an abstract base class with only abstract members. 
  * it contains no implementation of methods.
  * it can't be instantiated directly.
* Any class or struct that implements the interface must implement all its members.
* By using interfaces you can include behavior from multiple sources
* Use an interface if you want to simulate inheritance for structs

A class or struct can implement multiple interfaces. A class can inherit a base class and also implement one or more interfaces.

```cs
interface IEquatable<T>
{
    bool Equals(T obj);
}

interface ICoolness
{
    bool isCool();
}
```

```cs
public class Car : IEquatable<Car>, ICoolness
{
    public string Make {get; set;}
    public string Model { get; set; }
    public string Year { get; set; }

    public bool Equals(Car car)
    {
        return this.Make == car.Make &&
               this.Model == car.Model &&
               this.Year == car.Year;
    }
    
    public bool isCool()
    {
        return true;
    }
}
```
