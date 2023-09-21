# node-gdx
Read GAMS GDX files in Node.js. Does NOT require a GAMS installation for macOS & Windows systems.

## Installation
```
npm i node-gdx
```

## Usage
```js
const gdx = require('node-gdx')({
  gamsPath: "/path/to/gams/installation" // this is optional for macOS & Windows!
})

// read a whole gdx file
gdx.read('path/to/file.gdx')
  .then(data => {
    /* where data = {
      Demand: [{
          '0': 'New-York',
          Value: 324
        },
        ...
      ]
    }
    */
  })
  .catch(e => {
    console.error(e)
  })
  
// read a single symbol
gdx.read('path/to/file.gdx', 'Demand')
  .then(data => {
    /* where data = [{
          '0': 'New-York',
          Value: 324
        },
        ...
      ]
    */
  })
  .catch(e => {
    console.error(e)
  })
```

## API
### read(file: string, *symbol: string*)

Read a GDX file from disk. Returns all symbols in the GDX container by default,
unless otherwise specified by the optional second function argument.

