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

## Managing Collections of Custom Objects

```cpp
struct Hotmod
{
	string Name;
	string Description;
	
	void Show(){
		string isEnabledText = IsEnabled() ? "ON" : "OFF";
		printf("\nHOTMOD: %s (%s)\n%s\n", Name, isEnabledText, Description);
	}
	
	bool IsEnabled(){
		double state;
		LT_get_var(Name,&state);
		return state != 0;
	}
};
```

```cpp
class HotmodManager{
public:
	HotmodManager(){
		hodmods.SetAsOwner(true);
		
		Define("deltaTTL", 
			"Get new TTL times every sweep. " + 
			"Allows for variable inter pulse interval protocols, " + 
			"but still requires same total number of TTLs in each sweep.");
			
		Define("BasePerTTL", 
			"baseline subtract each evoked signal from a period just before the TTL");
	}
	
	void List(){
		for (int i=0; i<hodmods.GetSize(); i++){
			Hotmod& hm2 = hodmods.GetAt(i);
			hm2.Show();
		}
	}
	
private:
	Array<Hotmod&> hodmods;
	
	void Define(string name, string description){
		Hotmod *p = new Hotmod();
		p->Name = name;
		p->Description = description;
		hodmods.Add(*p);
	}
};
```
