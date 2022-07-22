# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys

sys.path.insert(0, os.path.abspath('.'))
sys.path.insert(0, os.path.abspath('./figures'))
sys.path.insert(0, os.path.abspath('./exts')) # needed for fibre_autodoc extension
# sys.path.insert(0, os.path.abspath('../tools/fibre-tools')) # needed for fibre_autodoc extension


# -- Project information -----------------------------------------------------

project = 'X1 Controller Documentation'
copyright = '2022, Precision Robotics'
author = 'Precision Robotics'

# The full version, including alpha/beta/rc tags
release = '0.1'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = ['sphinx_tabs.tabs',
    'sphinx_copybutton', # copy button for code blocks
    'sphinx_panels',    # dropdown directive
    'sphinx_rtd_theme', # read the docs theme
    'sphinx.ext.autodoc', # Generate documentation from Python modules
    'sphinx.ext.autosummary', # Generate summary tables for Python documentation
    'sphinx.ext.intersphinx', # Hyperlinks to external projects (such as Python standard library)
    # 'fibre_autodoc', # Generate summary tables for Python documentation
    'myst_parser' # render CHANGELOG markdown file
    
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
# html_theme = 'alabaster'
html_theme = "sphinx_rtd_theme"

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

autosummary_generate = False

intersphinx_mapping = {'python': ('https://docs.python.org/3', None)}
