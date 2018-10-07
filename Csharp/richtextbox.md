# Rich Textbox

## Automatically scroll to the bottom
```cs
private void richTextBox_TextChanged(object sender, EventArgs e) {
      richTextBox1.SelectionStart = richTextBox1.Text.Length; // place the caret
      richTextBox1.ScrollToCaret(); // scroll to the caret
}
```
