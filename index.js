const gdx = require('node-gyp-build')(__dirname)

module.exports = {
  read(path,symbol) {
    if (symbol) return gdx.read(__dirname + '/dll', path, symbol)
    else return gdx.read(__dirname + '/dll', path)
  }
}
