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

void structDemo(){
	KnownAbf abf;
	abf.strPath = "test path";
	abf.strGuid = "test guid";
	Display(abf);
}
```
