# WPF DataTable Quickstart

```cs
<DataGrid x:Name="dataGrid1" Grid.Row="0" Margin="0, 0, 0, 5" 
		  CanUserAddRows="False" 
		  AutoGenerateColumns="False" 
		  IsReadOnly="True" 
		  RowHeaderWidth="0"
		  SelectionMode="Single"
		  SelectionUnit="FullRow"
		  >
      
	<DataGrid.Columns>
		<DataGridTextColumn Header="Ion" Width="*" Binding="{Binding nameWithCharge}" />
		<DataGridTextColumn Header="Mobility" Width="*" Binding="{Binding mu, StringFormat=E4}" />
		<DataGridTextColumn Header="C0 (mM)" Width="*" Binding="{Binding c0}" />
		<DataGridTextColumn Header="CL (mM)" Width="*" Binding="{Binding cL}" />
	</DataGrid.Columns>

	<!-- prevent selected cell from having a bold outline -->
	<DataGrid.Resources>
		<Style TargetType="{x:Type DataGridCell}">
			<Setter Property="BorderThickness" Value="0" />
			<Setter Property="FocusVisualStyle" Value="{x:Null}" />
		</Style>
	</DataGrid.Resources>
	
</DataGrid>
```
