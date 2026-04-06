#!/usr/bin/env rake
# frozen_string_literal: true

require "bundler/gem_tasks"
require "rake/testtask"
require "fileutils"
require "tmpdir"

Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList["test/**/*_test.rb"]
  t.verbose = true
end

# ─── Extension compilation ─────────────────────────────────────────────────────

require "rake/extensiontask"

CROSS_PLATFORMS = %w[
  x86_64-linux-gnu
  x86_64-linux-musl
  aarch64-linux-gnu
  aarch64-linux-musl
]

NATIVE_PLATFORMS = %w[
  arm64-darwin
  x86_64-darwin
  x64-mingw-ucrt
]

ALL_PLATFORMS = CROSS_PLATFORMS + NATIVE_PLATFORMS

# Ruby versions to target for precompiled gems
CROSS_RUBIES = %w[3.1.0 3.2.0 3.3.0 3.4.0]

spec = Gem::Specification.load("mathematical.gemspec")

Rake::ExtensionTask.new("mathematical", spec) do |ext|
  ext.lib_dir = File.join("lib", "mathematical")
  ext.cross_compile = true
  ext.cross_platform = CROSS_PLATFORMS
  ext.cross_config_options << "--enable-cross-build"

  ext.cross_compiling do |cross_spec|
    # Native gems don't need source files — the compiled .so is included
    cross_spec.files.reject! { |path| File.fnmatch?("ext/**/*", path) }
    # Include font files in native gems
    cross_spec.files += Dir.glob("fonts/**/*")
  end
end

# Set RUBY_CC_VERSION for cross-compilation
begin
  require "rake_compiler_dock"
  ENV["RUBY_CC_VERSION"] = RakeCompilerDock.ruby_cc_version("3.1", "3.2", "3.3", "3.4")
rescue LoadError
  ENV["RUBY_CC_VERSION"] = CROSS_RUBIES.join(":")
end

# ─── Cross-compiled gem tasks (Linux via rake-compiler-dock) ───────────────────

namespace "gem" do
  CROSS_PLATFORMS.each do |platform|
    desc "Build native gem for #{platform}"
    task platform do
      require "rake_compiler_dock"

      # Determine which package manager and deps to install
      install_cmd = if platform.include?("musl")
        <<~SH
          apk add --no-cache \
            build-base cmake bison flex pkgconf meson ninja python3 py3-pip \
            glib-dev glib-static cairo-dev cairo-static \
            pango-dev gdk-pixbuf-dev libxml2-dev libxml2-static \
            harfbuzz-dev harfbuzz-static fribidi-dev fribidi-static \
            fontconfig-dev fontconfig-static freetype-dev freetype-static \
            pixman-dev pixman-static libffi-dev libpng-dev libpng-static \
            zlib-dev zlib-static jpeg-dev expat-dev expat-static \
            pcre2-dev
        SH
      else
        <<~SH
          apt-get update -qq && apt-get install -y --no-install-recommends \
            cmake bison flex pkg-config meson ninja-build python3 python3-pip \
            libffi-dev libxml2-dev libgdk-pixbuf2.0-dev libcairo2-dev \
            libpango1.0-dev libwebp-dev libglib2.0-dev
        SH
      end

      RakeCompilerDock.sh(<<~SCRIPT, platform: platform, verbose: true)
        set -e
        #{install_cmd}
        # On GNU Linux, build static deps from source (Debian lacks .a files)
        #{"script/build_static_deps" unless platform.include?("musl")}
        gem install bundler --no-document
        bundle install
        bundle exec rake native:#{platform} gem MAKE="nice make -j$(nproc)"
      SCRIPT
    end
  end

  desc "Build native gems for all Linux platforms"
  multitask linux: CROSS_PLATFORMS

  desc "Build the source (platform=ruby) gem"
  task :source do
    sh "gem build mathematical.gemspec"
  end
end

# ─── Default tasks ─────────────────────────────────────────────────────────────

task default: [:test]

Gem::PackageTask.new(spec)

Rake::Task[:test].prerequisites

task build: [:clean]

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
