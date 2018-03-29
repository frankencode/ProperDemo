#include <cc/debug>
#include <cc/toki/Registry>
#include <cc/ui/TextRun>
#include <cc/ui/StylePlugin>
#include <cc/ui/Image>
#include <qh/CodeScreen>
#include <qh/CodeMaster>
#include <qh/CodeLine>

namespace qh {

using namespace cc::syntax;

Ref<CodeLine> CodeLine::create(View *parent, String text)
{
    return fly(new CodeLine(parent, text));
}

CodeLine::CodeLine(View *parent, String text_):
    View(parent),
    text(text_),
    textStyle(alias(StylePlugin::instance()->defaultMonoTextStyle)),
    boldTextStyle(alias(StylePlugin::instance()->defaultMonoBoldTextStyle)),
    margin(alias(StylePlugin::instance()->defaultTextMargin))
{
    color = transparent;

    updateHighlight();

    text     ->connect([=]{ updateHighlight(); });
    textStyle->connect([=]{ updateLayout(); });
    margin   ->connect([=]{ updateSize(); });
    size     ->connect([=]{ update(); });
}

void CodeLine::updateHighlight()
{
    Ref<SyntaxState> state = CodeMaster::instance()->language()->highlightingSyntax()->match(text());
    CC_INSPECT(state->valid());
    if (state->valid()) {
        Ref<CodeScreen> screen = CodeScreen::create(text());
        state->rootToken()->project(screen);
        codeChunks_ = screen->chunks();
    }
    else
        codeChunks_ = 0;

    updateLayout();
}

void CodeLine::updateLayout()
{
    textRun_ = TextRun::create();

    if (codeChunks_) {
        for (const CodeChunk *chunk: codeChunks_) {
            const toki::Style *style = chunk->style();
            if (style) {
                textRun_->append(
                    chunk->text(),
                    TextStyle::create(
                        style->bold() ? boldTextStyle()->font() : textStyle()->font(),
                        style->ink()
                    )
                );
            }
            else
                textRun_->append(chunk->text(), textStyle());
        }
    }
    else
        textRun_->append(text(), textStyle());

    updateSize();
    update();
}

void CodeLine::updateSize()
{
    size = textRun_->size() + 2 * margin();
}

void CodeLine::paint()
{
    Painter(this)->showTextRun(
        center() + 0.5 * Step { -textRun_->size()[0], textRun_->size()[1] },
        textRun_
    );
}

} // namespace qh
