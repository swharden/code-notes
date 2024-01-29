# Rich Textbox

See [rtf.md](rtf.md) for formatting details

## Automatically scroll to the bottom
```cs
private void richTextBox_TextChanged(object sender, EventArgs e) {
      richTextBox1.SelectionStart = richTextBox1.Text.Length; // place the caret
      richTextBox1.ScrollToCaret(); // scroll to the caret
}
```

## Rich Text Formatting
```cs
richTextBox1.Rtf = @"{\rtf1\ansi This is in \b bold\b0.}";
```
