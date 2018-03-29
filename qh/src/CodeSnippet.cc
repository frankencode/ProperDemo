#include <qh/CodeLine>
#include <qh/CodeSnippet>

namespace qh {

Ref<CodeSnippet> CodeSnippet::create(View *parent, String text)
{
    return fly(new CodeSnippet(parent, text));
}

CodeSnippet::CodeSnippet(View *parent, String text):
    Column(parent)
{
    Ref<StringList> lines = text->split("\n");
    for (String line: lines)
        CodeLine::create(this, line);
}

} // namespaec qh
