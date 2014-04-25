#!/usr/bin/env rake
require "bundler/gem_tasks"
require 'rake/testtask'
require 'rbconfig'
require 'fileutils'
require 'mathematical'

Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList['test/**/*_test.rb']
  t.verbose = true
end

task :default => [:test]

require 'rake/extensiontask'
spec = Gem::Specification.load('mathematical.gemspec')
Rake::ExtensionTask.new('mathematical', spec)

task :single_text do
  text = """
  <html>

  <body>

  #{Mathematical::Render.new.render('\begin{equation}x = {-b \pm \sqrt{b^2-4ac} \over 2a}\end{equation}')}

  </body>


  </html>
  """

  puts text
  File.open("text.html", 'w') { |file| file.write(text) }

  # unless ARGV[0] == "-s"
  #   `open text.html`
  # else
  #   puts File.open("text.html")
  # end
end
