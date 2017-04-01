# WebWhir

Welcome to WebWhir!

## Project Overview

WebWhir is designed to become a simple HTML rendering engine (and, perhaps eventually, a fully-fledged web browser). That is, WebWhir will accept HTML files and turn them into rendered "web" pages.

## Project History

I began working on WebWhir in early 2013. Although the early versions of WebWhir were able to render basic HTML documents, for most of the time since then, development has been stagnant. Furthermore, when I first began the project, I was in high school, and had no real sense of how to design a large program such as an HTML rendering engine. 

Therefore, with several more years of experience, I am beginning a complete rewrite of WebWhir, which is what you will find on the `master` branch. Of course, if you are interested in seeing the legacy versions of WebWhir, the `0.1.0` and `0.2.0` tags and releases are still accessible.

## Rewrite Roadmap

The philosophy of the rewrite is to get the necessary skeletal structure into place to demonstrate how other cases will be handled. For example, in the [HTML tokenizer](src/HTMLParser/HTMLTokenizer.cpp), there are well over 30 possible states that the tokenizer state machine can enter (as defined in the [specification](https://www.w3.org/TR/2011/WD-html5-20110113/parsing.html)). The current implementation of the tokenizer only handles the few of these that were necessary to parse simple and well-formatted strings. This choice was made to allow development of as many pieces of the final program as quickly as possible, rather than spending significant amounts of time handling countless edge cases. Of course, as time goes on, more and more of these edge cases will be implemented.

In this sense, the basic framework of the new parser is now complete.

Now that the beginnings of the parser are finished, work is now shifting to writing a painter which will actually display the parsed HTML.

## Contributing

Additional contributors would be appreciated! Please see the [contributing guide](CONTRIBUTING.md) for more information.
