criterion = dependency('criterion', required: false)
if not criterion.found()
	criterion_proj = subproject('criterion')
    criterion = criterion_proj.get_variable('criterion')
endif

test_img_read = executable('test_img_read', 'test_img_read.c',
                include_directories: includedir,  
                dependencies: criterion,
                link_with: npeg_core,
)
test('Test img reading.', test_img_read, suite: 'npeg-core')

test_img_rotate = executable('test_img_rotate', 'test_img_rotate.c', 
                  include_directories: includedir,
                  dependencies: criterion,
                  link_with: npeg_core,
)
test('Test img rotating.', test_img_rotate, suite: 'npeg-core')
