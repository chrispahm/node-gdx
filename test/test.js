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

// check if parameter is read correctly
gdx.read('test/test.gdx', 'Demand')
.then(data => {
  assert.deepEqual(data,expected.Demand)
}).catch(e => {
  console.error(e)
})

// should fail since the symbol is not in the gdx
gdx.read('test/test.gdx', 'NotAvailable')
.then(data => {
  //
}).catch(e => {
  assert.deepStrictEqual(e.message,"Could not find symbol.");
})

// should fail since file is not available
gdx.read('notFound.gdx')
.then(data => {
  //
}).catch(e => {
  assert.deepStrictEqual(e.message,"Failed to open GDX");
})
