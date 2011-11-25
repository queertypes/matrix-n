from os.path import join as path_join
from os.path import basename as basename
from os import listdir as os_listdir
APPNAME = 'fast-slater-determinant'
VERSION = '0.1'

AMD_OPENCL_PATH = '/opt/AMDAPP/include'
NEEDED_TR1_LIBS = frozenset(['random', 'numeric',
                             'chrono', 'functional'])

def options(opt):
  opt.load('compiler_cxx waf_unit_test')

def try_file(ctx, file_name, 
             is_mandatory=False):
  feature_name = basename(file_name).replace('.cpp', '')
  def_name = ('HAS_' + feature_name.upper())
  feature_msg = feature_name
  data = ""
  with open(file_name, "r") as f:
    data = f.readlines()
  return ctx.check_cxx(fragment=''.join(data), define_name=def_name,
                       msg = '  ' + feature_msg,
                       cxxflags='-std=c++0x', 
                       mandatory=is_mandatory)

def configure(cfg):
  path = path_join(cfg.path.abspath(), 'config_tests')

  cfg.load('compiler_cxx waf_unit_test')

  cfg.define('FSD_VERSION', VERSION)

  # mandatory libraries
  cfg.check_cxx(lib='gsl', errmsg='Download and install GNU Scientific Library.')
  cfg.check_cxx(lib='gslcblas', errmsg='Download and install GNU Scientific Library.')
  print

  # check for c++-tr1 libraries
  print('==Checking for c++-tr1 headers ==')
  [cfg.check_cxx(header_name=x, msg='  ' + x, 
                 cxxflags='-std=c++0x', 
                 define_name='HAS_' + x.upper()) for x in NEEDED_TR1_LIBS]
  print

  print('== Checking for c++ steady clock definition ==')
  if try_file(cfg, path_join(path, 'clock_tests', 'steady_clock.cpp')) is None:
    try_file(cfg, path_join(path, 'clock_tests', 'monotonic_clock.cpp'), 
             is_mandatory=True)
  print

  # optional libraries
  cfg.check_cxx(header_name='CL/cl.h', 
                includes=AMD_OPENCL_PATH,
                mandatory=False, define_name='HAS_OPENCL',
                msg='Checking for OpenCL')
  print

  # check for c++11 features
  print('== Checking for c++11 features ==')
  [try_file(cfg,path_join(path,x)) for x in os_listdir(path) if x.endswith('.cpp')]
  print
  
  cfg.write_config_header('../include/config.h')
  print('Wrote configuration to include/config.h')

def build(bld):
  bld.program(source='src/fast-slater.cpp',
              includes='include',
              target='fast-slater',
              cxxflags='-Wall -Wextra -pedantic -ansi -std=c++0x -g -O2')

  from waflib.Tools import waf_unit_test
  bld.add_post_fun(waf_unit_test.summary)

  for test in os_listdir('tests'):
    bld.program(source=path_join('tests', test),
                features='test',
                cxxflags='-Wall -Wextra -O2 -g -std=c++0x',
                includes='include',
                libpath='../lib',
                lib='gtest',
                target=path_join('tests', test.replace('.cpp','')))
