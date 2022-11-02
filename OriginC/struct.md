# OriginC struct

```cs
struct KnownAbf
{
	string strPath;
	string strGuid;
};

void Display(KnownAbf abf){
	printf("%s\n", abf.strPath);
	printf("%s\n", abf.strGuid);
}

KnownAbf GetDemoStruct(){
	KnownAbf abf;
	abf.strPath = "test path";
	abf.strGuid = "test guid";
	return abf;
}

void structDemo(){
	KnownAbf &abf = GetDemoStruct();
	Display(abf);
}
```
