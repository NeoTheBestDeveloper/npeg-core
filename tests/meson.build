cc = meson.get_compiler('c')
criterion = cc.find_library('criterion', required: true)
npeg_core = shared_library('npeg-core', npeg_sources, include_directories: includedir, dependencies: [math_dep, thread_dep])


test_img_read = executable('test_img_read', 'test_img_read.c', 
  include_directories: includedir, 
  dependencies: [criterion], link_with: npeg_core)
test('Test img reading.', test_img_read)

test_img_rotate = executable('test_img_rotate', 'test_img_rotate.c', 
  include_directories: includedir, 
  dependencies: [criterion], link_with: npeg_core)
test('Test img rotating.', test_img_rotate)

