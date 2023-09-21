const { join } = require('path')
const os = require('os')
const { existsSync } = require('fs')
const gdx = require('node-gyp-build')(__dirname)

module.exports = (options = {}) => {
  let defaultDllPath = join(__dirname, 'dll', os.platform() + '-' + os.arch())
  let defaultDLLExists = existsSync(defaultDllPath)

  const {
    gamsPath = options.gamsPath || defaultDllPath
  } = options

  return {
    read(path, symbol, overrideDllPath) {
      if (!defaultDLLExists && !options.gamsPath && !overrideDllPath) {
        throw new Error('Could not find GAMS DLL. Please specify the path to the GAMS DLL.')
      }

      if (symbol) return gdx.read(overrideDllPath || gamsPath, path, symbol)
      else return gdx.read(overrideDllPath || gamsPath, path)
    }
  }
}