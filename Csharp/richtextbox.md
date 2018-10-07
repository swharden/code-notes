# Rich Textbox

## Automatically scroll to the bottom
```cs
private void richTextBox_TextChanged(object sender, EventArgs e) {
   richTextBox.SelectionStart = richTextBox.Text.Length; // place the caret
   richTextBox.ScrollToCaret(); // scroll to the caret
}
```
