const readGDX = require('../index.js')

readGDX('demanddata.gdx')
.then(data => {
  console.log(data)
})