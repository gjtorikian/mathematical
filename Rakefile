#!/usr/bin/env rake
require "bundler/gem_tasks"
require 'rake/testtask'
require 'rbconfig'
require 'fileutils'

Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList['test/**/*_test.rb']
  t.verbose = true
end

require 'rake/extensiontask'
spec = Gem::Specification.load('mathematical.gemspec')
Rake::ExtensionTask.new('mathematical', spec) do |ext|
  ext.lib_dir = File.join('lib', 'mathematical')
end

Gem::PackageTask.new(spec) do |pkg|
end

Rake::Task[:test].prerequisites << :compile

task :default => [:test]
