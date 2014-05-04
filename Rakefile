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
    titles_to_content = {}
    Dir.glob("#{tmp}/compliance_*.html") do |item|
      titles_to_content[File.basename(item)] = File.read(item)
    end

    system "git checkout gh-pages"

    li_listing = titles_to_content.keys.map { |title| "<li><a href='#{title}'>#{File.basename(title, File.extname(title))}</a></li>" }
    index = File.read("index.html")
    File.open("index.html", 'w') { |file| file.write(index.sub(/<!-- LIST_GOES_HERE -->/, li_listing.join("\n"))) }

    layout = File.read("layout_shell.text")
    titles_to_content.each do |title, content|
      new_layout = layout.sub(/<!-- TITLE_GOES_HERE -->/, title)
      new_layout = new_layout.sub(/<!-- CONTENT_GOES_HERE -->/, content)
      File.open("#{title}", 'w') { |file| file.write(content) }
    end

    # system "rm -rf *"
    # system "mv #{tmp}/* ."
    message = "Site updated at #{Time.now.utc}"
    # system "git add ."
    # system "git commit -am #{message.shellescape}"
    # system "git push origin gh-pages --force"
    # system "git checkout master"
    # system "echo yolo"
  end
end
