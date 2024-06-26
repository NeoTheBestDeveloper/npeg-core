project('npeg-core', 'c',
    version: '0.0.1',
    default_options: [
            'warning_level=3',
            'c_std=c17',
            'buildtype=debug',
            'b_sanitize=address,undefined',
            'b_lundef=false',
            'b_lto=true',
        ]
)

subdir('src')
includedir = include_directories('include')

cc = meson.get_compiler('c')
warning_flags = [
                '-Wfloat-equal',
                '-Wundef',
                '-Wshadow',
                '-Wpointer-arith',
                '-Wcast-align',
                '-Wwrite-strings',
                '-Wcast-qual',
                '-Wswitch-default',
                '-Wswitch-enum',
                '-Wconversion',
                '-Wformat=2',
                '-Wpedantic',
                '-Wformat-security',
                '-Wtype-limits',
                '-Wunused-result',
                '-Wvariadic-macros',
                '-Wno-format-extra-args',
                '-Wno-missing-prototypes',
                '-Wno-padded',
                '-Wno-missing-declarations',
                '-Wno-unused-function',
                '-Wno-declaration-after-statement',
]

avx_flags = []

if get_option ('buildtype').startswith('debug') 
  add_project_arguments('-DDEBUG', language: 'c')
endif

add_project_arguments(cc.get_supported_arguments(warning_flags), language: 'c') 
add_project_arguments(cc.get_supported_arguments(avx_flags), language: 'c')

math_dep = cc.find_library('m', required: true) 

if meson.is_cross_build() 
  thread_dep = cc.find_library('winpthread', static: true)
else 
  thread_dep = dependency('threads')
endif

npeg_core = both_libraries('npeg-core', npeg_sources, 
  include_directories: includedir, 
  dependencies: [math_dep, thread_dep],
)


if get_option('buildtype').startswith('debug')
  subdir('tests') 
endif
