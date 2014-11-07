require 'etc'

config_file = File.join(Dir.home(Etc.getlogin), ".myprojectconfig")
config_file # "/Users/ankit/.myprojectconfig"

p config_file
