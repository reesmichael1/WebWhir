add_subdirectory(Document)
add_subdirectory(HTMLParser)
add_subdirectory(HTMLElements)
add_subdirectory(Layout)
add_subdirectory(WW_Window)
add_subdirectory(Loader)

add_executable(WebWhir main.cpp)
target_link_libraries(WebWhir sfml-system sfml-graphics sfml-window
    Layout Box HTMLParser HTMLTokenizer Document HTMLToken StartToken EndToken
    CommentToken DocumentType DoctypeToken CharacterToken boost_regex 
    HTMLTokenizer_utils HTMLElement HTMLHeadElement HTMLBodyElement 
    HTMLParagraphElement HTMLTextElement WW_Window Loader)
