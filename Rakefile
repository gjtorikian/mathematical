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

task :default => [:test]

namespace :git do
  namespace :submodules do
    desc "Initialize git submodules"
    task :init do
      system "git submodule init"
      system "git submodule update"
    end
  end
end

task :makebin do
  host_os = RbConfig::CONFIG['host_os']
  Dir.chdir "ext/blahtexml" do
    case host_os
    # when /mswin|msys|mingw|cygwin|bccwin|wince|emc/
    #   :windows
    when /darwin|mac os/
      `make blahtex-mac`
      FileUtils.mkdir_p "../../bin/blahtex/macosx/"
      FileUtils.cp "blahtex", "../../bin/blahtex/macosx/"
    when /linux/
      `make blahtex-linux`
      FileUtils.mkdir_p "../../bin/blahtex/linux/"
      FileUtils.cp "blahtex", "../../bin/blahtex/linux/"
    # when /solaris|bsd/
      # :unix
    else
      raise Error, "unknown os: #{host_os.inspect}"
    end
  end
end
