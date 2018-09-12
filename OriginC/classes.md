# OriginC Classes

```c
class NuclearMissile{
	private:
		bool launch;
	public:
		NuclearMissile(bool &launch) {}
		
		HaveMeeting(){
			if (launch) {
				out_str("missile launched");
			} else {
				out_str("entering standby mode");
			}
		}
};

void DonaldTrumpSecondTerm(){
	NuclearMissile nuclearOption(false);
	nuclearOption.HaveMeeting();
}
```
