# Testing Vanilla JS

```
yarn init
yarn add jest
yarn jest
```

### math.js

```js
function square(a) {
    return a * a;
}

module.exports = square;
```

### math.test.js

```js
const square = require('./math.js');

test('2 squared is 4', () => {
    expect(square(2)).toBe(4);
});
```
