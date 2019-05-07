# Class Properties

## Streamlined Get
```cs
 class Demo
 {
     public string firstName = "Scott";
     public string lastName = "Harden";
     
     // look how nice this is
     public string fullNameStreamlined => $"{firstName}-{lastName}";
     
     // this does the same thing
     public string fullNameBulky
     {
         get
         {
             return $"{firstName}-{lastName}";
         }
     }
 }
```

## Get and Set
```cs
// Declare a Code property of type string:
public string Code {
   get {
      return code;
   }
   set {
      code = value;
   }
}

// Declare a Name property of type string:
public string Name {
   get {
      return name;
   }
   set {
      name = value;
   }
}

// Declare a Age property of type int:
public int Age { 
   get {
      return age;
   }
   set {
      age = value;
   }
}
```
