#!/usr/bin/env rake
require "bundler/gem_tasks"
require 'rake/testtask'
require 'rbconfig'
require 'fileutils'
require 'tmpdir'

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

Rake::Task["compile"].enhance do
  Rake::Task["destroy_copies"].invoke
end

Rake::Task[:test].prerequisites << :compile

task :default => [:test]

desc "Publish gh-pages content"
task :publish do
  Dir.mktmpdir do |tmp|
    system "cp samples/quality/* #{tmp}"

    system "git checkout gh-pages"

    index = File.read("index.html")

    i = 1
    Dir.glob("#{tmp}/*.svg") do |item|
      svg = File.read(item)
      index = index.sub /&sample#{i};/, svg
      i += 1
    end

    File.open("index.html", 'w') { |file| file.write(index) }
  end
end

task :destroy_copies do
  ext_dir = File.join(File.dirname(__FILE__), "ext", "mathematical")
  Dir.glob("#{ext_dir}/*").select { |f| File.file?(f) }.each do |f|
    next if f =~ /extconf.rb/ || f =~ /mathematical.c/
    File.delete(f)
  end
  Dir.glob("#{ext_dir}/{lib,src,test,ext}").select { |d| FileUtils.rm_rf d }
end
