#!/usr/bin/env rake
require "bundler/gem_tasks"
require 'rake/testtask'

Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList['test/**/*_test.rb']
  t.verbose = true
end

task :default => :test

namespace :git do
  namespace :submodules do
    desc "Initialize git submodules"
    task :init do
      system "git submodule init"
      system "git submodule update"
    end
  end
end
