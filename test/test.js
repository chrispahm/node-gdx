const readGDX = require('../index.js')

readGDX()
.then(data => {
  console.log(data)
})
.catch(e => {
  console.error(e);
})