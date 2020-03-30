# WPF Data Binding

## Property in a Class - simpler
They key is to set your DataContext to be the view model

```xaml
<Slider x:Name="BaselineSlider1" Maximum="100" Value="{Binding b1, Mode=TwoWay, UpdateSourceTrigger=PropertyChanged}"/>
```

```cs
public class Structures : INotifyPropertyChanged
{
	int _b1 = 13;
	public int b1
	{
		get { return _b1; }
		set { _b1 = value; OnPropertyChanged("b1"); }
	}

	public event PropertyChangedEventHandler PropertyChanged;
	private void OnPropertyChanged(string info)
	{
		PropertyChangedEventHandler handler = PropertyChanged;
		if (handler != null)
		{
			handler(this, new PropertyChangedEventArgs(info));
		}
	}
}
```

```cs
Structures structures = new Structures();
public StructureControl()
{
	InitializeComponent();
	DataContext = structures;
	structures.b1 = 77;
}
```

## Property in a Class - complex

```cs
public class Structures : INotifyPropertyChanged
{
	public Structures() { }

	private int _baselinePixel1;
	public int baselinePixel1
	{
		get { return _baselinePixel1; }
		set
		{
			_baselinePixel1 = value;
			Debug.WriteLine(_baselinePixel1);
			OnPropertyChanged("baselinePixel1");
		}
	}

	public event PropertyChangedEventHandler PropertyChanged;
	private void OnPropertyChanged(string info)
	{
		PropertyChangedEventHandler handler = PropertyChanged;
		if (handler != null)
		{
			handler(this, new PropertyChangedEventArgs(info));
		}
	}
}
``

```cs
InitializeComponent();
BaselineSlider1.SetBinding(
	dp: Slider.ValueProperty,
	binding: new Binding("baselinePixel1")
	{
		Source = structures,
		Mode = BindingMode.TwoWay,
		UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
	}
);
``
