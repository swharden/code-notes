# WPF Notes

## Border with Shading in Center

```xaml
<Grid>
	<Grid.ColumnDefinitions>
		<ColumnDefinition Width="*"/>
		<ColumnDefinition Width="Auto"/>
		<ColumnDefinition Width="*"/>
	</Grid.ColumnDefinitions>
	<Grid.RowDefinitions>
		<RowDefinition Height="*"/>
		<RowDefinition Height="Auto"/>
		<RowDefinition Height="*"/>
	</Grid.RowDefinitions>

	<Border Grid.Row="1" Grid.Column="1" BorderThickness="1" BorderBrush="Black">
		<Border.Effect>
			<DropShadowEffect Color="LightGray"/>
		</Border.Effect>
		<local:AboutControl/>
	</Border>
</Grid>
```
