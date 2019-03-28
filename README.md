# node-gdx
Node.js bindings for GAMS GDX containers.

## Purpose
This repository aims to create a native C++ Package for Node.js to allow for reading (and writing) GAMS GDX containers.

## Mockup example usage
```js
const gdx = require('fs')
const gdx = require('node-gdx')

const file = fs.readFileSync('test.gdx')

gdx.read(file,'symbolInGDX')
  .then(data => {
    /* where data = [{
      'domain1': 'exampleString',
      'domain2: 'anotherExample',
      'domainN: 'string',
      'value': 1234 // value always has to be an integer, or NaN
    },
    ...
    ]
    */
  })
```

