# OriginC Classes

```c
#include <Origin.h>
```

```c
class Animal {
  public:
  	int age;
  	string species;
  	
  	void SayHi(){
  		printf("I am a %s and my age is %d\n", species, age);
  	}
  	
  private:
	void Animal(){
		age = 0;
		species = "generic animal";
	}
};
```

```c
class Dog : public Animal {
public:
	void WagTail(){
  		printf("I can wag my tail");
	}
private:
	Dog(){
		species = "dog";
		age = 5;
	}
};
```

---

```
void RunClassTests(){
	Animal myAnimal;
	myAnimal.SayHi();
	
	Dog myDog;
	myDog.SayHi();
	myDog.WagTail();
}
```

```
>>runclasstests
I am a generic animal and my age is 0
I am a dog and my age is 5
I can wag my tail
```
