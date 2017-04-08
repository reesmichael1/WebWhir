add_executable(htmlparser_tests htmlparser_tests.cpp)
add_executable(htmltokenization_tests htmltokenization_tests.cpp)
add_executable(htmlvalidation_tests htmlvalidation_tests.cpp)

target_link_libraries(htmlparser_tests test_skeleton 
    HTMLParser HTMLTokenizer Document HTMLToken StartToken EndToken
    CommentToken DocumentType DoctypeToken CharacterToken boost_regex 
    HTMLTokenizer_utils HTMLElement HTMLHeadElement HTMLBodyElement 
    HTMLParagraphElement HTMLTextElement)

target_link_libraries(htmltokenization_tests test_skeleton 
    HTMLParser HTMLTokenizer Document HTMLToken StartToken EndToken
    CommentToken DocumentType DoctypeToken CharacterToken boost_regex 
    HTMLTokenizer_utils HTMLElement HTMLHeadElement HTMLBodyElement 
    HTMLParagraphElement HTMLTextElement)

target_link_libraries(htmlvalidation_tests test_skeleton 
    HTMLParser HTMLTokenizer Document HTMLToken StartToken EndToken
    CommentToken DocumentType DoctypeToken CharacterToken boost_regex 
    HTMLTokenizer_utils HTMLElement HTMLHeadElement HTMLBodyElement 
    HTMLParagraphElement HTMLTextElement)

INSTALL(TARGETS htmlparser_tests htmlvalidation_tests htmltokenization_tests 
    DESTINATION ${WebWhirTests_SOURCE_DIR}/build)
