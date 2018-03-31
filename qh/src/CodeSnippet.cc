#include <cc/ui/ColumnLayout>
#include <qh/CodeLine>
#include <qh/CodeSnippet>

namespace qh {

Ref<CodeSnippet> CodeSnippet::create(View *parent, String text)
{
    return Object::create<CodeSnippet>(parent, text);
}

CodeSnippet::CodeSnippet(View *parent, String text):
    View(parent)
{
    ColumnLayout::setup(this);

    Ref<StringList> lines = text->split("\n");
    for (String line: lines)
        CodeLine::create(this, line);
}

} // namespaec qh
