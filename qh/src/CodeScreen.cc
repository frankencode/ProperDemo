#include <cc/debug>
#include <qh/CodeMaster>
#include <qh/CodeScreen>

namespace qh {

Ref<CodeScreen> CodeScreen::create(String text, String theme)
{
    return new CodeScreen(text, theme);
}

CodeScreen::CodeScreen(String text, String theme):
    text_(text),
    theme_(CodeMaster::instance()->theme()),
    chunks_(CodeChunks::create())
{}

bool CodeScreen::project(Token *token, int i0, int i1)
{
    String scopeName;
    String ruleName;
    toki::Palette *palette = 0;
    toki::Style *style = 0;
    if (theme_->lookupPaletteByScope(token->scope(), &palette)) {
        scopeName = palette->scopeName();
        if (palette->lookupStyleByRule(token->rule(), &style)) {
            ruleName = style->ruleName();
        }
    }

    chunks_->append(CodeChunk::create(text_->copy(i0, i1), style));
        // FIXME: should also work with text_->select()!

    // CC_DEBUG << i0 << ".." << i1 << ":" << text_->select(i0, i1) << "(" << scopeName << ":" << ruleName << ")";

    return true;
}

} // namespace qh
