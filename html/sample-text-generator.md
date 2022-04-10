# Generate Sample Text with JavaScript

Drop this anywhere on a page to write 500 words of _lorem ipsum_ in random order

```js
<script>
    var words = "lorem ipsum dolor sit amet consectetur adipiscing elit".split(" ");
    var text = [];
    for (let i = 0; i < 500; i++)
        text.push(words[Math.floor(Math.random() * words.length)]);
    document.write(text.join(" "))
</script>
```
