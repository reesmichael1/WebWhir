# TODOS

The short-term goal of current development is to get a simple framework that can easily be extended to handle more diverse cases. This means that only subsets of features that will eventually be fully handled, such as the various states the tokenizer encounters while parsing HTML, are being implemented at a time. This allows the structure of the program to grow without be held back by trying to implement these early stages entirely.

This list is primarily included as a reminder to myself as to what needs to be done, but also to provide a general roadmap of features that should be included before the first release. As I go through the HTML standard and find more tasks that need to be done, this list will grow quickly! If you would like to work on one of these, please see the [Contributing Guide](CONTRIBUTING.md) and perhaps open a pull request to let me know you are doing so.

## List

- Log parse errors
- Handle more types of parse errors
- Handle additional states in the tokenization stage
- Develop HTMLElement interface more fully
- Handle more doctype tokens
- Implement graphical layout
- Include CSS support
- Implement scripting 

Finally, one can never have too many tests in a project! Even writing HTML strings that reveal interesting edge cases would be an important contribution.
