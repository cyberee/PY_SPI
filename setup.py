from distutils.core import setup, Extension
setup(name= 'PY_Spi',
      version = '0.0.2',
      ext_modules = [Extension('PY_Spi',["PY_Spi.c","PI_SPI.c"])])
