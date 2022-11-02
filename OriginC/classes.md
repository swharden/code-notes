# OriginC Classes

## Required Headers

```c
#include <Origin.h>
#include <Array.h>
```

## Classes and Inheritance

```c
class AnimalBase {
public:
  	virtual void MakeSound(){
  		printf("base sound\n");
  	}
};

class AnimalCat : public AnimalBase {
public:
  	void MakeSound(){
  		printf("meow\n");
  	}
};

class AnimalDog : public AnimalBase {
public: 
  	void MakeSound(){
  		printf("woof\n");
  	}
};

class AnimalCow : public AnimalBase {
public: 
  	void MakeSound(){
  		printf("moo\n");
  	}
};
```

## Functions Consume Base Classes

```cs
void KickAnimal(AnimalBase &animal){
	animal.MakeSound();
}

void ScottDemo1(){
	AnimalCat cat;
	AnimalDog dog;
	AnimalCow cow;
	KickAnimal(cat);
	KickAnimal(dog);
	KickAnimal(cow);
}
```

```cs
void KickAnimals(Array<AnimalBase&> &animals){
	for (int i=0; i<animals.GetSize(); i++){
		AnimalBase& animal = animals.GetAt(i);
		animal.MakeSound();
	}
}

void ScottDemo3(){

	AnimalCat cat;
	AnimalDog dog;
	AnimalCow cow;
	
	Array<AnimalBase&> animals;
	animals.Add(cat);
	animals.Add(dog);
	animals.Add(cow);
	
	KickAnimals(animals); 
}
```
