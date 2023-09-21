const { join } = require('path')
const os = require('os')
const { existsSync } = require('fs')
const gdx = require('node-gyp-build')(__dirname)

module.exports = (options = {}) => {
  let defaultDllPath = join(__dirname, 'dll', os.platform() + '-' + os.arch())
  if (!existsSync(defaultDllPath) && !options.gamsPath) {
    throw new Error('Could not find GAMS DLL. Please specify the path to the GAMS DLL.')
  }
  const {
    gamsPath = options.gamsPath || defaultDllPath
  } = options

  return {
    read(path, symbol) {
      if (symbol) return gdx.read(gamsPath, path, symbol)
      else return gdx.read(gamsPath, path)
    }
  }
}