Welcome to OpenWeb!

OpenWeb is a personal project of mine. It came out of the news that my personal favorite browser, Opera, is abandoning my personal favorite rendering engine, Presto. Because of this, I've decided to write my own HTML rendering engine to gain more insight into how these pieces of software work.

OpenWeb will be updated as I complete work. This could be a very short-lived project, or it could grow into a fully featured engine--only time will tell. If it does gain momentum, I'll probably package an interface as well and release a browser.

OpenWeb is, right now, in a very early stage of development. It does not read HTML files--only text files. In fact, this is a text file that is being displayed right now. However, I hope to be able to take the mechanism that I have developed to paint these text files and expand it to rendering HTML properly.

At this point, you may be wondering: How does a rendering engine work? For an incredibly basic overview, let's look at it this way: As the document is parsed, objects called "nodes" are created. These nodes contain all of the information necessary to display a certain part of a web page. These nodes are then taken and linked together as a linked list. This list is passed to the painter, which takes the information in the nodes and displays the web page.

If you would like to build, test or modify OpenWeb, please be aware of some prerequisites. OpenWeb currently uses SFML for its graphics handling, and uses TGUI to render its interface. These libraries are necessary to build OpenWeb. Additionally, other libraries, including the "C String Toolkit Library" (which in turn relies on Boost), are used.
Right now, I'm using quake to build the files on my development machines--I've found its implementation significantly more intuitive than cmake. The quake .pro file is not included in this repository, however, and a make file of some sort will have to be configured on any machine that is used for OpenWeb.

If nothing else, OpenWeb has taught me quite a bit about how to use external libraries. I spent the last weekend fighting various graphics libraries, trying to force them to compile and link with OpenWeb properly--and, at the end of it, I have learned a significant amount about libraries, compilation, linking, and how UNIX works in general.

So far, OpenWeb has been a great project. I'm excited to see where it develops.
