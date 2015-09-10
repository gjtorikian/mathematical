#!/usr/bin/env rake

require 'bundler/gem_tasks'
require 'rake/testtask'
require 'fileutils'
require 'tmpdir'

LASEM_DIR = File.expand_path(File.join(File.dirname(__FILE__), 'ext', 'mathematical', 'lasem'))
LASEM_SRC_DIR = File.join(LASEM_DIR, 'src')
LASEM_LIB_DIR = File.join(LASEM_SRC_DIR, '.libs')

Rake::TestTask.new do |t|
  t.libs << 'test'
  t.test_files = FileList['test/**/*_test.rb']
  t.verbose = true
end

require 'rake/extensiontask'
spec = Gem::Specification.load('mathematical.gemspec')
Rake::ExtensionTask.new('mathematical', spec) do |ext|
  ext.lib_dir = File.join('lib', 'mathematical')
end

Gem::PackageTask.new(spec)

task :compile => [:set_vars]

Rake::Task[:test].prerequisites

task default: [:test]

desc 'Sets necessary environment variables for dynamically linking Lasem'
task :set_vars do
  ENV['DYLD_LIBRARY_PATH'] = "#{LASEM_LIB_DIR}:#{ENV['DYLD_LIBRARY_PATH']}"
  ENV['LD_LIBRARY_PATH'] = "#{LASEM_LIB_DIR}:#{ENV['LD_LIBRARY_PATH']}"
end

desc 'Copy samples to gh-pages'
task :copy_samples do
  Dir.mktmpdir do |tmp|
    system "cp -r samples #{tmp}"

    system 'git checkout gh-pages'

    system "cp -r #{tmp}/samples ."
  end
end

desc 'Pretty format C code'
task :format do
  puts `astyle --indent=spaces=2 --style=1tbs --keep-one-line-blocks \
        $(ack -n -f --type=cpp --type=cc ext/mathematical/)`
end

desc 'Run a benchmark'
task :benchmark do
  $:.unshift 'lib'
  load 'script/benchmark.rb'
end
