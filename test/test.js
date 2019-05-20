const gdx = require('../index.js')
const assert = require('assert')

const expected = {
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

// check if correct JSON is read
gdx.read('test/test.gdx')
  .then(data => {
    assert.deepEqual(data,expected)
  })
  .catch(e => {
    console.error(e);
  })