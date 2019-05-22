# node-gdx
Read GAMS GDX files in Node.js. Does NOT require a GAMS installation.

## Usage
```js
const gdx = require('node-gdx')

gdx.read('path/to/file.gdx')
  .then(data => {
    /* where data = {
      Demand: [{
          '0': 'New-York',
          Value: 324
        },
        {
          '0': 'Chicago',
          Value: 299
        },
        {
          '0': 'Topeka',
          Value: 274
        }
      ]
    }
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

