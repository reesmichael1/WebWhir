# WebWhir

Welcome to WebWhir!

## Project Overview

WebWhir is designed to become a simple HTML rendering engine (and, perhaps eventually, a fully-fledged web browser). That is, WebWhir will accept HTML files and turn them into rendered "web" pages.

## Project History

I began working on WebWhir in early 2013. Although the early versions of WebWhir were able to render basic HTML documents, for most of the time since then, development has been stagnant. Furthermore, when I first began the project, I was in high school, and had no real sense of how to design a large program such as an HTML rendering engine. 

Therefore, with several more years of experience, I am beginning a complete rewrite of WebWhir, which is what you will find on the `master` branch. Of course, if you are interested in seeing the legacy versions of WebWhir, the `0.1.0` and `0.2.0` tags and releases are still accessible.

## Rewrite Roadmap

The first step will be to reconstruct a parser. The original parser was entirely designed by myself, and, although it worked surprisingly well, had no sense of how to handle malformed HTML, and became so complicated that it was exceedingly difficult to maintain. To avoid this happening again, the new parser will follow the W3C guidelines for [parsing HTML documents](https://www.w3.org/TR/2011/WD-html5-20110113/parsing.html). This parser is well underway.

After completing a basic parser, I will then start to write a new painter, which will actually display the parsed HTML. The original version of WebWhir used Qt, but I will carefully consider what graphics library to use this time around.
