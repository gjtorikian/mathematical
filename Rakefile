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

Rake::Task[:test].prerequisites << :compile

task :default => [:test]

desc "Generate and publish to gh-pages"
task :publish do
  Dir.mktmpdir do |tmp|
    system "cp test/mathematical/fixtures/after/* #{tmp}"
    system "cp README.md #{tmp}"
    system "git checkout gh-pages"
    # system "rm -rf *"
    system "mv #{tmp}/* ."
    message = "Site updated at #{Time.now.utc}"
    system "git add ."
    system "git commit -am #{message.shellescape}"
    system "git push origin gh-pages --force"
    system "git checkout master"
    system "echo yolo"
  end
end
