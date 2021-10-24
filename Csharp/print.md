# Printing in WinForms

```cs
private void PrintPage(object sender, PrintPageEventArgs e)
{
	formsPlot1.plt.Resize(e.MarginBounds.Width, (int)(e.MarginBounds.Width * .5));
	formsPlot1.plt.Style(figBg: Color.White);
	e.Graphics.DrawImage(formsPlot1.plt.GetBitmap(), e.MarginBounds.Left, e.MarginBounds.Top);
}

private void Print_Click(object sender, EventArgs e)
{
	var pd = new PrintDocument();
	pd.PrintPage += new PrintPageEventHandler(PrintPage);
	if (new PrintDialog { Document = pd }.ShowDialog() == DialogResult.OK)
		pd.Print();
}

private void PrintPreview_Click(object sender, EventArgs e)
{
	var pd = new PrintDocument();
	pd.PrintPage += new PrintPageEventHandler(PrintPage);
	new PrintPreviewDialog { Document = pd }.ShowDialog();
}
```
