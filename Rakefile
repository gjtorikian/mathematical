#!/usr/bin/env rake
# frozen_string_literal: true

require "bundler/gem_tasks"
require "rake/testtask"
require "fileutils"
require "tmpdir"

LASEM_DIR = File.expand_path(File.join(File.dirname(__FILE__), "ext", "mathematical", "lasem"))

Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList["test/**/*_test.rb"]
  t.verbose = true
end

require "rake/extensiontask"
spec = Gem::Specification.load("mathematical.gemspec")
Rake::ExtensionTask.new("mathematical", spec) do |ext|
  ext.lib_dir = File.join("lib", "mathematical")
end

task default: [:test]

Gem::PackageTask.new(spec)

Rake::Task[:test].prerequisites

task build: [:clean]

Rake::Task[:clean].enhance do
  Dir.chdir(LASEM_DIR) { puts %x(git clean -fdx) }
end

desc "Copy samples to gh-pages"
task :copy_samples do
  Dir.mktmpdir do |tmp|
    system "cp -r samples #{tmp}"

    system "git checkout gh-pages"

    system "cp -r #{tmp}/samples ."
  end
end

require "rubocop/rake_task"

RuboCop::RakeTask.new

desc "Pretty format C code"
task :format do
  puts %x(astyle --indent=spaces=2 --style=1tbs --keep-one-line-blocks \
        $(ack -n -f --type=cpp --type=cc ext/mathematical/))
end

desc "Run a benchmark"
task :benchmark do
  $LOAD_PATH.unshift("lib")
  load "script/benchmark.rb"
end

GEMSPEC = Bundler.load_gemspec("mathematical.gemspec")
gem_path = Gem::PackageTask.new(GEMSPEC).define
desc "Package the ruby gem"
task "package" => [gem_path]
