from setuptools import setup, Extension

module = Extension('spam', sources=['spam_module.c'])

setup(name = 'spam', 
      version = '1.0',
      description = "An interface for the C System command",
      ext_modules = [module]
      )




