criterion = dependency('criterion', required: false)
if not criterion.found()
	criterion_proj = subproject('criterion')
    libcriterion = criterion_proj.get_variable('libcriterion')
    deps = criterion_proj.get_variable('deps')
    criterion_api = criterion_proj.get_variable('criterion_api')

    criterion = declare_dependency(
        include_directories: [criterion_api],
        dependencies: deps,
        link_with: [libcriterion.get_static_lib()])
endif

test_img_read = executable('test_img_read', 'test_img_read.c',
                include_directories: includedir,  
                link_with: [npeg_core.get_static_lib()],
                dependencies: criterion,
)
test('Test img reading.', test_img_read, suite: 'npeg-core')

test_img_rotate = executable('test_img_rotate', 'test_img_rotate.c', 
                  include_directories: includedir,
                link_with: [npeg_core.get_static_lib() ],
                dependencies: criterion,
)
test('Test img rotating.', test_img_rotate, suite: 'npeg-core')

test_matrix = executable('test_matrix', 'test_matrix.c', 
                  include_directories: includedir,
                link_with: [npeg_core.get_static_lib()],
                dependencies: criterion,
)
test('Test matrix', test_img_rotate, suite: 'npeg-core')
