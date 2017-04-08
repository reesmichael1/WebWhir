add_executable(layout_tests layout_tests.cpp)
target_link_libraries(layout_tests sfml-system sfml-graphics test_skeleton 
    Layout Box HTMLParser HTMLTokenizer Document HTMLToken StartToken EndToken
    CommentToken DocumentType DoctypeToken CharacterToken boost_regex 
    HTMLTokenizer_utils HTMLElement HTMLHeadElement HTMLBodyElement 
    HTMLParagraphElement HTMLTextElement)


INSTALL(TARGETS layout_tests DESTINATION ${WebWhirTests_SOURCE_DIR}/build)
