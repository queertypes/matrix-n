from os.path import join as path_join
from os.path import basename as basename
from os import listdir as os_listdir
APPNAME = 'Matrix N'
VERSION = '0.9'

AMD_OPENCL_PATH = '/opt/AMDAPP/include'
NEEDED_TR1_LIBS = frozenset(['random', 'numeric',
                             'chrono', 'functional'])
FAST_TEST_FLAGS = '-Wall -Wextra -march=native -O3 -std=c++0x -fwhole-program -fopenmp'
TEST_FLAGS = '-Wall -Wextra -gdwarf-4 -fvar-tracking-assignments -O0 -fno-inline -std=c++0x'
CXX_FLAGS = '-Wall -Wextra -pedantic -ansi -O2 -std=c++0x -g'

def contains(haystack, needle):
  return haystack.count(needle) > 0

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
              cxxflags=CXX_FLAGS)

  for test in os_listdir('tests'):
    libs = ['gtest']

    if contains(test, 'gsl'):
      libs += ['gsl', 'gslcblas']

    if contains(test, 'slater'):
      libs += ['gsl', 'gslcblas']

    bld.program(source=path_join('tests', test),
                cxxflags=TEST_FLAGS,
                includes='include',
                libpath='../lib',
                lib=libs,
                target=path_join('tests', test.replace('.cpp','')))
