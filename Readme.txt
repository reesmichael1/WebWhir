Welcome to OpenWeb!

OpenWeb is a personal project of mine. It came out of the news that my personal favorite browser, Opera, is abandoning my personal favorite rendering engine, Presto. Because of this, I've decided to write my own HTML rendering engine to gain more insight into how these incredible pieces of software work.

OpenWeb will be updated as I complete work. This could be a very short-lived project, or it could grow into a fully featured engine--only time will tell. If it does gain momentum, I'll probably package an interface as well and release a browser.

At this point, you may be wondering: How does a rendering engine work? For an incredibly basic overview, let's look at it this way: As the document is parsed, objects called "nodes" are created. These nodes contain all of the information necessary to display a certain part of a web page. These nodes are then taken and linked together. This list is passed to the painter, which takes the information in the nodes and displays the web page.

Right now, I'm using quake to build the files on my development machines--I've found its implementation significantly more intuitive than cmake.

So far, OpenWeb has been a great project. I'm excited to see where it develops.
