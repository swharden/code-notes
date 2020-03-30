# WPF Data Binding

## Property in a Class

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
