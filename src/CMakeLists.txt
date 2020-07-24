target_sources(MatrixExample PUBLIC MatrixExample.cpp)

target_sources(BindExample PUBLIC BindExample.cpp)

target_sources(StringLiteralsExample PUBLIC StringLiteralsExample.cpp)

target_sources(RAIIAndSmartExample PUBLIC RAIIAndSmartExample.cpp)

target_sources(InheritanceExample PUBLIC InheritanceExample.cpp)

target_sources(StructuredBindingExample PUBLIC StructuredBindingExample.cpp)

target_sources(RegexAndFilesystemExample PUBLIC RegexAndFilesystemExample.cpp)

target_sources(AsyncExample PUBLIC AsyncExample.cpp)

add_library(pImpllib SHARED pImplExampleImpl.cpp)

target_sources(pImplExample PUBLIC pImplUsage.cpp)

target_link_libraries(pImplExample PUBLIC pImpllib)

