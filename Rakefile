#!/usr/bin/env rake

require 'bundler/gem_tasks'
require 'rake/testtask'
require 'rubocop/rake_task'
require 'rbconfig'
require 'fileutils'
require 'tmpdir'

Rake::TestTask.new do |t|
  t.libs << 'test'
  t.test_files = FileList['test/**/*_test.rb']
  t.verbose = true
end

RuboCop::RakeTask.new

require 'rake/extensiontask'
spec = Gem::Specification.load('mathematical.gemspec')
Rake::ExtensionTask.new('mathematical', spec) do |ext|
  ext.lib_dir = File.join('lib', 'mathematical')
end

Gem::PackageTask.new(spec)

Rake::Task['compile'].enhance do
  Rake::Task['destroy_copies'].invoke
end

Rake::Task[:test].prerequisites << :compile

task default: [:test]

desc 'Copy samples to gh-pages'
task :copy_samples do
  Dir.mktmpdir do |tmp|
    system "cp -r samples #{tmp}"

    system 'git checkout gh-pages'

    system "cp -r #{tmp}/samples ."
  end
end

task :destroy_copies do
  ext_dir = File.join(File.dirname(__FILE__), 'ext', 'mathematical')
  Dir.glob("#{ext_dir}/*").select { |f| File.file?(f) }.each do |f|
    next if f =~ /extconf.rb$/ || f =~ /mathematical.c$/
    File.delete(f)
  end
  Dir.glob("#{ext_dir}/{lib,src,test,ext,deps,uthash}").select { |d| FileUtils.rm_rf d }
end

desc 'Pretty format C code'
task :format do
  puts `astyle --indent=spaces=2 --style=1tbs --keep-one-line-blocks \
        $(ack -f --type=cpp --type=cc ext/mathematical/mathematical.c)`
end
