require 'mkmf'

extension_name = 'mathematical'

dir_config(extension_name)

with_cflags("-DAA -DPLUSNOTBLANK -DNOSMASH") do
  create_makefile(extension_name)
end
