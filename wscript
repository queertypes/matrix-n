def options(opt):
  opt.load('compiler_cxx waf_unit_test')

def configure(cfg):
  cfg.load('compiler_cxx waf_unit_test')

def build(bld):
  bld.program(source='src/fast-slater.cpp',
              includes='include',
              target='fast-slater',
              cxxflags='-Wall -Wextra -pedantic -ansi -std=c++0x -g -O2')
              
